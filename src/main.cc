#include "vase.hpp"
#include "shiny.hpp"
#include "collection.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <filesystem>

using std::stoi;
using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::directory_iterator;

#define print(s) std::cout << s << std::endl;




int main() {

    
    



    // initialize interface, implement menu/etc later
    Collection collection;

    // vec to save the to be loaded file names
    vector<string> saved_files_vec;
    
    // loading all files into saved_files_vec
    string path = "storage";
    for (const auto & file : directory_iterator(path)) {
        
        collection.AddAtDate(01, 01, 3000, 0);
        collection.CurrVase()->LoadFile(file.path());

        // saved_files_vec.push_back(file.path());
    }

    // for (auto & file_name : saved_files_vec) {

    // }


    std::cout << "+----------------------------------------+" << std::endl;
    std::cout << "| |                                    | |" << std::endl;
    std::cout << "| |        |‾|         /‾_‾_‾|         | |" << std::endl;
    std::cout << "| |        | |        | |              | |" << std::endl;
    std::cout << "| |        | |        | | |_‾\\         | |" << std::endl;
    std::cout << "| |        | |        | \\   | |        | |" << std::endl;
    std::cout << "| |        |_‾_‾_‾|    \\_‾_‾_/         | |" << std::endl;
    std::cout << "| |                                    | |" << std::endl;
    std::cout << "| |    __╲╲Liquid╲╲\\ᛥ/╱╱Growth╱╱__     | |" << std::endl;
    std::cout << "| |                                    | |" << std::endl;
    std::cout << "+----------------------------------------+" << std::endl;
    std::cout << "   [type \"start\" to begin the journey]    " << std::endl;
    std::cout << "     [type \"help\" to check commands]      " << std::endl;


    /*
    build 12 06 2002 0
    build 12 07 2002 0
    build 12 05 2002 0
    add 10 Ѿ Talked with family
    add 30 Ǥ Finished TRA
    */


    while (true) {
        // record user input
        // vector<string> input_vec;
        string input_string;
        std::getline(std::cin, input_string);
        std::istringstream buf(input_string);
        std::istream_iterator<std::string> beg(buf), end;
        std::vector<string> input(beg, end);

        if (input.size() == 1 && (input.at(0) == "start" || input.at(0) == "Start" || input.at(0) == "s")) {
            collection.SetVaseIdx(0);
            collection.ToString();
            continue;
        }
        /* Show Commands Available */
        else if (input.size() == 1 && (input.at(0) == "help" || input.at(0) == "h")) {
            std::cout << std::endl << std::endl << std::endl;
            std::cout << std::endl << std::endl << std::endl;
            std::cout << "[Commands Available]" << std::endl;
            std::cout << " + build m d y V >> add entry at specified day, V = vase type" << std::endl;
            std::cout << " + cd m d y      >> check vase of the day" << std::endl;
            std::cout << " + add # U T     >> add num unicode log_text" << std::endl;
            std::cout << " + next          >> check vase of the next day" << std::endl;
            std::cout << " + prev          >> check vase of the previous day" << std::endl;
            std::cout << " + log @         >> add text to log." << std::endl;
            std::cout << " + mood @        >> change mood" << std::endl;
            std::cout << " + weath @       >> change weather" << std::endl;
            std::cout << " + undo          >> undo last entry (only allowed for today)" << std::endl;
            continue;
        }
        /* AddAtDate */
        // build m d y which_vase
        else if (input.size() == 5 && input.at(0) == "build") {
            // std::cout << "passed" << std::endl;
            try {
                collection.AddAtDate(stoi(input.at(1)), stoi(input.at(2)), stoi(input.at(3)), stoi(input.at(4)));
            } catch (const std::exception &exc) {
                std::cerr << exc.what() << std::endl; 
            }
        }
        /* ChangeDate */
        // cd m d y
        else if (input.size() == 4 && input.at(0) == "cd") {
            try {
                collection.ChangeDate(stoi(input.at(1)), stoi(input.at(2)), stoi(input.at(3)));
            } catch (const std::runtime_error &exc) {
                std::cerr << exc.what() << std::endl;
                continue;
            }
        }
        /* Add */
        // add num unicode logText
        else if (input.size() >= 4 && input.at(0) == "add") {
            
            string log_text = "";
            log_text += input.at(3);
            for (size_t i = 4; i < input.size(); i++) {
                log_text += " ";
                log_text += input.at(i);
            }
            

            collection.Add(stoi(input.at(1)), input.at(2), log_text);
        }
        /* Next */
        else if (input.size() == 1 && input.at(0) == "next") {
            // current one is the latest.
            if (collection.GetVaseCount() <= collection.GetVaseIdx() + 1) {
                std::cout << "Current vase is the latest. Use \"build\" to create a vase of the desired date." << std::endl; 
                continue;
            } 
            // current one is not the latest. 
            else { 
                collection.Next();
            }
        }
        /* Prev */
        else if (input.size() == 1 && input.at(0) == "prev") {
            // current one is the latest.
            if (collection.GetVaseIdx() == 0) {
                std::cout << "Current vase is the oldest. Use \"build\" to create a vase of the desired date." << std::endl; 
                continue;
            } 
            // current one is not the latest. 
            else { 
                collection.Prev();
            }
        }
        /* log */
        else if (input.size() >= 2 && input.at(0) == "log") {
            string log_text = "";
            log_text += input.at(1);
            for (size_t i = 2; i < input.size(); i++) {
                log_text += " ";
                log_text += input.at(i);
            }
            collection.SetLastLog(log_text);
        } 
        /* mood */
        else if (input.size() >= 2 && input.at(0) == "mood") {
            string mood_text = "";
            mood_text += input.at(1);
            for (size_t i = 2; i < input.size(); i++) {
                mood_text += " ";
                mood_text += input.at(i);
            }
            collection.SetMood(mood_text);
        }
        /* weath */
        else if (input.size() >= 2 && input.at(0) == "weath") {
            string weath_text = "";
            weath_text += input.at(1);
            for (size_t i = 2; i < input.size(); i++) {
                weath_text += " ";
                weath_text += input.at(i);
            }
            collection.SetWeather(weath_text);
        }
        /* day */
        else if (input.size() >= 2 && input.at(0) == "day") {
            string day_text = "";
            day_text += input.at(1);
            for (size_t i = 2; i < input.size(); i++) {
                day_text += " ";
                day_text += input.at(i);
            }
            collection.SetDay(day_text);
        }
        /* undo */
        else if (input.size() == 1 && input.at(0) == "undo") {
            collection.Undo();
        }

        /* quit */
        // stop the entire program
        else if (input.size() == 1 && (input.at(0) == "q" || input.at(0) == "quit")) {
            return 0;
        }

        // invalid imput form user
        else {
            std::cout << "Didn't catch you there. Type \"help\" if you are lost :)" << std::endl;
            continue;
        }


        // 


        // collection.Add(10, "Ǥ", "HARRAAYYYYYYY!!!!");
        // collection.Add(10, "Ǥ", "HARRAAYYYYYYY!!!!");
        
        
        // lastly, always print it out. 
        collection.ToString();
        collection.SaveAllFiles();
    }
}






