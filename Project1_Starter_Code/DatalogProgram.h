#include "Token.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"
#include <vector>
#include <set>

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
    void ParseRule();
    void Query();
    void HeadPredicate(Predicate &headPredicate);
    Predicate* ParsePredicate(std::string &initId);
    void PredicateList();
    void ParameterList();
    void StringList();
    void IdList();
    void parameter();
    std::string ToString();

private:
    std::vector<Token*> tokens;
    int index = 0;
    std::vector<Predicate*> pschemes;
    std::vector<Predicate*> pquery;
    std::vector<Predicate*> pfacts;
    std::vector<Predicate*> pRules;
    std::vector<Rule*> ruleVector;
    std::vector<Parameter> tempParameters;
    std::set<std::string> domain;
};
#endif //PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
