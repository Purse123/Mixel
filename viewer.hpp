#pragma once
#include "csv_types.hpp"

namespace csvview {
  class Viewer {
  public:
    static void viewTable(const csvview::Table& t);
  };
}
