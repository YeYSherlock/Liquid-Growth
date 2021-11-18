#include "vase.hpp"
#include "shiny.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#define print(s) std::cout << s << std::endl;



int main() {


    
    srand((unsigned) time(0));
    for (int i = 0; i < 100; i++) {
        print(rand()%9);
    }


    vase vase(0);

    for (size_t i = 0; i < vase.stamnos.size(); i++) {
        for (size_t j = 0; j < vase.stamnos.at(i).size(); j++) {
            std::cout << vase.stamnos.at(i).at(j);
        }
        std::cout << std::endl;
    }








   // Testing
   /*
   vase vase(2);
   for(size_t i = 0; i < vase.kalathos.size(); i++) {
        for(size_t j = 0; j < vase.kalathos[i].size(); j++) {
            std::cout << vase.kalathos[i][j];
        }
        std::cout << std::endl;
    }
    */

   //Testing Shiny
    // Shiny* piece = new Shiny("Piece", 10, 'p');
    // std::cout <<  piece->ShinyCharacter << " " << piece->ShinyName << " " << piece->ShinySize <<std::endl;






    
}








