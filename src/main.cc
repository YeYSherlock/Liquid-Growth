#include "vase.hpp"
#include "shiny.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#define print(s) std::cout << s << std::endl;



int main() {


    
    // srand((unsigned) time(0));
    // for (int i = 0; i < 100; i++) {
    //     print(rand()%9);
    // }


    Vase vase(0);
    // vase.addShiny(5, "x", "hellooooo madam");
    // vase.addShiny(5, "O", "hellooooo madam");

    for (size_t i = 0; i < 20; i++) {
        for (size_t j = 0; j < 40; j++) {
            // if (vase.shinyAt(i, j) != " ") {
            //     std::cout << vase.shinyAt(i, j);
            // } else {
            //     std::cout << vase.vase_.at(i).substr(j, 1);
            // }
            std::cout << vase.vase_.at(i).substr(j, 1);

        }
        std::cout << std::endl;
    }





    
}








