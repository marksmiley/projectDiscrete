#include "Rule.h"
#include <sstream>
#include <iostream>

Rule::Rule(Predicate copyHeadPredicate, std::vector<Predicate*> copyPredicates){
    headPredicate = copyHeadPredicate;
    for (int i = 0; i < (int)copyPredicates.size(); ++i){
        bodyPredicates.push_back(copyPredicates.at(i));
    }
}

std::string Rule::ToString() {
    std::stringstream returnString;
    returnString << headPredicate.ToString(headPredicate) << " :- ";
    for (int i = 0; i < (int)bodyPredicates.size(); i++){
        if (i != (int)bodyPredicates.size() -1) {
            returnString << bodyPredicates.at(i)->ToString(*bodyPredicates.at(i)) << ",";
        }
        else {
            returnString << bodyPredicates.at(i)->ToString(*bodyPredicates.at(i)) << ".";
        }
    }
    return returnString.str();
}