// formula.hpp
// Copyright (c) 2026 Pierce Neupane - CC BY 4.0
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace Formula {
  struct FunctionCall {
    std::string name;
    std::string args;
  };

  /**
   *@class Function
   *
   *@breif:
   * This is a base interface
   * It is absolute class
   */
  class IFunction {
  public:
    virtual ~IFunction() = default;

    virtual double evaluate(const std::vector<double>& arg) const = 0;
    
    // virtual double evaluate(const std::vector<std::string>& str_arg, const std::vector<double>& arg) const = 0;
  };

  
  /**
   *@CLASS: FunctionFactory
   *
   *@NOTE:
   * THIS IS MY EXPERIMENTAL PROJECT
   * FOR FACTORY METHOD
   * GOT INSIPRATION FROM MINECRAFT IGUESS
   *
   * THIS IS THE PART WHERE I CONSIDER USING SOME LLM
   * I AM NEW WITH THIS ONE.
   */
  class FunctionFactory {
  public:
    //@Note: Only place to change when adding new function later
    static std::unique_ptr<Formula::IFunction> create(const std::string& name);
  };
}
