#include <iostream>
#include <string>

#include "csv_parser.hpp"
#include "viewer.hpp"
#include "csv_types.hpp"
#include "cell_method.hpp"
#include "table_model.hpp"

int main() {
  csvview::CSVParser parser;
  csvview::TableModel model = parser.parse("test.csv");
  csvview::Viewer::view(model.data());

  std::cout << csvview::colNameToIndex("B") << std::endl;
  std::cout << csvview::indexToColName(27) << std::endl;
  csvview::CellRef ref = csvview::parseCellRef("A1");
  std::cout << "Row: " << ref.row << std::endl
	    << "Column: " << ref.col << std::endl;
  
  return 0;
}
