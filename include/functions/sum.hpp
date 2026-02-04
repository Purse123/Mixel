#pragma once
#include "../formula.hpp"

namespace Formula {
  class SumFunction() : public Function {
  public:
    virtual ~Function() = default;

    double evaluate(const std::vector<double>& arg) const override;
  };
}
