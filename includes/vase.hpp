#pragma once

#include <iostream>
#include <vector>
#include "shiny.hpp"
using std::vector;
using std::string;


class vase {

    public:
    int date[3];
    vase(int template_idx);
    void addShiny(int num_shiny, string shiny);





    // below should be private, but for convenience temp public: 
    // private: 
    vector<string> vase_;
    vector<Shiny*> shiny_vec;
    int VaseOpeningWidth();



    // template empty vases
    // 0
    static const vector<string> stamnos;

    // 1
    static const vector<string> amphora;
    static const size_t amphora_opening_width;

    // 2
    static const vector<string> kalathos;
    static const size_t kalathos_opening_width;



};

