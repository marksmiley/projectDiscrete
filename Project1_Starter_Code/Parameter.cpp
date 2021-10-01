//
// Created by Marcus Smiley on 9/30/21.
//

#include "Parameter.h"
#include <string>

//josh had some sort of for-loop in this.  who knows why
Parameter::Parameter() {}

Parameter::Parameter(std::string input) {
    p = input;
}

std::string Parameter::ToString(Parameter parameter) {
    return p;
}