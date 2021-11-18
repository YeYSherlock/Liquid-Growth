#ifndef SHINY_HPP
#define SHINY_HPP

#include <string>
#include <vector>
#include <iostream>
using std::vector;
using std::string;

class Shiny {
  public:
  Shiny(size_t num_shiny, string unicode, std::string log);
  size_t num_shiny_;
  string unicode_;
  string log_;
  vector<vector<string>> shiny_vec_;
};

#endif
