#pragma once
#include <vector>
#include <string>
#include "csv_types.hpp"

/*
  Used CSV format
  a, b, c, d
  e, f, g, h
*/

namespace csvview {

  class CSVParser {
  private:
    Table values_;
    
  public:
    int parse(const char* file_path);
    void normalizeTable();
    const Table& getTable() const;

  };
}
