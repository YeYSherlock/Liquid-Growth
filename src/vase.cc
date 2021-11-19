#include "vase.hpp"
#include <random>



Vase::Vase(size_t template_idx) {
    // initialize
    if (template_idx == 0) {
        vase_ = stamnos;
        vase_opening_left = stamnos_opening_left_idx;
        vase_opening_right = stamnos_opening_right_idx;
    } else if (template_idx == 1) {
        vase_ = amphora;
        vase_opening_left = amphora_opening_left_idx;
        vase_opening_right = amphora_opening_right_idx;
    } else if (template_idx == 2) {
        vase_ = kalathos;
        vase_opening_left = kalathos_opening_left_idx;
        vase_opening_right = kalathos_opening_right_idx;
    } else {
        throw std::runtime_error("template idx out of bound");
    }

}

Vase::Vase(size_t template_idx, size_t month, size_t date, size_t year, string day, string mood, string weather): Vase(template_idx) {
    date_[0] = month;
    date_[1] = date;
    date_[2] = year;
    day_ = day;
    mood_ = mood;
    weather_ = weather;
}

void Vase::ToString() {

std::cout << "[Menu]" << std::endl;
std::cout << " + next     >> check vase of the next day" << std::endl;
std::cout << " + prev     >> check vase of the previous day" << std::endl;
std::cout << " + add #    >> add entry (only allowed for today)" << std::endl;
std::cout << " + undo     >> undo last entry (only allowed for today)" << std::endl;
std::cout << " + log @    >> add text to log." << std::endl;
std::cout << " + day @    >> change day" << std::endl;
std::cout << " + mood @   >> change mood" << std::endl;
std::cout << " + weat @   >> change weather" << std::endl;
std::cout << " + cd @/@/@ >> check vase of the day" << std::endl;

    
    
    // print vase and all shiny
    for (size_t i = 0; i < 20; i++) {
        for (size_t j = 0; j < 40; j++) {
            if (shinyAt(i, j) != " ") {
                std::cout << shinyAt(i, j);
            } else {
                std::cout << vase_.at(i).at(j);
            }

            // std::cout << vase.vase_.at(i).at(j);
            // std::cout << vase.stamnos.at(i).at(j);
        }
        std::cout << std::endl;
    }

    // print all other attributes
    std::cout << "[" << day_ << "] " << "[Mood: " << mood_ << "] " << "[Weather: " << weather_ << "]" << std::endl;
    std::cout << "+--------------[" << date_[0] << "/" << date_[1] << "/" << date_[2] << "]" << "--------------+" << std::endl;
    for (Shiny* shiny : shiny_vec) {
        if (shiny->num_shiny_ >= 10) {

            std::cout << "| " << shiny->num_shiny_ << " " << shiny->unicode_ << " << "  << shiny->log_ << std::endl;
        } else {
            std::cout << "| _" << shiny->num_shiny_ << " " << shiny->unicode_ << " << "  << shiny->log_ << std::endl;        }
    }
    std::cout << "+----------------------------------------+" << std::endl;

}
void Vase::addShiny(size_t num_shiny, string unicode, string log) {
    // make random value between vase_opening_right and vase_opening_left
    srand((unsigned) time(0));
    // drop_idx = 20;

    Shiny* new_shiny = new Shiny(num_shiny, unicode, log);
    shiny_vec.push_back(new_shiny);
    //addShiny(num_shiny,unicode,"Low Friction",new_shiny);
    addShiny(num_shiny,unicode,"High Friction", new_shiny);
    
}

void Vase::addShiny(size_t num_shiny, string unicode,string friction,Shiny* new_shiny){
    if(friction == "Low Friction"){
        for(size_t i = 0; i < num_shiny; i++){
            addShinyAtPosition2( 0, unicode, (vase_opening_left + rand()%(vase_opening_right - vase_opening_left - 1) + 1), new_shiny);
        }
    }else{
        size_t drop_idx = 0;
        for (size_t i = 0; i < 5; i++) {
            drop_idx += (vase_opening_left + rand()%(vase_opening_right - vase_opening_left));
        }
        drop_idx = drop_idx / 5;
        for(size_t i = 0; i < num_shiny; i++){
            addShinyAtPosition2( 0, unicode, drop_idx, new_shiny);
        }
    }
}

