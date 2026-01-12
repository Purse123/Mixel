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
    std::string filePath_;
    std::string lockPath_;
    
  public:
    int parse(const char* file_path);
    void normalizeTable();
    const Table& getTable() const;

    // TODOS: void createLock();
    // TODOS: void removeLock();
  };

  // ~CSVParser() {
  //   removeLock();
  // }
}
