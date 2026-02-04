#pragma once
#include <iostream>
#include <vector>
#include "csv_types.hpp"

namespace csvview {
  // A -> 0, AA -> 26
  size_t colNameToIndex(const std::string& name);
  
  // 0 -> A, 27 -> AB
  std::string indexToColName(size_t index);
  
  // A1 -> { row: 0, col: 0}
  // CellRef cr = csvview::parseCellRef("G4");
  CellRef parseCellRef(const std::string& ref);

  // bool isNum(const std::string& cell);
  // bool isFormula(const std::string& cell);

  // does cell ref contain in range
  // bool containRef(const CellRange&, const CellRef&);

  
  // TODOS: std::string getCellName(const CellRef& ref);
  // TODOS: Handle Cell range A1:B2 or B2:A1
  // TODOS: bool isValidCellRef(const std::string& ref);
  // TODOS: bool isValidColName(const std::string& ref);
  // TODOS: std::vector<CellRef> rangeExpand(const CellRange& r);
  // TODOS: Maybe operator overloading for cellRefs


  // TODOS: If A1 changes B1 should change handlers
}
