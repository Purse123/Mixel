#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

namespace csvview {
  using Cell = std::string;
  using Row = std::vector<Cell>;
  using Table = std::vector<Row>;

  struct CellRef {
    size_t row;
    size_t col;
    
    bool operator==(const CellRef& other) const {
      return row == other.row && col == other.col;
    }
  };

  struct CellRange {
    CellRef from;
    CellRef to;
  };

  // trim from start (in place)
  static inline void ltrim(std::string &s) {
    s.erase(
	    s.begin(),
	    std::find_if(s.begin(), s.end(), [](unsigned char ch){
	      return !std::isspace(ch);
	    })
    );
  }

  // trim from end (in place)
  static inline void rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), s.rend(),[](unsigned char ch){
	      return !std::isspace(ch);
	    }).base(), s.end()
    );
  }

  // trim from both ends (in place)
  static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
  }

  // trim and return a new string (copy)
  static inline std::string trimmed(const std::string &s) {
    std::string copy = s;
    trim(copy);
    return copy;
  }
}
