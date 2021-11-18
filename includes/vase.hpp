#pragma once

#include <iostream>
#include <vector>
#include "shiny.hpp"
// randomness
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
// usings
using std::vector;
using std::string;


class Vase {

    public:
    int date[3];
    Vase(size_t template_idx);
    void addShiny(size_t num_shiny, string unicode, string log);
    





    // below should be private, but for convenience temp public: 
    // private: 
    vector<string> vase_;
    vector<Shiny*> shiny_vec;
    size_t vase_opening_left;
    size_t vase_opening_right;
    int VaseOpeningWidth();
    bool IsSpace(size_t row_idx, size_t col_idx);
    string shinyAt(size_t row_idx, size_t col_idx);
    void addShinyAtPosition(size_t num_shiny, string unicode, size_t drop_idx, Shiny* new_shiny);



    // template empty vases
    // 0
    static const vector<string> stamnos;
    static const size_t stamnos_opening_left_idx = 13;
    static const size_t stamnos_opening_right_idx = 27;

    // 1
    static const vector<string> amphora;
    static const size_t amphora_opening_left_idx = 0;
    static const size_t amphora_opening_right_idx = 20;

    // 2
    static const vector<string> kalathos;
    static const size_t kalathos_opening_left_idx = 0;
    static const size_t kalathos_opening_right_idx = 20;



};

