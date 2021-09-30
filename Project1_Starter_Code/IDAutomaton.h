//
// Created by Marcus Smiley on 9/16/21.
//

#ifndef PROJECT1_STARTER_CODE_IDAUTOMATON_H
#define PROJECT1_STARTER_CODE_IDAUTOMATON_H
#include "Automaton.h"

class IDAutomaton : public Automaton{
public:

    IDAutomaton (): Automaton(TokenType::ID) {}
    void S0(const std::string& input);
    void S1(const std::string &input);

};

#include "Automaton.h"
#endif //PROJECT1_STARTER_CODE_IDAUTOMATON_H
