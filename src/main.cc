#include "vase.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#define print(s) std::cout << s << std::endl;



int main() {


    srand((unsigned) time(0));
    for (int i = 0; i < 100; i++) {
        print(rand()%6);
    }


    vase vase(0);

    for (size_t i = 0; i < vase.stamnos.size(); i++) {
        for (size_t j = 0; j < vase.stamnos.at(i).size(); j++) {
            std::cout << vase.stamnos.at(i).at(j);
        }
        std::cout << std::endl;
    }
}








