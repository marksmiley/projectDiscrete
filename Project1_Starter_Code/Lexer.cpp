#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "Q_MarkAutomaton.h"
#include "Left_ParenAutomaton.h"
#include "Right_ParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "Facts.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "CommentAutomata.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "Automaton.h"
#include <iostream>
#include <cctype>
#include <sstream>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
    // Don't forget you still got to look at the newLines
}

void Lexer::CreateAutomata() {
    automata.push_back(new CommaAutomaton());
    automata.push_back(new CommentAutomata());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new Q_MarkAutomaton());
    automata.push_back(new Left_ParenAutomaton());
    automata.push_back(new Right_ParenAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new IDAutomaton());


}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;

    while (input.size() > 0) {
        int maxRead = 0;
        Automaton *maxAutonama = automata.at(0);

        /* Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        foreach automaton in automata {
                inputRead = automaton.Start(input)
                if (inputRead > maxRead) {
                    set maxRead to inputRead
                    set maxAutomaton to automaton
                }
        }
        */ //pseudo code for parallel algorithm

        for (int i = 0; i < (int)automata.size(); ++i) {
            while (input.substr(0, 1) == "\n") {
                ++lineNumber;
                input = input.substr(1);} // Finds and erases newlines and increments LineNumber
                for (int i = 0; i < (int)input.size(); ++i){
                if (isspace(input[0]) && input[0] != '\n') {
                    input.erase(0, 1);}} // Finds and erases spaces
            int inputRead = automata.at(i)->Start(input);
                if (inputRead > maxRead) {
                    maxRead = inputRead;
                    maxAutonama = automata.at(i);
                }
            }

            if (maxRead > 0 && !isdigit(input[0])) {

                Token *newToken = maxAutonama->CreateToken(input.substr(0, maxRead), lineNumber);
                lineNumber += maxAutonama->NewLinesRead();
                newToken->ToString();
                if (newToken->ReturnType() != TokenType::COMMENT){ //Here the code is checking and eliminating comment tokens from the list
                    tokens.push_back(newToken);
                }
            }

            else if (input.size() > 0){
                maxRead = 1;
                tokens.push_back(new Token(TokenType::UNDEFINED, input.substr(0, 1), lineNumber));
            }

            input.erase(0, maxRead);
        }

        tokens.push_back(new Token (TokenType::ENDOFFILE, "", lineNumber));

        //std::cout << "Total Tokens = " << tokens.size();
    }

std::string Lexer::ToString() {
    std::ostringstream returnType;
    for (long unsigned int i = 0; i < tokens.size(); ++i){
        returnType << tokens.at(i)->ToString() << std::endl;}
    returnType << "Total Tokens = " << tokens.size();
    return returnType.str();
}