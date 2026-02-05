#include "functions/sum.hpp"
#include <vector>

double Formula::SumFunction::evaluate(const std::vector<double>& args) const {
  double res = 0;
  
  for (double v: args)
    res += v;
  return res;
}
