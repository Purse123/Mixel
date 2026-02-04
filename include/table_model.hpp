// table_model.hpp
// Copyright (c) 2026 Pierce Neupane - CC BY 4.0
#pragma once
#include "csv_types.hpp"
#include "formula.hpp"
#include <unordered_set>
#include <unordered_map>

namespace std {
  template <>
  struct hash<csvview::CellRef> {
    size_t operator()(const csvview::CellRef& c) const noexcept {
      return (c.row << 16) ^ c.col; // simple hash combining row & col
    }
  };
} // namespace std

namespace csvview {
  /*
   *This takes data with help of parser and stays here for remaining
   */

  class TableModel {
  private:
    // ====== Data Members ======
    Table data_;

    /**
     *@breif tracking cell currently evaluated (cycle detection)
     *
     *Why unordered_set
     * Insertion, deletion, finding = O(1) (avg)
     * traverse, access element     = O(n)
     */
    std::unordered_set<CellRef> visiting_;

    /**
     *@breif cache mechnism
     *@key CellRef
     *@value double
     *
     *Why unordered_set
     * Insertion, deletion, finding, access element = O(1) (avg)
     * traverse                                     = O(n)
     */

    std::unordered_map<CellRef, double> cache_;
    
  public:
    // ===== CONSTRUCTOR =====
    /*
    Explicit: Remove internal typeconversion
    later:
         - TableModel model = exampleTable;     [ERROR]
         - TableModel model(exampleTable);      [CORRECT]
    */
    explicit TableModel(Table data);
    
    // ===== Methods =====
    void normalize();
    const Table& data() const;
    
    void evaluateAll();
    void UpdateFileWithCache();

    double evaluateFormula(const std::string& formula);
    bool isFormula(const std::string& cell);
    bool isFunctionCall(const std::string& expr);
    Formula::FunctionCall parseFunction(const std::string& expr);

    double evaluateExpression(const std::string& expr);

    // ================= Evaluate methods ========================
    double evaluateFunction(const std::string& expr);

    std::vector<csvview::CellRange>
    extractRangesFromFormula(const std::string& args);
    
    std::vector<csvview::CellRef>
    expandRanges(const std::vector<csvview::CellRange>& ranges);
    // ============================================================
    
    // TODOS: const Cell& at(const CellRef&) const;
    // TODOS: Cell& at(const CellRef&);
    // TODOS: void addRow(const Row&);
  private:
    /*
     *A1(=B1*2) is referenced then send check on cache_ and visiting_
     *if not found add to visiting_
     *
     *then it need B1 then similar
     *
     *now B1 is value 5, then erase from visiting_
     *cache_ = {B1 -> 5}
     *
     *now erase A1 from visiting_
     *cache_ = {B1 -> 5, A1 -> 10}
     */
    double evaluateCell(const CellRef& ref);

    // -------------
    // Tokenizer
    // -------------
    std::vector<std::string> tokenize(const std::string& expr);


    // --------------------------------
    // Shunting Yard: infix -> postfix
    // --------------------------------
    std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens);

    // --------------------------------
    // Shunting Yard: infix -> postfix
    // --------------------------------
    double evaluatePostfix(const std::vector<std::string>& postfix);
  };
}
