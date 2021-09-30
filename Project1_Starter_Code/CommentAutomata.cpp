//
// Created by Marcus Smiley on 9/16/21.
//

#include "CommentAutomata.h"
void CommentAutomata:: S0(const std::string& input) {
    if (input[index] == '#') {
        //std::cout << input.size() << std::endl;
        ++inputRead;
        ++index;
        S1(input);
    }
}

void CommentAutomata:: S1(const std::string &input) {
       if (input[index] == '|') {
           ++inputRead;
           ++index;
           S3(input);
       }
       else {
           S2(input);
       }
}

void CommentAutomata:: S2(const std::string &input){
    if (input[index] == '\n'){ //How do we make it end with ENDOFFILE?
        //++newLines;
        return;
    }
    else {
        ++inputRead;
        ++index;
        S2(input);
    }
}

void CommentAutomata:: S3(const std::string &input){
    if( input[index] =='\n'){
        while(input[index] == '\n') {
            ++newLines;
            ++inputRead;
            ++index;
        }
    } //Checking for newline
    if (index == (int) input.size()) {
        ++inputRead;
        ++index;
        type = TokenType::UNDEFINED;
        return;
    } // checking for eof

    if (input[index] == '|'){
        ++inputRead;
        ++index;
        S4(input);
    }
    else if (input[index] ){
        ++inputRead;
        ++index;
        S3(input);
        return;
    }
}

void CommentAutomata:: S4(const std::string &input){
    if(input[index] =='\n'){
        ++newLines;
        ++inputRead;
        ++index;
        S3(input);
    }
    if (index == (int) input.size()) {
        ++inputRead;
        type = TokenType::UNDEFINED;
        return;
    }
    if (input[index] == '|'){
        ++inputRead;
        ++index;
        S4(input);
    }
    else if (input[index] == '#'){
        ++inputRead;
        ++index;
        //S5(input);
        return;
    }
    else {
        ++inputRead;
        ++index;
        S3(input);

    }
}



/*int CommentAutomata::Start(const std::string& input){
    inputRead = 0;
    index = 0;
    S0(input);
    return inputRead;
}
void CommentAutomata::S0(const std::string& input){
    newLines = 0;
    if(input[this->index] == '#'){
        buildingComment = true;
        ++inputRead;
        ++index;
        S1(input);
    }
    else{
        Serr();
    }
}

void CommentAutomata::S1(const std::string &input) {
    if(input[index] == '|'){
        buildingComment = true;
        ++inputRead;
        ++index;
        S2(input);
    }
    else{
        buildingComment = false;
        Serr();
    }
}

void CommentAutomata::S2(const std::string &input) {
    while(buildingComment == true){
        if(index == input.size()){
            Serr();
            break;
        }
        if(input[index] == '\n'){
            ++newLines;
            ++index;
            ++inputRead;
        }
        else if(input[index] != '|'){
            ++index;
            ++inputRead;
        }
        else{ //meaning it DOES hit '|' //
            ++index;
            ++inputRead;
            S3(input);
        }
    }
}

void CommentAutomata::S3(const std::string &input) {
    if(input[index] == '#'){
        ++index;
        ++inputRead;
        buildingComment = false;
        return;
    }
    else{
        if(input[index] == '\n'){
            ++newLines;
//            ++index;
//            ++inputRead;
        }
        ++index;
        ++inputRead;
        return;
    }
}


*/
