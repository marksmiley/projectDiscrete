//
// Created by Marcus Smiley on 9/30/21.
//

#include "Predicate.h"

Predicate::Predicate(std::string predID, std::vector<Parameter> predParameters) {
    initID = predID;
    for (int i = 0; i < predParameters.size(); i++){
        parameters.push_back(predParameters.at(i));
    }
}

std::string Predicate::getInitId() {
    return initID;
}

void Predicate::setInitId(const std::string &initId) {
    initID = initId;
}
