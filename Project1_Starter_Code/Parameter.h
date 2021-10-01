//
// Created by Marcus Smiley on 9/30/21.
//

#ifndef PROJECT1_STARTER_CODE_PARAMETER_H
#define PROJECT1_STARTER_CODE_PARAMETER_H
#include <string>

class Parameter {
public:
    Parameter();
    Parameter(std::string input);
    std::string p;
    std::string ToString(Parameter parameter);
};


#endif //PROJECT1_STARTER_CODE_PARAMETER_H
