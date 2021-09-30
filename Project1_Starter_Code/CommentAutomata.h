//
// Created by Marcus Smiley on 9/16/21.
//

#ifndef PROJECT1_STARTER_CODE_COMMENTAUTOMATA_H
#define PROJECT1_STARTER_CODE_COMMENTAUTOMATA_H

#include "Automaton.h"

class CommentAutomata : public Automaton {
private:

public:
    CommentAutomata(): Automaton(TokenType::COMMENT) {}

    void S0(const std::string& input);
    void S1(const std::string &input);
    void S2(const std::string &input);
    void S3(const std::string &input);
    void S4(const std::string &input);
};
#endif //PROJECT1_STARTER_CODE_COMMENTAUTOMATA_H





/*
    CommentAutomata(): Automaton(TokenType::COMMENT) {}
    void S0(const std::string& input);
    void S1(const std::string &input);
    void S2(const std::string &input);
    void S3(const std::string &input);
    void S4(const std::string &input);
    void S5(const std::string &input);

};


*/