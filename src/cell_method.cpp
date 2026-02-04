#include <cctype>
#include <cassert>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "cell_method.hpp"

size_t csvview::colNameToIndex(const std::string& name) {
  assert(!name.empty());
  size_t acc = 0;
  
  for (size_t i = 0; i < name.length(); i++) {
    char ch = static_cast<char>(std::toupper(static_cast<unsigned char>(name[i])));

    if (ch < 'A' || ch > 'Z') {
      throw std::invalid_argument("Invalid Column name");
    }
    
    size_t v = static_cast<size_t>(ch - 'A' + 1);
    acc = acc * 26 + v;
  }

  return acc - 1;
}

std::string csvview::indexToColName(size_t index) {
  std::string result;
  index += 1;
  
  while (index > 0) {
    index--;
    char c = static_cast<char>('A' + (index % 26));
    result.push_back(c);
    index /= 26;
  }

  std::reverse(result.begin(), result.end());
  return result;
}

// A1 -> { row: 0, col: 0}
// CellRef cr = csvview::parseCellRef("G4");
csvview::CellRef csvview::parseCellRef(const std::string& ref) {
  csvview::CellRef result;
  
  size_t i = 0;
  while (i < ref.size() &&
	 std::isalpha(static_cast<unsigned char>(ref[i]))) {
    ++i;
  }
  
  if (i == 0 || i == ref.size()) {
    throw std::invalid_argument("Invalid cell reference");
  }

  std::string colPart = ref.substr(0, i);
  
  std::string rowPart = ref.substr(i);
  for (char c : rowPart) {
    if (!std::isdigit(static_cast<unsigned char>(c))) {
      throw std::invalid_argument("Invalid cell refernce");
    }
  }

  size_t row = std::stoul(rowPart);
  if (row == 0) {
    throw std::invalid_argument("Row index must be >= 1");
  }
  result.row = row - 1;
  result.col = colNameToIndex(colPart);

  return result;
}
