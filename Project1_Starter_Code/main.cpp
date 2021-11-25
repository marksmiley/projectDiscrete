#include "Lexer.h"
#include "Token.h"
#include "DatalogProgram.h"
#include "Interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>



int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();

// check command line arguments
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " input_file" << std::endl;
        return 1;
    }

// open file
    std::string fileName = argv[1];
    std::ifstream input(fileName);
    if (!input.is_open()) {
        std::cout << "File " << fileName << " could not be found or opened." << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << input.rdbuf();
    std::string inputString = buffer.str();

    Lexer proj1;
    proj1.Run(inputString);
    std::vector<Token*> tokenList = proj1.ReturnTokens();
    //std::cout << proj1.ToString() << std::endl;

    DatalogProgram nowThis(tokenList); // do something similar with the returned DatalogProgram

    try{
        nowThis.DatalogProgramInit();
    } catch(Token* error){
        std::cout << "Failure!" << std::endl << error->ToString();
        return 0;
    }
    //std::cout << "Success!" << std::endl;
    //std::cout << nowThis.ToString();

    Interpreter proj3(nowThis);
    //call interpreter and use nowThis as parameter
    //create constructor within interpreter to pass in values to a DatalogProgram object that can be manipulated in Interpreter

    delete lexer;
    return 0;

}


/*  Write a `toString` method for each of these classes so that you can easily print them out.
    Return a DatalogProgram object from the parser and then traverse this structure and use
    `toString` as needed to print the required output.

    To integrate this project with later projects, be sure to have a way to get the lists of schemes,
    facts, rules and queries out of the DatalogProgram.*/