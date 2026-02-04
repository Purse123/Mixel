// viewer.hpp
// Copyright (c) 2026 Pierce Neupane - CC BY 4.0
#pragma once
#include "csv_types.hpp"

namespace csvview {
  class Viewer {
  public:
    static void view(const csvview::Table& t);
    // TODOS: Pie chart and other statistics craps
  };
}
