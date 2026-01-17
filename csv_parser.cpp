#include "csv_parser.hpp"
#include "table_model.hpp"
#include "table_model.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

using csvview::Row;
using csvview::Table;

/*
 *@brief: Its was storing parse data in same class private variable
int csvview::CSVParser::parse(const std::string file_path) {
  std::ifstream fp(file_path);
  if (!fp.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return -1;
  }
  
  std::string line;
  int count = 0;
  
  while (std::getline(fp, line)) {
    Row row;
    std::stringstream ss(line);
    std::string token;
    
    while (std::getline(ss, token, ',')) {
      row.push_back(token);
      count++;
    }
    values_.push_back(row);
  }
  
  fp.close();
  return count;
}
*/


csvview::TableModel csvview::CSVParser::parse(const std::string file_path) {
  std::ifstream fp(file_path);
  if (!fp.is_open()) {
    throw std::runtime_error("Error opening file");
  }

  Table table;
  std::string line;
  
  while (std::getline(fp, line)) {
    Row row;
    std::stringstream ss(line);
    std::string token;
    
    while (std::getline(ss, token, ',')) {
      row.push_back(token);
    }
    table.push_back(std::move(row));
  }
  
  fp.close();
  return csvview::TableModel(std::move(table));
}
