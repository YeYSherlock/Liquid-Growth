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
// #include <filesystem>
#include <experimental/filesystem>
// #include <boost/filesystem.hpp>
// #include <boost/range/iterator_range.hpp>
#include <fstream>
#include <cstdio>

using std::stoi;
using std::cout; using std::cin;
using std::endl; using std::string;
// using std::filesystem::directory_iterator;
using std::experimental::filesystem::directory_iterator;
namespace fs = std::experimental::filesystem;
// using namespace boost::filesystem;


#define print(s) std::cout << s << std::endl;


/**
 * @brief main function.
 * @see collection.hpp shiny.hpp vase.hpp
 * @return int, 0 to terminate program. 
 * 
 */
int main() {

    // path p1{"---"};

    // initialize interface, implement menu/etc later
    Collection collection;

    // vec to save the to be loaded file names
    vector<string> saved_files_vec;
    
    // loading all files into saved_files_vec
    string path = "storage";

    // for (const auto & file : directory_iterator(path)) {
    //     if (!std::filesystem::is_empty(file)) {
    //         std::cout << "once" << std::endl;
    //         collection.AddAtDate(01, 01, 3000, 0);
    //     }

    // }

    // return 0;
    for (const auto & file : directory_iterator(path)) {
        if (!fs::is_empty(file)) {
            collection.AddAtDate(01, 01, 3000, 0);
            collection.CurrVase()->LoadFile(file.path());
        }

    }


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
    // std::cout << "   [type \"start\" to begin the journey]    " << std::endl;
    // std::cout << "     [type \"help\" to check commands]      " << std::endl;

    if (fs::is_empty(path)) {
        std::cout << "[You have no vases. Type \"build m d y V\" to build one!]    " << std::endl;
    } else {
        std::cout << "   [type \"start\" to begin the journey]    " << std::endl;
        std::cout << "     [type \"help\" to check commands]      " << std::endl;
    }

    while (true) {
        // record user input
        // vector<string> input;
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
            std::cout << " +                    Ex: build 12 31 2021 0" <<std::endl;
            std::cout << " + cd m d y      >> check vase of the day" << std::endl;
            std::cout << " +                    Ex: cd 12 31 2002" <<std::endl;
            std::cout << " + add n # T     >> add num unicode log_text" << std::endl;
            std::cout << " +                    Ex: add 10 $ Completed HW!" <<std::endl;
            std::cout << " + next          >> check vase of the next day" << std::endl;
            std::cout << " + prev          >> check vase of the previous day" << std::endl;
            std::cout << " + log @         >> add text to log." << std::endl;
            std::cout << " + mood @        >> change mood" << std::endl;
            std::cout << " + weath @       >> change weather" << std::endl;
            std::cout << " + undo          >> undo last entry" << std::endl;
            std::cout << " + quit          >> exit the program" << std::endl;
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
        
        // lastly, always print it out. 
        collection.ToString();

        // save files
        collection.SaveAllFiles();
    }




    
}





// /**
//  * @brief Here is a brief description. Remember that *markdown* is **enable**. This is in main.cc
//  * @note document the interface in the header. The Gory details of the how and why in the source.
//  * 
//  * @param a does something
//  * @param b does another thing
//  * @param c does the other thing
//  * @returns void
//  * 
//  * @see main() collection.hpp shiny.hpp vase.hpp
//  * @attention here is an attention
//  * @warning here is a warning
//  */
// void DoxygenReference(int a, int b, int c) {


    
}