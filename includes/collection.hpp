#pragma once
#include "vase.hpp"

// enum mode {main_menu, daily, exhibition};

/// @brief 
class Collection {
public:

    /***** User Interface *****/

    // return the pointer of the current vase
    Vase* CurrVase();

    // Create a vase at this date
    void AddAtDate(size_t month, size_t date, size_t year, size_t template_idx);

    // add # of shiny (only allowed for today)
    void Add(int num, string unicode, string log_text);

    // switch to vase of the next day
    void Next();

    // switch to vase of the previous day
    void Prev();

    // undo last entry (only allowed for today)
    void Undo();

    // add text to log
    void SetLastLog(string log_text);

    // change day
    void SetDay(string day_text);

    // change mood
    void SetMood(string mood_text);

    // change weather
    void SetWeather(string weather_text); 

    // switch to the specified date
    void ChangeDate(size_t month, size_t date, size_t year);

    // change mode
    // void SetMode(mode setMode);

    /// @todo probably change all hidden support to protected later. 
    /***** Hidden Support *****/ 
    
    // print the current vase
    void ToString();

    // sort vases (maybe not necessary)
    void SortVases();

    // return count of all_vases_
    size_t GetVaseCount() { return all_vases_.size(); };

    // return vase_idx_
    size_t GetVaseIdx() { return vase_idx_; };
    
    // return vase_at vase_idx_
    Vase* GetVase() { return all_vases_[vase_idx_]; }

    // set vase_idx_
    void SetVaseIdx(size_t idx) { vase_idx_ = idx; };

    // save all files into storage
    void SaveAllFiles();

    // get curr_mode_
    // mode GetCurrMode() { return curr_mode_; };
    
    // Delete? 

        

private:
    // mode curr_mode_;
    vector<Vase*> all_vases_;
    size_t vase_idx_;

};
