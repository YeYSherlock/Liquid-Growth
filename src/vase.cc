#include "vase.hpp"
#include <random>
#include <fstream>
#include <sstream> 


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

    std::cout << "Type \"help\" to get a list of commands available" << std::endl;

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

        //std::cout << "Left tower " << left_height <<std::endl;
        //std::cout << "Right tower " << right_height <<std::endl;

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


void Vase::DeleteLastShiny() {
    if (shiny_vec.size() >= 1) {
        // free memory
        delete shiny_vec.at(shiny_vec.size() - 1);
        // remove last element
        shiny_vec.pop_back();
    }
}

void Vase::SetLastLog(string log_text) {
    if (shiny_vec.size() >= 1) {
        // remove last element
        shiny_vec.at(shiny_vec.size() - 1)->log_ = log_text;
    }
}

void Vase::SetDay(string day_text) {
    day_ = day_text;
}

void Vase::SetMood(string mood_text) {
    mood_ = mood_text;
}

void Vase::SetWeather(string weather_text) {
    weather_ = weather_text;
}

size_t Vase::GetMonth() {
    return date_[0];
}

size_t Vase::GetDate() {
    return date_[1];
}

size_t Vase::GetYear() {
    return date_[2];
}

void Vase::SaveFile() {
    std::string filename = std::to_string(date_[0]) + "_" + std::to_string(date_[1]) + "_" + std::to_string(date_[2]);
    // Create an output filestream object
    std::ofstream saveFile(filename);
    //Save type of vase
    if(!stamnos.empty()) {
        saveFile << "stamnos" << std::endl;
    }
    else if(!amphora.empty()) {
        saveFile << "amphora" << std::endl;
    }
    else if (!kalathos.empty()) {
        saveFile << "amphora" << std::endl;
    }
    //save shiny_vec_ size
    saveFile << shiny_vec.size() << std::endl;
    //save vase
    for (size_t i = 0; i < 20; i++) {
        for (size_t j = 0; j < 40; j++) {
            if (shinyAt(i, j) != " ") {
                saveFile << shinyAt(i, j);
            } else {
                saveFile << vase_.at(i).at(j);
            }
        }
        saveFile << std::endl;
    }

    // save all other attributes
    saveFile << "[" << day_ << "] " << "[Mood: " << mood_ << "] " << "[Weather: " << weather_ << "]" << std::endl;
    saveFile << "+--------------[" << date_[0] << "/" << date_[1] << "/" << date_[2] << "]" << "--------------+" << std::endl;
    for (Shiny* shiny : shiny_vec) {
        if (shiny->num_shiny_ >= 10) {

            saveFile << "| " << shiny->num_shiny_ << " " << shiny->unicode_ << " << "  << shiny->log_ << std::endl;
        } else {
            saveFile << "| _" << shiny->num_shiny_ << " " << shiny->unicode_ << " << "  << shiny->log_ << std::endl;        }
    }
    // save shiny_vec_ by printing the shiny_vec_ of each shiny
    for (Shiny* shiny : shiny_vec) {
        for (size_t i = 0; i < 20; i++) {
            for (size_t j = 0; j < 40; j++) {
                saveFile << shiny->shiny_vec_.at(i).at(j);
            }
            saveFile << std::endl;
        }
    }
    // close file
    saveFile.close();

}
void Vase::LoadFile(std::string filename) {
    vector<vector<string>> vase;
    std::ifstream saveFile(filename);
    if(!saveFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    // Helper vars
    string line;
    int row = 0; //used for the vase to get 20 rows of the vase
    int shiny_vec_size;


    // get the vase
    if(saveFile.good()) {
        // Get the first line in the file
        std::getline(saveFile, line);
        if(line == "stamnos") {
            vase_ = stamnos;
        }
        else if(line == "amphora") {
            vase_ = amphora;
        }
        else if (line == "kalathos") {
            vase_ = kalathos;
        }
    }
    std::getline(saveFile, line);
    shiny_vec_size = std::stoi(line);
    // load vase
    vase_.clear();
     while(std::getline(saveFile, line) && row != 20) {
        vector<string> current_row;
        for(size_t col = 0; col < 40; col++) {
            string c;
            c.push_back(line[col]);
            current_row.push_back(c);
            //std::cout << c <<std::endl;
        }
        vase_.push_back(current_row);
        // std::cout << current_row << std::endl;
        row++;
    }
    // get day, mood, weather
    // split strings by '[' to extract variables
    std::stringstream ss(line);
    std::string portion;
    std::vector<std::string> portionlist;
    while(std::getline(ss, portion, '[')) {
        portionlist.push_back(portion);
    }
    day_ = portionlist[1].substr(0, portionlist[1].size() - 2);
    mood_ = portionlist[2].substr(6, portionlist[1].size() - 3);
    weather_ = portionlist[3].substr(9, portionlist[3].size() - 10);
    //date by splitting strings by '/'
    std::getline(saveFile, line);
    std::stringstream datess(line);
    std::string date;
    std::vector<std::string> datelist;
    while(std::getline(datess, date, '/')) {
        datelist.push_back(date);
        //std::cout << date <<std::endl;
    }
    date_[0] = std::stoi(datelist[0].substr(16, 2));
    date_[1] = std::stoi(datelist[1].substr(0, 2));
    date_[2] = std::stoi(datelist[2].substr(0, 4));

    //shiny vector, by going line by line and making a shiny from each line
    //stops when it reaches shiny_vec_size
    int row2 = 0;
    while(std::getline(saveFile, line) && row2 < shiny_vec_size) {
        row2++;
        std::cout << shiny_vec_size << std::endl;
        std::stringstream shinyss(line);
        std::string shinyinfo;
        std::vector<std::string> shiny;
        while(std::getline(shinyss, shinyinfo, ' ')) {
            shiny.push_back(shinyinfo);
        }
        size_t num_shiny = 0;
        //if num_shiny is single digit then ignore the _
        for (char const &c : shiny[1]) {
            if (std::isdigit(c) == 0){
                num_shiny = std::stoi(shiny[1].substr(1, 1));
                break;
            }
            else {
                std::cout << shiny[1] << std::endl;
                num_shiny = std::stoi(shiny[1]);
            }
        }
        string unicode = shiny[2];
        string log;
        for(size_t word = 4; word < shiny.size(); word++) {
            log += shiny[word] + " ";
        }
        Shiny* new_shiny = new Shiny(num_shiny, unicode, log);
        shiny_vec.push_back(new_shiny);
    }
    //load shiny_vec_ of each shiny by looping shiny_vec_size times and copying the value at each row and col 
    for(int i = 0; i < shiny_vec_size; i++){
        int row3 = 0;
        while(std::getline(saveFile, line) && row3 < 20) {
            vector<string> current_row;
            for(size_t col = 0; col < 40; col++) {
                string c;
                c.push_back(line[col]);
                shiny_vec[i]->shiny_vec_[row3][col] = c;
                //std::cout << row << col << c <<std::endl;
            }
            // std::cout << current_row << std::endl;
            row3++;
        }
    }


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

        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "⎛", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "⎞", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},    
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


