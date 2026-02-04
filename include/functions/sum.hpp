#pragma once
#include "../formula.hpp"

namespace Formula {
  class SumFunction : public IFunction {
  public:
    double evaluate(const std::vector<double>& args) const override;
  };
}
