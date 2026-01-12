#pragma once
#include <vector>
#include <iostream>
#include <string>

namespace csvview {
  using Cell = std::string;
  using Row = std::vector<Cell>;
  using Table = std::vector<Row>;

  struct CellRef {
    size_t row;
    size_t col;
  };

  struct CellRange {
    CellRef from;
    CellRef to;
  };
}
