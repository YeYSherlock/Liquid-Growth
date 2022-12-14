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
    Vase(size_t template_idx);
    Vase(size_t template_idx, size_t month, size_t date, size_t year, string day, string mood, string weather);
    void ToString();
    void addShiny(size_t num_shiny, string unicode, string log);

    void DeleteLastShiny();
    void SetLastLog(string log_text);
    void SetDay(string day_text);
    void SetMood(string mood_text);
    void SetWeather(string weather_text);

    size_t GetMonth();
    size_t GetDate();
    size_t GetYear();
    string GetMood();
    string GetWeather();
    string GetDay();
    vector<vector<string>> GetVase();
    vector<vector<string>> Getstamnos();
    vector<vector<string>> Getkalathos();
    vector<Shiny*> GetShinyvector();

    void SaveFile();
    void LoadFile(std::string filename);
    ~Vase();



private: 
    size_t date_[3];
    string day_;
    string mood_;
    string weather_;

    vector<Shiny*> shiny_vec;
    vector<vector<string>> vase_;

    size_t vase_opening_left;
    size_t vase_opening_right;
    int VaseOpeningWidth();
    bool IsSpace(size_t row_idx, size_t col_idx);
    string shinyAt(size_t row_idx, size_t col_idx);
    void addShinyAtPosition(size_t drop_row, string unicode, size_t drop_idx, Shiny* new_shiny);
    int TowerHieght(size_t row,size_t col);
    void addShiny(size_t num_shiny, string unicode,string friction,Shiny* new_shiny);


    // template empty vases
    // 0
    static const vector<vector<string>> stamnos;
    static const size_t stamnos_opening_left_idx = 13;
    static const size_t stamnos_opening_right_idx = 27;

    // 1
    static const vector<vector<string>> kalathos;
    static const size_t kalathos_opening_left_idx = 12;
    static const size_t kalathos_opening_right_idx = 28;



};

