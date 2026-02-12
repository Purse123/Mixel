#include "functions/pie.hpp"
#include <vector>
#include <stdexcept>
#include <numeric>
#include <iomanip>
#include <fstream>

constexpr double degree_in_circle = 360.0;
constexpr const char* output_path = "pie_char.purse.sim";

double Formula::PieFunction::evaluate(const std::vector<double>& args) const {
  if (args.empty()) return 0.0;
  
  std::vector<double> res = eval_Vect(args);

  // File operation for pie chart value
  std::ofstream output_fp(output_path);
  if (output_fp.is_open()) {
    output_fp << std::fixed << std::setprecision(6);

    for (size_t i = 0; i < args.size(); ++i) {
      output_fp << args[i] << " " << res[i] << "\n";
    }
    output_fp.close();
  }
  
  return res.empty() ? 0.0 : 1.0;
}

std::vector<double> Formula::PieFunction::eval_Vect(std::vector<double> args) const{
  if (args.empty()) {
    throw std::invalid_argument("[Error] Empty vector to pie function");
  }
  // std::accumulate() is more faster

  // It is clean
  // It initialize to acc then acc = acc + 1
  // TODOS: replace std::accumulate()
  double total = std::accumulate(args.begin(), args.end(), 0.0);

  if (total == 0.0) {
    throw std::invalid_argument("[Error] Empty vector to pie function");
  }

  std::vector<double> degrees;
  degrees.reserve(args.size());

  for (double value : args) {
    degrees.push_back((value / total) * degree_in_circle);
  }
  
  return degrees;
}
