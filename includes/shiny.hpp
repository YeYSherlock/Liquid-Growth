#ifndef NODE_HPP
#define NODE_HPP

#include <string>

struct Shiny {
  Shiny() = default;
  Shiny(std::string name, int size, int character) : ShinyName(name), ShinySize(size), ShinyCharacter(character){}
  std::string ShinyName;
  int ShinySize;
  char ShinyCharacter;
};

#endif
