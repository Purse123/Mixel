#include "functions/sum.hpp"

double Formula::SumFunction::evaluate(const std::vector<double>& arg) const {
  double sumRes = 0;
  for (double v: args)
    sum += v;
  return sumRes;
}
