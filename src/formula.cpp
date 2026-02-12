#include <string>
#include <cctype>
#include <algorithm>
#include "formula.hpp"
#include "functions/sum.hpp"
#include "functions/avg.hpp"
#include "functions/pie.hpp"

std::unique_ptr<Formula::IFunction> Formula::FunctionFactory::create(const std::string& name) {
  // weird way of Uppercase conversion
  std::string upper = name;

  /**
   *@note:
   * ::toupper is from C standard <cctype> just like `int toupper(int c)`
   * std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
   * This will be ok for ASCII but fail when non-ASCII         ^^^^^^^^^

   *@Therefore: using another but similar method accepting non-ascii too
   *@see: https://en.cppreference.com/w/cpp/string/byte/toupper.html
   */
  // output_iterator transform(input_iterator, input_iterator, output_iterator, unary_op );
  std::transform(upper.begin(), upper.end(), upper.begin(), [](unsigned char c) {return std::toupper(c);});

  if (upper == "SUM")
    return std::make_unique<SumFunction>();
  else if (upper == "AVG" || upper == "AVERAGE")
    return std::make_unique<AvgFunction>();
  else if (upper == "PIE")
    return std::make_unique<PieFunction>();
  
  throw std::invalid_argument("Unknown function: " + name);
}
