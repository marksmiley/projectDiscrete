//
// Created by Marcus Smiley on 9/30/21.
//
#include <iostream>
#include <sstream>
#include "Predicate.h"

Predicate::Predicate(std::string predID, std::vector<Parameter> predParameters) {
    initID = predID;
    std::stringstream oss;
    for (int i = 0; i < predParameters.size(); i++){
        parameters.push_back(predParameters.at(i));
    }
}

std::string Predicate::getInitId() {
    return initID;
}

std::vector<Parameter> Predicate::getParameters()  {
    return parameters;
}

std::string Predicate::ToString(Predicate currPredicate){
    std::stringstream returnString;
    returnString << currPredicate.getInitId() << "(";
    for (int i = 0; i < parameters.size(); i++){
        if (i != parameters.size() - 1) {
            returnString << parameters.at(i).ToString(parameters.at(i)) << ",";
        }
        else {
            returnString << parameters.at(i).ToString(parameters.at(i)) << ")";
        }
    }
    return returnString.str();
}