void Vase::addShinyAtPosition(size_t num_shiny, size_t drop_row, string unicode, size_t drop_idx, Shiny* new_shiny) {
    // ensuring it stays within vertical bound (0 ~ 39)
    if (drop_idx >= 39) {
        drop_idx = 39;
    } else if (drop_idx <= 0) {
        drop_idx = 0;
    }

    // ensuring it stays within horizontal bound (0 ~ 19)
    if (drop_row <= 0) {
        drop_row = 1;
    } else if (drop_row >= 19) {
        drop_row = 19;
    }    

    // base case
    if (num_shiny == 0) {
        return;
    }
    
    for (size_t row = drop_row; row < 20; row++) {
        if (IsSpace(row, drop_idx)) {
            // continue falling 
        } else {
            // generate random num
            int position_num;
            // left right both empty
            if (IsSpace(row, drop_idx - 1) && IsSpace(row, drop_idx + 1)) {
                position_num = (rand()%(3));// 0, 1, 2
                position_num--; // -1, 0, 1
            } 
            // left empty
            else if (IsSpace(row, drop_idx - 1)) {
                position_num = (rand()%(2));// 0, 1
                position_num--; // -1, 0
            }
            // right empty
            else if (IsSpace(row, drop_idx + 1)) {
                position_num = (rand()%(2));// 0, 1
            }
            // both full
            else {
                position_num = 0;
            }

            if (position_num == -1) {
                addShinyAtPosition(num_shiny, row - 1, unicode, drop_idx - 1, new_shiny);
            } else if (position_num == 1) {
                addShinyAtPosition(num_shiny, row - 1, unicode, drop_idx + 1, new_shiny);

            } else {
                
                // std::cout << drop_idx ;
                new_shiny->shiny_vec_.at(row - 1).at(drop_idx) = unicode;
                addShinyAtPosition(num_shiny - 1, 0, unicode, drop_idx, new_shiny);
            }
            return;
        }
    }
}

void Vase::addShinyAtPosition2(size_t drop_row, string unicode, size_t drop_idx, Shiny* new_shiny) {
    // ensuring it stays within vertical bound (0 ~ 39)
    if (drop_idx >= 39) {
        drop_idx = 39;
    } else if (drop_idx <= 0) {
        drop_idx = 0;
    }

    // ensuring it stays within horizontal bound (0 ~ 19)
    if (drop_row <= 0) {
        drop_row = 1;
    } else if (drop_row >= 19) {
        drop_row = 19;
    }    
    
    if (IsSpace(drop_row + 1, drop_idx)) {
        //Continue Falling
        addShinyAtPosition2(drop_row + 1, unicode, drop_idx, new_shiny);
    }else{
        //Reach Ground
        int left_height;
        int right_height;
        if(drop_idx - 1 < 0){
            //left wall
            left_height = 0;
        }else{
            left_height = TowerHieght(drop_row,drop_idx - 1);
        }

        if(drop_idx + 1 > 39){
            // right wall
            right_height = 0;
        }else{
            right_height = TowerHieght(drop_row,drop_idx + 1);
        }

        std::cout << "Left tower " << left_height <<std::endl;
        std::cout << "Right tower " << right_height <<std::endl;

        if(left_height > 2 ){
            // Tower collapse to left 
            addShinyAtPosition2(drop_row  + 1, unicode, drop_idx - 1, new_shiny);
        }else if(right_height > 2){
            // Tower collapse to right
            addShinyAtPosition2(drop_row  + 1, unicode, drop_idx + 1, new_shiny);
        }else if(left_height > 1 && rand() % 2 == 0 ){
            addShinyAtPosition2(drop_row  + 1, unicode, drop_idx - 1, new_shiny);
        }else if(right_height > 1 && rand() % 2 == 0 ){
            addShinyAtPosition2(drop_row  + 1, unicode, drop_idx + 1, new_shiny);
        }else{
            //Shiny Settled
            new_shiny->shiny_vec_.at(drop_row).at(drop_idx) = unicode;
        }
    }
}

