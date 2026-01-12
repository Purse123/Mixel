#include <iostream>
#include <string>

#include "csv_parser.hpp"
#include "viewer.hpp"
#include "csv_types.hpp"
#include "cell_method.hpp"

int main() {
  csvview::CSVParser c;
  csvview::Viewer v;

  c.parse("test.csv");
  c.normalizeTable();
  v.viewTable(c.getTable());

  std::cout << csvview::colNameToIndex("B") << std::endl;
  std::cout << csvview::indexToColName(27) << std::endl;
  csvview::CellRef ref = csvview::parseCellRef("A1");
  std::cout << "Row: " << ref.row << std::endl
	    << "Column: " << ref.col << std::endl;

  return 0;
}
