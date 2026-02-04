// csv_parser.hpp
// Copyright (c) 2026 Pierce Neupane - CC BY 4.0
#pragma once
#include <vector>
#include <string>
#include "csv_types.hpp"
#include "table_model.hpp"

/*
  Used CSV format
  a, b, c, d
  e, f, g, h
*/

namespace csvview {
  /**
   *@class CSVParser
   *@brief
   * Parses CSV files into structured TableModel object
   * TODOS: To add mechanism for lock file
   *
   * CSVParser class is responsible for reading CSV file from disk and convert them into TableModel object, which owns and manages table data. CSVParser doesn't itself store the table value.
   *
   *Desgin note:
   *  CSVParser acts as a factory, It produces TableModel obj but doesn't manages lifetime
   *  Exception are thrown for file I/O error or unrecoverable issue
   *  It supports parsing // formula handling and file locking
   *
   *Example usage:
   *  CSVParser parser;
   *  TableModel model = parser.parse("example.csv");
   *  Viewer::view(model);
   *
   *@see class TabelModel
   *@see class Viewer
   */
  class CSVParser {
  private:
    Table values_;
    std::string filePath_;
    std::string lockPath_;
    
  public:
    csvview::TableModel parse(const std::string file_path);
    // TODOS: void createLock();
    // TODOS: void removeLock();
    
    // ~CSVParser() {
    //   removeLock();
    // }
  };
}
