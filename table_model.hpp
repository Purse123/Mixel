#pragma once
#include "csv_types.hpp"

namespace csvview {
  /*
   *This takes data with help of parser and stays here for remaining
   */

  class TableModel {
  private:
    Table data_;
    
  public:
    // ===== CONSTRUCTORS =====
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

    // TODOS: const Cell& at(const CellRef&) const;
    // TODOS: Cell& at(const CellRef&);
    // TODOS: void addRow(const Row&);
  };
}
