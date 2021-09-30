//
// Created by Marcus Smiley on 9/16/21.
//

#include "StringAutomaton.h"
#include <cctype>

void StringAutomaton::S0(const std::string& input){
    if (input[index] == '\''){
        ++inputRead;
        ++index;
        S1(input);
    }
}
void StringAutomaton::S1(const std::string& input){
    if (index == (int)input.size() - 1){
        ++inputRead;
        if(input[index] == '\n'){
            ++newLines;}
        type = TokenType::UNDEFINED;
        return;
    }
    if (input[index] == '\''){
        ++inputRead;
        ++index;
        S2(input);
    }
    else {
        if(input[index] == '\n'){
            ++newLines;
        }
        ++inputRead;
        ++index;
        S1(input);
    }

}

void StringAutomaton::S2(const std::string&input){

    if (input[index] == '\''){
        ++inputRead;
        ++index;
        S1(input);
    }
    else {return;}
}
