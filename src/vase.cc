#include "vase.hpp"
#include <random>
#include <fstream>
#include <sstream> 

//constructor for vase
Vase::Vase(size_t template_idx) {
    // initialize
    if (template_idx == 0) {
        vase_ = stamnos;
        vase_opening_left = stamnos_opening_left_idx;
        vase_opening_right = stamnos_opening_right_idx;
    }else if (template_idx == 1) {
        vase_ = kalathos;
        vase_opening_left = kalathos_opening_left_idx;
        vase_opening_right = kalathos_opening_right_idx;
    } else {
        throw std::runtime_error("template idx out of bound");
    }
}

//Constructor for vase
Vase::Vase(size_t template_idx, size_t month, size_t date, size_t year, string day, string mood, string weather): Vase(template_idx) {
    date_[0] = month;
    date_[1] = date;
    date_[2] = year;
    day_ = day;
    mood_ = mood;
    weather_ = weather;
}

void Vase::ToString() {
    std::cout << "+----------------------------------------+" << std::endl;
    // print vase and all shiny
    for (size_t i = 0; i < 20; i++) {
        std::cout << "|";
        for (size_t j = 0; j < 40; j++) {
            if (shinyAt(i, j) != " ") {
                std::cout << shinyAt(i, j);
            } else {
                std::cout << vase_.at(i).at(j);
            }
        }
        std::cout << "|";
        std::cout << std::endl;
    }

    // print all other attributes
    std::cout << "[" << day_ << "] " << "[Mood: " << mood_ << "] " << "[Weather: " << weather_ << "]" << std::endl;
    
    std::cout << "+--------------[";
    if (date_[0] >= 10) {
        std::cout << date_[0] << "/";
    } else {
        std::cout << "0" << date_[0] << "/";
    }
    if (date_[1] >= 10) {
        std::cout << date_[1] << "/";
    } else {
        std::cout << "0" << date_[1] << "/";
    }
    std::cout << date_[2] << "]" << "--------------+" << std::endl;

    for (Shiny* shiny : shiny_vec) {
        if (shiny->num_shiny_ >= 10) {

            std::cout << "| " << shiny->num_shiny_ << " " << shiny->unicode_ << " << "  << shiny->log_ << std::endl;
        } else {
            std::cout << "| _" << shiny->num_shiny_ << " " << shiny->unicode_ << " << "  << shiny->log_ << std::endl;        }
    }
    std::cout << "+----------------------------------------+" << std::endl;

    std::cout << "Type \"help\" to get a list of commands available" << std::endl;

}

//there is a 50%/50% chance whether the shiny will slip to the bottom, or in another word, whether the shiny has high or low friction
void Vase::addShiny(size_t num_shiny, string unicode, string log) {
    // make random value between vase_opening_right and vase_opening_left
    srand((unsigned) time(0));
    // drop_idx = 20;

    Shiny* new_shiny = new Shiny(num_shiny, unicode, log);
    shiny_vec.push_back(new_shiny);
    if(rand() % 2 == 1){
        addShiny(num_shiny,unicode,"Low Friction",new_shiny);    
    }else{
        addShiny(num_shiny,unicode, "High Friction", new_shiny);
    }
}

void Vase::addShiny(size_t num_shiny, string unicode,string friction,Shiny* new_shiny){
    if(friction == "Low Friction"){
        for(size_t i = 0; i < num_shiny; i++){
            addShinyAtPosition( 0, unicode, (vase_opening_left + rand()%(vase_opening_right - vase_opening_left - 1) + 1), new_shiny);
        }
    }else{
        size_t drop_idx = 0;
        for (size_t i = 0; i < 5; i++) {
            drop_idx += (vase_opening_left + rand()%(vase_opening_right - vase_opening_left));
        }
        drop_idx = drop_idx / 5;
        for(size_t i = 0; i < num_shiny; i++){
            addShinyAtPosition( 0, unicode, drop_idx, new_shiny);
        }
    }
}

void Vase::addShinyAtPosition(size_t drop_row, string unicode, size_t drop_idx, Shiny* new_shiny) {
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
        addShinyAtPosition(drop_row + 1, unicode, drop_idx, new_shiny);
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
            addShinyAtPosition(drop_row  + 1, unicode, drop_idx - 1, new_shiny);
        }else if(right_height > 2){
            // Tower collapse to right
            addShinyAtPosition(drop_row  + 1, unicode, drop_idx + 1, new_shiny);
        }else if(left_height > 1 && rand() % 2 == 0 ){
            addShinyAtPosition(drop_row  + 1, unicode, drop_idx - 1, new_shiny);
        }else if(right_height > 1 && rand() % 2 == 0 ){
            addShinyAtPosition(drop_row  + 1, unicode, drop_idx + 1, new_shiny);
        }else{
            //Shiny Settled
            new_shiny->shiny_vec_.at(drop_row).at(drop_idx) = unicode;
        }
    }
}

