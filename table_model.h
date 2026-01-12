#pragma once

namespace csvview {
  class TableModel {
    /*
    Explicit: Remove internal typeconversion
    later:
         - TableModel model = exampleTable;     [ERROR]
         - TableModel model(exampleTable);      [CORRECT]
    */
    explicit TableModel(Table data);
  public:
    // no of rows and col
    // reference to cell(at) with row and col number
    // and with cellRef
  private:
    Table table_;
  };
}
