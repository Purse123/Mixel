#pragma once
#include "../formula.hpp"

namespace Formula {
  class AvgFunction : public IFunction {
  public:
    double evaluate(const std::vector<double>& args) const;
  };
}
