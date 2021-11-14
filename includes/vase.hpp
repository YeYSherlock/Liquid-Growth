#pragma once

#include <iostream>
#include <vector>
using std::vector;
using std::string;


class vase {

    public:

    vase(int template_idx);
    void addShiny(int num_shiny, string shiny);





    // below should be private, but for convenience temp public: 
    // private: 
    vector<vector<string>> vase_2d;
    int VaseOpeningWidth();



    // template empty vases
    // 0
    static const vector<vector<string>> stamnos;
    // 1
    static const vector<vector<string>> amphora;
    // 2
    static vector<vector<string>> kalathos;
    // static const vector<vector<string>> lebes;
    // static const vector<vector<string>> pelike;
    // static const vector<vector<string>> pithos;
    // static const vector<vector<string>> situla;
    // static const vector<vector<string>> kernos;
    // static const vector<vector<string>> phormiskos;
    // static const vector<vector<string>> patera;
    // static const vector<vector<string>> phiale;
    // static const vector<vector<string>> nestoris;
    // static const vector<vector<string>> lekythos;
    // static const vector<vector<string>> loutrophoros;
    // static const vector<vector<string>> epinetron;
    // static const vector<vector<string>> oil_lamp;
    // static const vector<vector<string>> plemochoe;
    // static const vector<vector<string>> exaleiptron;

};

