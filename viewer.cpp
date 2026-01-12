#include "viewer.hpp"
#include <iostream>

void csvview::Viewer::viewTable(const Table& t) {
  for (const auto& r: t) {
    for (const auto& x: r) {
      std::cout << x << " ";
    }
    std::cout << '\n';
  }
}

