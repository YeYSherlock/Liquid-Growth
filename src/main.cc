#include "vase.hpp"

#define print(s) std::cout << s << std::endl;



int main() {

    
    // vase_case vase_template;
    // for (size_t i = 0; i < vase_template.stamnos.size(); i++) {
    //     for (size_t j = 0; j < vase_template.stamnos.at(i).size(); j++) {
    //         std::cout << vase_template.stamnos.at(i).at(j);
    //     }
    //     std::cout << std::endl;
    // }

    vase vase;

    for (size_t i = 0; i < vase.stamnos.size(); i++) {
        for (size_t j = 0; j < vase.stamnos.at(i).size(); j++) {
            std::cout << vase.stamnos.at(i).at(j);
        }
        std::cout << std::endl;
    }
}