int Vase::TowerHieght(size_t row,size_t col){
    if(!IsSpace(row,col)){
        return 0;
    }else{
        return TowerHieght(row+1, col) + 1;
    }
}

bool Vase::IsSpace(size_t row_idx, size_t col_idx) {
    // iterating through vase template itself
    if (vase_.at(row_idx).at(col_idx) != " ") {
        return false;
    }
    // iterating through each shiny class and check if it is " "
    for (Shiny* shiny : shiny_vec) {
        if (shiny->shiny_vec_.at(row_idx).at(col_idx) != " ") {
            return false;
        }
    }
    return true;
}


string Vase::shinyAt(size_t row_idx, size_t col_idx) {
    for (Shiny* shiny : shiny_vec) {
        if (shiny->shiny_vec_.at(row_idx).at(col_idx) != " ") {
            // std::cout << "[" << shiny->shiny_vec_.at(row_idx).substr(col_idx, 1) << "]" << std::endl;
            return shiny->shiny_vec_.at(row_idx).at(col_idx);
        }
    }
    return " ";
}



Vase::~Vase() {
    for (Shiny* shiny : shiny_vec) {
        delete shiny;
    }
}



 
const vector<vector<string>> Vase::stamnos = 
       {{" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},

        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "⎛", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "⎞", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},    
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "‾", "‾", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", "‾", "‾", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}, 
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "_", "_", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", "_", "_", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}, 
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "⎛", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "⎞", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", "⎛", "‾", "‾", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "‾", "‾", "⎞", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", "‾", "‾", "⎝", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "⎠", "‾", "‾", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ","\\", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "/", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "\\"," ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "/", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "‾", "‾", "⎛", " ", " ", " ", " ", " ", " ", " ", "⎞", "‾", "‾", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "‾", "‾", "‾", "‾", "‾", "‾", "‾", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        };
// {
//     {"                                        "},
//     {"                                        "},
//     {"                                        "},
//     {"                                        "},
//     {"                                        "},
//     {"                                        "},
//     {"                                        "},
//     {"                                        "},
//     {"                                        "},
//     {"                                        "},
//     {"                                        "},
//     {"           ⎛_             _⎞            "},
//     {"           __|           |__            "},
//     {"          ⎛                 ⎞           "},
//     {"       ⎛‾‾                   ‾‾⎞        "},
//     {"        ‾‾⎝                 ⎠‾‾         "},
//     {"           \\               /            "},
//     {"            \\            /             "},
//     {"              ‾‾⎛      ⎞‾‾                "},
//     {"                 ‾‾‾‾‾‾                 "}
// };




// to be drawn (note: have to be a closed vase)
const vector<vector<string>> Vase::amphora = 
        {{}};

// to be drawn (note: have to be a closed vase)
const vector<vector<string>> Vase::kalathos = 
        {{}};

// vector<vector<string>> vase::kalathos = 
//         {{}};
// string row1 = "___                     ___";
    
// string row2 = "   ⎞                  ⎛   ";

// string row3 = "    ⎞                ⎛    ";

// string row4 = "     ⎞              ⎛     ";
// string row5 = "      |             |      ";
// string row6 = "      |             |      ";
// string row7 = "      |             |      ";

// string row8 = "      ⎞             ⎛     ";
// string row9 = "      _⎛___________⎞_     ";
// std::vector<std::string> rows = {row1, row2, row3, row4, row5, row6, row7, row8, row9};

// for (auto row : rows) {
//     vector<string> vectorrow;
//     for(size_t col = 0; col < row.length(); col++) {
//         string c;
//         c.push_back(row[col]);
//         vectorrow.push_back(c);
//     }
//     kalathos.push_back(vectorrow);
// }


