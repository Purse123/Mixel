#include "functions/avg.hpp"
#include <stdexcept>
#include <vector>

double Formula::AvgFunction::evaluate(const std::vector<double>& args) const {
  if (args.empty()) {
    throw std::invalid_argument("AVG requires at least one number");
  }

  // for (size_t i = 0; i < args.size(); i++) {
    // std::cout << "  args[" << i << "] = " << args[i] << std::endl;
  // }
  
  double res = 0.0;
  for (double v: args)
    res += v;
  
  return (res / static_cast<double>(args.size()));
}
