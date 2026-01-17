#pragma once
#include "csv_types.hpp"

namespace csvview {
  class Viewer {
  public:
    static void view(const csvview::Table& t);
  };
}
