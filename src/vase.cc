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




void Vase::addShiny(size_t num_shiny, string unicode, string log) {
    srand((unsigned) time(0));
    size_t drop_idx = 0;
    for (size_t i = 0; i < 5; i++) {
        drop_idx += (vase_opening_left + rand()%(vase_opening_right - vase_opening_left));
    }
    // drop_idx = drop_idx / 5;
    drop_idx = 20;

    Shiny* new_shiny = new Shiny(num_shiny, unicode, log);
    shiny_vec.push_back(new_shiny);
    addShinyAtPosition(num_shiny, unicode, drop_idx, new_shiny);

}

void Vase::addShinyAtPosition(size_t num_shiny, string unicode, size_t drop_idx, Shiny* new_shiny) {
    
    // base case
    if (num_shiny == 0) {
        return;
    }
    
    for (size_t row = 0; row < 20; row++) {
        if (IsSpace(row, drop_idx)) {
            // continue falling 
        } else {
            // generate random num
            int position_num;
            // left right both empty
            if (IsSpace(row, drop_idx - 1) && IsSpace(row, drop_idx + 1)) {
                position_num = (rand()%(3));// 0, 1, 2
                position_num--;
            } 
            // left empty
            else if (IsSpace(row, drop_idx - 1)) {
                position_num = (rand()%(2));// 0, 1
                position_num--;
            }
            // right empty
            else if (IsSpace(row, drop_idx + 1)) {
                position_num = (rand()%(2));// 0, 1
            }
            // both full
            else {
                position_num = 0;
            }
            // int position_num = 0;


            if (position_num == -1) {
                addShinyAtPosition(num_shiny, unicode, drop_idx - 1, new_shiny);
            } else if (position_num == 1) {
                addShinyAtPosition(num_shiny, unicode, drop_idx + 1, new_shiny);

            } else {
                
                std::cout << drop_idx ;
                new_shiny->shiny_vec_.at(row - 1).replace(drop_idx, 1, unicode);
                addShinyAtPosition(num_shiny - 1, unicode, drop_idx, new_shiny);
            }
            return;
        }
    }
}










bool Vase::IsSpace(size_t row_idx, size_t col_idx) {
    if (vase_.at(row_idx).substr(col_idx, 1) != " ") {
        return false;
    }
    for (Shiny* shiny : shiny_vec) {
        if (shiny->shiny_vec_.at(row_idx).substr(col_idx, 1) != " ") {
            return false;
        }
    }
    return true;
}


string Vase::shinyAt(size_t row_idx, size_t col_idx) {
    for (Shiny* shiny : shiny_vec) {
        if (shiny->shiny_vec_.at(row_idx).substr(col_idx, 1) != " ") {
            // std::cout << "[" << shiny->shiny_vec_.at(row_idx).substr(col_idx, 1) << "]" << std::endl;
            return shiny->shiny_vec_.at(row_idx).substr(col_idx, 1);
        }
    }
    return " ";
}






const vector<string> Vase::stamnos = 
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
    {"           ⎛_             _⎞            "},
    {"           __|           |__            "},
    {"          ⎛                 ⎞           "},
    {"       ⎛‾‾                   ‾‾⎞        "},
    {"        ‾‾⎝                 ⎠‾‾         "},
    {"           \\               /            "},
    {"            \\___       ___/             "},
    {"                ⎛      ⎞                "},
    {"                 ‾‾‾‾‾‾                 "}
};



    //    {{" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},

    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},    
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "⎛", "_", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "_", "⎞", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}, 
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "_", "_", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", "_", "_", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}, 
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "⎛", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "⎞", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    //     {" ", " ", " ", " ", " ", " ", " ", " ", "⎛", "‾", "‾", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "‾", "‾", "⎞", " ", " ", " ", " ", " ", " ", " "},
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", "‾", "‾", "⎝", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "⎠", "‾", "‾", " ", " ", " ", " ", " ", " ", " ", " "},
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ","\\", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "/", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "\\","_", "_", "_", " ", " ", " ", " ", " ", " ", " ", "_", "_", "_", "/", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "⎛", " ", " ", " ", " ", " ", " ", " ", "⎞", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    //     {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "‾", "‾", "‾", "‾", "‾", "‾", "‾", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    //     };

// to be drawn (note: have to be a closed vase)
const vector<string> Vase::amphora = 
        {{}};

// to be drawn (note: have to be a closed vase)
const vector<string> Vase::kalathos = 
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


