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

using std::stoi;

#define print(s) std::cout << s << std::endl;


int main() {
    // initialize interface, implement menu/etc later
    Collection collection(menu);


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

        /* AddAtDate */
        // build m d y which_vase
        if (input.size() == 5 && input.at(0) == "build") {
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
        /* Show Commands Available */
        else if (input.size() == 1 && input.at(0) == "help") {
            std::cout << std::endl << std::endl << std::endl;
            std::cout << "[Commands Available]" << std::endl;
            std::cout << " + build m d y >> add entry at specified day (year 4 number)" << std::endl;
            std::cout << " + cd m d y    >> check vase of the day" << std::endl;
            std::cout << " + add # U T   >> add num unicode log_text" << std::endl;
            std::cout << " + next        >> check vase of the next day" << std::endl;
            std::cout << " + prev        >> check vase of the previous day" << std::endl;
            std::cout << " + log @       >> add text to log." << std::endl;
            std::cout << " + mood @      >> change mood" << std::endl;
            std::cout << " + weath @     >> change weather" << std::endl;
            std::cout << " + undo        >> undo last entry (only allowed for today)" << std::endl;
            continue;
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
        else if (input.size() >= 2 && input.at(0) == "log") {

        }
        /* weath */
        /* undo */


        else {
            std::cout << "Didn't catch you there. Type \"help\" if you are lost :)" << std::endl;
            continue;
        }


        // 


        // collection.Add(10, "Ǥ", "HARRAAYYYYYYY!!!!");
        // collection.Add(10, "Ǥ", "HARRAAYYYYYYY!!!!");
        
        
        // lastly, always print it out. 
        collection.ToString();
    }








    // 1. load all data from saved files
    // 2. 


    // Vase vase(0, 11, 18, 2021, "Thursday", "Superb!", "Sunny");
    // vase.addShiny(10, "Ѿ", "finished laundry");
    // vase.addShiny(9, "Ǥ", "changed schedule: Math 416");
    // vase.addShiny(18, "Ѯ", "Worked on TRA");
    // vase.addShiny(29, "Ф", "Finished TRA");
    // vase.addShiny(16, "Ѻ", "Working on Final Project");
    // vase.addShiny(10, "Ѿ", "Final Project Presentation Prep");
    // vase.addShiny(9, "Ǥ", "changed schedule: Math 416");
    // vase.addShiny(9, "Ѯ", "changed schedule: Math 416");
    // vase.addShiny(9, "Ф", "changed schedule: Math 416");
    // vase.addShiny(9, "Ѻ", "changed schedule: Math 416");
    // vase.addShiny(10, "Ѿ", "finished laundry");
    // vase.addShiny(9, "Ǥ", "changed schedule: Math 416");
    // vase.addShiny(9, "Ѯ", "changed schedule: Math 416");
    // vase.addShiny(9, "Ф", "changed schedule: Math 416");
    // vase.addShiny(9, "Ѻ", "changed schedule: Math 416");
    // vase.addShiny(9, "Ǥ", "changed schedule: Math 416");
    // vase.addShiny(9, "Ѯ", "changed schedule: Math 416");
    // vase.addShiny(9, "Ф", "changed schedule: Math 416");
    // vase.addShiny(9, "Ѻ", "changed schedule: Math 416");
    // vase.addShiny(10, "Ѿ", "finished laundry");
    // vase.addShiny(9, "Ǥ", "changed schedule: Math 416");
    // vase.addShiny(9, "Ѯ", "changed schedule: Math 416");
    // vase.addShiny(9, "Ф", "changed schedule: Math 416");
    // vase.addShiny(9, "Ѻ", "changed schedule: Math 416");
    /*
    vase.addShiny(40, "Ф", "25 minutes study block for CS");
    vase.addShiny(30, "Ѯ", "started TRA");
    vase.addShiny(36, "Ѻ", "finished TRA");
    vase.addShiny(8, "Ѿ", "project");
    vase.addShiny(20, "Ѯ", "25 minutes study block for Math");
    vase.addShiny(36, "Ѻ", "25 minutes study block for Math");
    vase.addShiny(30, "Ф", "25 minutes study block for Math");
    */


    // vase.ToString();
    // vase.SaveFile();

    // Vase vase_l(0);
    // vase_l.LoadFile("11_18_2021");
    // vase_l.ToString();
    
}


/*


[Menu]
+ touch @ @ @ # >> add a vase at that date
+ next     >> check vase of the next day
+ prev     >> check vase of the previous day
+ add #    >> add entry (only allowed for today)
+ undo     >> undo last entry (only allowed for today)
+ log @    >> add text to the last log.
+ day @    >> change day
+ mood @   >> change mood
+ weat @   >> change weather
+ cd @/@/@ >> check vase of the day   


*/





