//
// Created by Marcus Smiley on 9/30/21.
//

#ifndef PROJECT1_STARTER_CODE_RULE_H
#define PROJECT1_STARTER_CODE_RULE_H
#include "Predicate.h"
#include <vector>

class Rule {
public:
    Rule(){}
    Rule(Predicate headPredicate, std::vector<Predicate*> copyPredicates);
    std::string ToString();

private:
    Predicate headPredicate;
    std::vector<Predicate*>bodyPredicates;
};

#endif //PROJECT1_STARTER_CODE_RULE_H