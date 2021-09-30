#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COMMA,
    Q_MARK,
    PERIOD,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    COMMENT,
    STRING,
    ID,
    UNDEFINED,
    ENDOFFILE
};

class Token {

private:
    std::string tokenValue = "none";
    int tokenLine = 0;
    TokenType itemType = TokenType::UNDEFINED;


public:
    Token(TokenType type, std::string description, int line);
    std::string ToString();
    std::string TypeToString(TokenType itemType);
    TokenType ReturnType() {return itemType;}
    std::string ReturnValue(){return tokenValue;}
    int ReturnLine(){return tokenLine;}
};

#endif // TOKEN_H

