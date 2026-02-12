#pragma once
#include "../formula.hpp"

namespace Formula {

  class PieFunction : public IFunction {
  public:
    double evaluate(const std::vector<double>& args) const override;
    
    std::vector<double> eval_Vect(std::vector<double> args) const;
  };
}
