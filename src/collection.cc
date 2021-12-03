#include "collection.hpp"

// switch to vase of the next day
void Collection::Next() {
    if (vase_idx_ <= all_vases_.size() - 2) {
        vase_idx_++;
    }
}

// switch to vase of the previous day
void Collection::Prev() {
    if (vase_idx_ >= 1) {
        vase_idx_--;
    }
}

// add # of shiny (only allowed for today)
void Collection::Add(int num, string unicode, string log_text) {
    all_vases_[vase_idx_]->addShiny(num, unicode, log_text);
}

// undo last entry (only allowed for today)
void Collection::Undo() {
    all_vases_[vase_idx_]->DeleteLastShiny();
}

// add text to log
void Collection::SetLastLog(string log_text) {
    all_vases_[vase_idx_]->SetLastLog(log_text);
}

// change day
void Collection::SetDay(string day_text) {
    all_vases_[vase_idx_]->SetDay(day_text);
}


// change mood
void Collection::SetMood(string mood_text) {
    all_vases_[vase_idx_]->SetMood(mood_text);
}

// change weather
void Collection::SetWeather(string weather_text) {
    all_vases_[vase_idx_]->SetWeather(weather_text);
}

// switch to vase of the specified date
void Collection::ChangeDate(size_t month, size_t date, size_t year) {
    for (size_t i = 0; i < all_vases_.size(); i++) {
        if (all_vases_.at(i)->GetMonth() == month
         && all_vases_.at(i)->GetDate() == date
         && all_vases_.at(i)->GetYear() == year) {
            vase_idx_ = i;
            return;
        }
    }
    throw std::runtime_error("Date Not Found, or Haven't initialized yet. Try to \"build\" a Vase in that date");
}

// switch to vase of the specified date
void Collection::AddAtDate(size_t month, size_t date, size_t year, size_t template_idx) {
    // convert month, date, year to easy to compare formate
    // Example: 2021 12 09 -> 20211209
    size_t add_num = year * 10000 + month * 100 + date;


    // check date formate error
    if (month <= 0 || month >= 13 || date <= 0 || date >= 32 || year < 1000 || year > 3000) {
        throw std::runtime_error("Date formate error. Correct Example: 12 09 2021");
    }

    // create new vase
    Vase* new_vase = new Vase(template_idx, month, date, year, "~day~", "~mood~", "~weather~");

    // empty situation
    if (all_vases_.size() == 0) {
        all_vases_.push_back(new_vase);
        vase_idx_ = 0;
    } 
    // normal situation
    else {
        for (size_t i = 0; i < all_vases_.size(); i++) {
            size_t i_num = all_vases_.at(i)->GetYear() * 10000 + all_vases_.at(i)->GetMonth() * 100 + all_vases_.at(i)->GetDate();
            std::cout << "comparing: " << add_num << " and " << i_num << " at idx: " << vase_idx_ << std::endl;
            if (add_num < i_num) {  
                all_vases_.insert(all_vases_.begin() + i, new_vase);
                vase_idx_ = i;
                return;
            } 

        } 
        // latest entry
        all_vases_.push_back(new_vase);
        vase_idx_ = all_vases_.size() - 1;
            
        


        // std::cout << all_vases_.size() << std::endl;
    }


}

void Collection::ToString() {
    all_vases_.at(vase_idx_)->ToString();
}


// change mode
// void Collection::SetMode(mode setMode) {

// }