//Height of the tower that is piled up 
int Vase::TowerHieght(size_t row,size_t col){
    if(!IsSpace(row,col)){
        return 0;
    }else{
        return TowerHieght(row+1, col) + 1;
    }
}

//check whether the character in this index is space 
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


//return the shiny at this index
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

//Save the vase 
void Vase::SaveFile() {

    //std::to_string 

    std::string filename = "storage/";
    if (date_[0] >= 10) {
        filename += std::to_string(date_[0]);
    } else {
        filename += "0";
        filename += std::to_string(date_[0]);
    }
    filename += "_";
    if (date_[1] >= 10) {
        filename += std::to_string(date_[1]);
    } else {
        filename += "0";
        filename += std::to_string(date_[1]);
    }
    filename += "_";
    filename += std::to_string(date_[2]);


    // filename += 
    //  + std::to_string(date_[0]) + "_" + std::to_string(date_[1]) + "_" + std::to_string(date_[2]);


    //std::string filename = "test";
    // Create an output filestream object
    std::ofstream saveFile(filename);
    //Save type of vase
    if(!stamnos.empty()) {
        saveFile << "stamnos" << std::endl;
    }else if (!kalathos.empty()) {
        saveFile << "kalathos" << std::endl;
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
    
    // Original: 
    // saveFile << "+--------------[" << date_[0] << "/" << date_[1] << "/" << date_[2] << "]" << "--------------+" << std::endl;
    
    
    saveFile << "+--------------[";
    if (date_[0] >= 10) {
        saveFile << date_[0] << "/";
    } else {
        saveFile << "0" << date_[0] << "/";
    }
    if (date_[1] >= 10) {
        saveFile << date_[1] << "/";
    } else {
        saveFile << "0" << date_[1] << "/";
    }
    saveFile << date_[2] << "]" << "--------------+" << std::endl;

    //


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
                if(shiny->shiny_vec_.at(i).at(j) != " ") {
                    saveFile << shiny->unicode_;
                    saveFile << " " << i << " " << j << " ";
                }
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
        }else if (line == "kalathos") {
            vase_ = kalathos;
        }
    }
    std::getline(saveFile, line);
    shiny_vec_size = std::stoi(line);
    // load vase
    //vase_.clear();
     while(std::getline(saveFile, line) && row != 20) {
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
    mood_ = portionlist[2].substr(6, portionlist[2].size() - 8);
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
        // std::cout << line << std::endl;
        row2++;
        // std::cout << shiny_vec_size << std::endl;
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
                // std::cout << shiny[1] << std::endl;
                num_shiny = std::stoi(shiny[1]);
            }
        }
        string unicode = shiny[2];
        string log;
        for(size_t word = 4; word < shiny.size(); word++) {
            if(word != shiny.size() - 1) {
                log += shiny[word] + " ";
            }
            else {
                log += shiny[word];
            }
        }
        Shiny* new_shiny = new Shiny(num_shiny, unicode, log);
        shiny_vec.push_back(new_shiny);
        if(row2 == shiny_vec_size) {
            break;
        }
    }


    //load shiny_vec_ of each shiny by looping shiny_vec_size times and copying the value at each row and col 
    for(int i = 0; i < shiny_vec_size; i++){
        int row3 = 0;
        while(std::getline(saveFile, line) && row3 < 20) {
            if(line.substr(0, 1) != "") {
                std::stringstream shinyvecss(line);
                std::string shinypos;
                std::vector<std::string> shinys;
                while(std::getline(shinyvecss, shinypos, ' ')) {
                    shinys.push_back(shinypos);
                }
                for(size_t numshiny = 0; numshiny < shinys.size() / 3; numshiny++) {
                    shiny_vec[i]->shiny_vec_[std::stoi(shinys[3*numshiny + 1])][std::stoi(shinys[3*numshiny + 2])] = shinys[0];
                }
            }
            row3++;
            if(row3 == 20) {
                break;
            }
        }
    }


}

Vase::~Vase() {
    for (Shiny* shiny : shiny_vec) {
        delete shiny;
    }
}
 
vector<vector<string>> Vase::GetVase(){
    return vase_;
}

vector<vector<string>> Vase::Getstamnos(){
    return stamnos;
}

vector<vector<string>> Vase::Getkalathos(){
    return kalathos;
}

string Vase::GetMood(){
    return mood_;
}

string Vase::GetWeather(){
    return weather_;
}

string Vase::GetDay(){
    return day_;
}

vector<Shiny*> Vase::GetShinyvector(){
    return shiny_vec;
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

        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},    
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", "???", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", "???", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}, 
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "_", "_", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", "_", "_", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}, 
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", "???", "???", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", "???", "???", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", "???", "???", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", "???", "???", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ","\\", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "/", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "\\"," ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "/", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", "???", "???", " ", " ", " ", " ", " ", " ", " ", "???", "???", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", "???", "???", "???", "???", "???", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        };

const vector<vector<string>> Vase::kalathos = 
       {{" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "\\", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "/", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "," "},

        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},    
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "\\", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "/", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}, 
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}, 
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
        };
