#include "shiny.hpp"
#include <random>


Shiny::Shiny(size_t num_shiny, string unicode, std::string log) : num_shiny_(num_shiny), unicode_(unicode), log_(log) {
    shiny_vec_ = 
    {
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "},
        {"                                        "}
    };
}
