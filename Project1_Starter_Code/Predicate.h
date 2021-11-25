#ifndef PROJECT1_STARTER_CODE_PREDICATE_H
#define PROJECT1_STARTER_CODE_PREDICATE_H
#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
public:
    Predicate(std::string PredID, std::vector<Parameter> predParameters);
    Predicate(){}
    std::string ToString(Predicate currPredicate);
    std::string getInitId();
    std::vector<Parameter> getParameters();
    std::vector <std::string> GetParamValues(std::vector<Parameter> paramVec);
    //create GetParamValues

private:
    std::string initID;
    std::vector<Parameter> parameters;

};


#endif //PROJECT1_STARTER_CODE_PREDICATE_H
