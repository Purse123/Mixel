#include "csv_types.hpp"
#include "table_model.hpp"
#include "formula.hpp"
#include "cell_method.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <string>
#include <utility>
#include <unordered_set>
#include <unordered_map>

csvview::TableModel::TableModel(Table data): data_(std::move(data)) {}

void csvview::TableModel::normalize() {
  size_t maxCols = 0;
  
  // @result = max column in each row
  for (const auto& row : data_)
    if (row.size() > maxCols)
      maxCols = row.size();

  // adding empty string field for padding
  for (auto& row : data_)
    while (row.size() < maxCols)
      row.push_back("0");
}
    
const csvview::Table& csvview::TableModel::data() const {
  return data_;
}

void csvview::TableModel::UpdateFileWithCache() {
  for (const auto& [ref, value] : cache_) {
    data_[ref.row][ref.col] = std::to_string(value);
  }
}

void csvview::TableModel::evaluateAll() {
  for (size_t r = 0; r < data_.size(); ++r) {
    for (size_t c = 0; c < data_[r].size(); ++c) {
      // return: It can return same cell multiple times in any order
      evaluateCell({r, c});
    }
  }

  // replace formula with computed values
  UpdateFileWithCache();
}

double csvview::TableModel::evaluateCell(const CellRef& ref) {
  //already computed cell
  if (cache_.count(ref)) {
    // 1 -> key exists on cache       // exit with return
    // 0 -> key doesn't exists
    return cache_[ref];
  }

  // circular reference
  // eg:
  // A1 = B1 + 1
  // B1 = A1 + 1
  if (visiting_.count(ref)) {
    // principle: if same ref on visiting_ then recursion occurs
    throw std::runtime_error("Circular reference detected");
  }

  visiting_.insert(ref);

  const std::string& raw = data_[ref.row][ref.col];
  double result = 0.0;

  if (isFormula(raw)) {
    result = evaluateFormula(raw);
  } else {
    result = std::stod(raw);
  }

  visiting_.erase(ref);
  cache_[ref] = result;
  return result;
}

// 2 type of formulas
// operator expression or function call
double csvview::TableModel::evaluateFormula(const std::string& formula) {
  // remove "="
  std::string expr = csvview::trimmed(formula.substr(1));

  // expression starts with 'letter' followed by 'letter or digit' then '('
  // edge case A1(B1)
  if (isFunctionCall(expr)) {
    return evaluateFunction(expr);
  }

  return evaluateExpression(expr);
}
bool csvview::TableModel::isFormula(const std::string& cell) {
  return !cell.empty() && cell[0] == '=';
}

bool csvview::TableModel::isFunctionCall(const std::string& expr) {
  if (expr.empty() || !std::isalpha(expr[0])) {
    return false;
  }

  size_t i = 0;
  while(i < expr.size() && std::isalnum(expr[i])) {
    ++i;
  }

  return (i < expr.size()) && (expr[i] == '(');
}

Formula::FunctionCall csvview::TableModel::parseFunction(const std::string& expr) {
  size_t open = expr.find('(');
  size_t close = expr.rfind(')');

  if (open == std::string::npos || close == std::string::npos || close < open) {
    throw std::invalid_argument("Invalid function synatx");
  }

  return {
    expr.substr(0, open),
    expr.substr(open + 1, close - open - 1)
  };
}

double csvview::TableModel::evaluateExpression(const std::string& expr) {
  std::vector<std::string> tokens = tokenize(expr);
  std::vector<std::string> postfix = infixToPostfix(tokens);
  return evaluatePostfix(postfix);
}

std::vector<std::string> csvview::TableModel::tokenize(const std::string& expr) {
  std::vector<std::string> tokens;
  std::string cur;

  for(size_t i = 0; i < expr.size(); ++i) {
    char ch = expr[i];
    
    if (std::isspace(ch)) continue;      // space

    if (std::isdigit(ch) || ch == '.') { // number
      cur += ch;
    } else if (std::isalpha(ch)) { // cell reference
      cur += ch;
    } else {
      if (!cur.empty()) {
	tokens.push_back(cur);
	cur.clear();
      }
      tokens.push_back(std::string(1, ch));
    }
  }
  if (!cur.empty()) tokens.push_back(cur);
  return tokens;
}

std::vector<std::string> csvview::TableModel::infixToPostfix(const std::vector<std::string>& tokens) {
  std::vector<std::string> res;
  std::stack<std::string>  opstack;

  // Lambda syntax for: int precedence(const std::string& op);
  auto precedence = [](const std::string& op) -> int {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
  };

  auto isOperator = [](const std::string& tok) -> bool {
    return (tok == "+" || tok == "-" || tok == "*" ||
	    tok == "/" || tok == "^");
  };

  for (const auto& tok: tokens) {
    if (std::isdigit(tok[0]) || std::isalpha(tok[0])) {
      res.push_back(tok);
    } else if (tok == "(") {
      opstack.push(tok);
    } else if (tok == ")") {
      while (!opstack.empty() && opstack.top() != "(") {
	res.push_back(opstack.top());
	opstack.pop();
      }
      // discard ')'
      if (!opstack.empty()) opstack.pop();
    } else if (isOperator(tok)) {
      while (!opstack.empty() && isOperator(opstack.top())
	     && precedence(opstack.top()) >= precedence(tok)) {
	res.push_back(opstack.top());
	opstack.pop();
      }
      opstack.push(tok);
    } else {
      throw std::invalid_argument("Unknown token: " + tok);
    }
  }
  while (!opstack.empty()) {
    if (opstack.top() == "(" || opstack.top() == ")")
      throw std::invalid_argument("parenthesis sickness");

    res.push_back(opstack.top());
    opstack.pop();
  }
  return res;
}

double csvview::TableModel::evaluatePostfix(const std::vector<std::string>& postfix) {
  std::stack<double> s;

  for (const auto& tok : postfix) {
    if (std::isdigit(tok[0])) {   	// number
      s.push(std::stod(tok));
    }
    else if (std::isalpha(tok[0])) {     // cell reference
      csvview::CellRef ref = csvview::parseCellRef(tok);
      auto it = cache_.find(ref);
      
      if (it == cache_.end()) {
	throw std::runtime_error("Cell " + tok + " has no value");
      }

      s.push(it->second);
    }
    else {			// operator
      if (s.size() < 2)
	throw std::runtime_error("Invalid expression");
      
      double b = s.top();
      s.pop();
      double a = s.top();
      s.pop();

      if (tok == "+")
	s.push(a + b);
      else if (tok == "-")
	s.push(a - b);
      else if (tok == "*")
	s.push(a * b);
      else if (tok == "/") {
	if (b == 0) throw std::runtime_error("Division by zero");
	s.push(a / b);
      }
      else if (tok == "^")
	s.push (std::pow(a, b));
      else
	throw std::runtime_error("Unknown operator: " + tok);
    }
  }

  if (s.size() != 1) throw std::runtime_error("Invalid expression");
  return s.top();
}
// const csvview::Cell& at(const CellRef&) const;
// csvviewCell& at(const CellRef&);
// void addRow(const Row&);
