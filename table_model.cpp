#include "csv_types.hpp"
#include "table_model.hpp"
#include  <vector>
#include  <iostream>
#include  <utility>

csvview::TableModel::TableModel(Table data): data_(std::move(data)) {}

void csvview::TableModel::normalize() {
  size_t maxCols = 0;
  
  // @result = max column in each row
  for (const auto& row : data_)
    if (row.size() > maxCols)
      maxCols = row.size();

  // adding empty string field for padding
  for (auto& row : data_)
    while (row.size() < maxCols)
      row.push_back("*");
}
    
const csvview::Table& csvview::TableModel::data() const {
  return data_;
}

// const csvview::Cell& at(const CellRef&) const;
// csvviewCell& at(const CellRef&);
// void addRow(const Row&);
