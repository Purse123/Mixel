#pragma once
#include <iostream>
#include <cstring>
#include <vector>

namespace Formula {
  struct FunctionCall {
    std::string name;
    std::string args;
  };

  class Function() {
  public:
    virtual ~Function() = default;

    virtual double evaluate(const std::vector<double>& arg) const = 0;
  };

  class FunctionFactory {
  public:
    static std::unique_ptr<Function> create(const std::string& name);
  };
}
