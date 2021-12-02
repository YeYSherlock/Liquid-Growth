#pragma once
#include "vase.hpp"

enum mode {menu, daily, exhibition};

class Collection {
public:
    /***** User Interface *****/

    // switch to vase of the next day
    void Next();

    // switch to vase of the previous day
    void Prev();

    // add # of shiny (only allowed for today)
    void Add(int num);

    // undo last entry (only allowed for today)
    void Undo();

    // add text to log
    void SetLog(string log_text);

    // change mood
    void SetMood(string mood_text);

    // change weather
    void SetWeather(string weather_text);

    // switch to vase of the specified date
    void ChangeDate(size_t month, size_t date, size_t year);

    // change mode
    void SetMode(mode setMode);

    /***** Hidden Support *****/
    
    // sort vases
    void SortVases()

private:
    mode curr_mode;
    vector<Vase> all_vases;
    Vase curr_vase;

};