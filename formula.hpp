#pragma once
#include <iostream>
#include <cstring>
#include "csv_types.hpp"

namespace Formula {
  struct FunctionCall {
    std::string name;
    std::string args;
  };
}
