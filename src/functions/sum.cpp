#include "functions/sum.hpp"

double Formula::SumFunction::evaluate(const std::vector<double>& args) const {
  double sumRes = 0;
  for (double v: args)
    sumRes += v;
  return sumRes;
}
