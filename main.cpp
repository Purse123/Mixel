#include <string>

#include "csv_parser.hpp"
#include "viewer.hpp"
#include "csv_types.hpp"
#include "cell_method.hpp"
#include "table_model.hpp"

int main() {
  csvview::CSVParser parser;
  csvview::TableModel table = parser.parse("test.csv");
  csvview::Viewer::view(table.data());

  std::cout << std::endl << "After:" << std::endl;
  table.evaluateAll();

  // print after eval result
  const auto& data = table.data();
  for (size_t r = 0; r < data.size(); ++r) {
    for (size_t c = 0; c < data[r].size(); ++c) {
      std::cout << data[r][c] << "\t";
    }
    std::cout << "\n";
  }

  return 0;
  
  std::cout << "col name B -> index: " <<csvview::colNameToIndex("B") << std::endl;
  std::cout << "index 27 -> col name: " << csvview::indexToColName(27) << std::endl;
  csvview::CellRef ref = csvview::parseCellRef("A1");
  std::cout << "Row: " << ref.row << std::endl
	    << "Column: " << ref.col << std::endl;
  
}
