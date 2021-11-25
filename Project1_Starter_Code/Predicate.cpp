//
// Created by Marcus Smiley on 9/30/21.
//
#include <iostream>
#include <sstream>
#include "Predicate.h"

Predicate::Predicate(std::string predID, std::vector<Parameter> predParameters) {
    initID = predID;
    std::stringstream oss;
    for (int i = 0; i < (int)predParameters.size(); i++){
        parameters.push_back(predParameters.at(i));
    }
}

std::string Predicate::getInitId() {
    return initID;
}

std::vector<std::string> Predicate::GetParamValues(std::vector<Parameter> paramVec){
    std::vector<std::string> stringVals;
    for (unsigned int i = 0; i < paramVec.size(); i++){
        stringVals.push_back(paramVec.at(i).ToString());
    }
    return stringVals;
}

std::vector<Parameter> Predicate::getParameters()  {
    return parameters;
}

std::string Predicate::ToString(Predicate currPredicate){
    std::stringstream returnString;
    returnString << currPredicate.getInitId() << "(";
    for (int i = 0; i < (int)parameters.size(); i++){
        if (i != (int)parameters.size() - 1) {
            returnString << parameters.at(i).ToString() << ",";
        }
        else {
            returnString << parameters.at(i).ToString() << ")";
        }
    }
    return returnString.str();
}
