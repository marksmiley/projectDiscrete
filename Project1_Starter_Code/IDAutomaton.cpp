#include "IDAutomaton.h"
#include <iostream>
#include <string>

/*void IDAutomaton::S0(const std::string& input) {

    for (int j = 4; j <= 7; ++j) {
        if (input.substr(0, j) == "Schemes") {
            //std::cout << std::endl << "found Schemes" << std::endl;
            break;
        } else if (input.substr(0, j) == "Facts") {
            //std::cout << std::endl << "found Facts" << std::endl;
            break;
        } else if (input.substr(0, j) == "Rules") {
            //std::cout << std::endl << "found Rules" << std::endl;
            break;
        } else if (input.substr(0, j) == "Queries") {
            //std::cout << std::endl << "found Queries" << std::endl;
            break;
        } else {
            inputRead++;
            //Serr(); // the problem here is that it eventually reaches this statement no matter what
        }
    }

    if (isalpha(input[index] || isdigit(input[index]))) {
        inputRead++;
        index++;
    }
}
*/
#include "IDAutomaton.h"
#include <cctype>

void IDAutomaton::S0(const std::string &input) {
    if(isalpha(input[index])){
        index++;
        inputRead++;
        S1(input);
    }
    else{
        Serr();
    }
}

void IDAutomaton::S1(const std::string &input) {
    if(isalnum(input[index])){
        index++;
        inputRead++;
        S1(input);
    }
    else{}
}