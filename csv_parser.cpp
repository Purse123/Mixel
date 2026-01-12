#include "csv_parser.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using csvview::Row;
using csvview::Table;

int csvview::CSVParser::parse(const char* file_path) {
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

void csvview::CSVParser::normalizeTable() {
  size_t maxCols = 0;
  
  // @result = max column in each row
  for (const auto& row : values_)
    if (row.size() > maxCols)
      maxCols = row.size();

  // adding empty string field for padding
  for (auto& row : values_)
    while (row.size() < maxCols)
      row.push_back("*");
}
    
const Table& csvview::CSVParser::getTable() const {
  return values_;
}

