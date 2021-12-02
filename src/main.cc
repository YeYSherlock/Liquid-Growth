#include "vase.hpp"
#include "shiny.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#define print(s) std::cout << s << std::endl;



int main() {


    Vase vase(0, 11, 18, 2021, "Thursday", "Superb!", "Sunny");
    vase.addShiny(10, "Ѿ", "finished laundry");
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


    vase.ToString();
    vase.SaveFile();

    Vase vase_l(0);
    vase_l.LoadFile("11_18_2021");
    vase_l.ToString();
    
    
}


/*


[Menu]
+ next     >> check vase of the next day
+ prev     >> check vase of the previous day
+ add #    >> add entry (only allowed for today)
+ undo     >> undo last entry (only allowed for today)
+ log @    >> add text to log.
+ day @    >> change day
+ mood @   >> change mood
+ weat @   >> change weather
+ cd @/@/@ >> check vase of the day   


*/





