#include "Token.h"
#include "Predicate.h"
#include "Parameter.h"
#include <vector>

#ifndef PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
#define PROJECT1_STARTER_CODE_DATALOGPROGRAM_H


class DatalogProgram {
public:
    DatalogProgram(std::vector<Token*> allTokens);
    bool Match(TokenType currToken, TokenType requiredToken);
    void DatalogProgramInit();
    void SchemeList();
    void FactList();
    void RuleList();
    void QueryList();
    void Scheme();
    void Fact();
    void Rule();
    void Query();
    void HeadPredicate();
    void ParsePredicate();
    void PredicateList();
    void ParameterList();
    void StringList();
    void IdList();
    void Parameter();

private:
    std::vector<Token*> tokens;
    int index = 0;
    std::vector<Predicate> pschemes;
    std::vector<Predicate> pquery;
    std::vector<Predicate> pfacts;
    //std::vector<Parameter> parameters;
};
#endif //PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
