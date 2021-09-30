#include "Token.h"
#include <iostream>
#include <sstream>
#include <string>

Token::Token(TokenType type, std::string description, int line) {
    itemType = type;
    tokenValue = description;
    tokenLine = line;
}

// prepping values for output
std::string Token::ToString() {
    std::ostringstream returnType;
    returnType << "(" << TypeToString(itemType) << ",\"" << tokenValue/*.substr(0,valueLength*/ << "\"," << tokenLine << ")";
    return returnType.str();
}

std::string Token::TypeToString(TokenType itemType) {
    switch (itemType) {
        case TokenType::COMMA:          return "COMMA"; break;
        case TokenType::PERIOD:         return "PERIOD"; break;
        case TokenType::Q_MARK:         return "Q_MARK"; break;
        case TokenType::LEFT_PAREN:     return "LEFT_PAREN"; break;
        case TokenType::RIGHT_PAREN:    return "RIGHT_PAREN"; break;
        case TokenType::COLON:          return "COLON"; break;
        case TokenType::COLON_DASH:     return "COLON_DASH"; break;
        case TokenType::MULTIPLY:       return "MULTIPLY"; break;
        case TokenType::ADD:            return "ADD";
        case TokenType::SCHEMES:        return "SCHEMES"; break;
        case TokenType::FACTS:          return "FACTS"; break;
        case TokenType::RULES:          return "RULES"; break;
        case TokenType::QUERIES:        return "QUERIES"; break;
        case TokenType::COMMENT:        return "COMMENT"; break;
        case TokenType::UNDEFINED:      return "UNDEFINED"; break;
        case TokenType::ENDOFFILE:      return "EOF"; break;
        case TokenType::STRING:         return "STRING"; break;
        case TokenType::ID:             return "ID"; break;
    }
    return "ERROR"; // a string MUST be returned by the end
    //return std::string();
}
//converting item types to strings for ToString function

