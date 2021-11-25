#include "DatalogProgram.h"
#include "Database.h"
#include <vector>
#ifndef PROJECT1_STARTER_CODE_INTERPRETER_H
#define PROJECT1_STARTER_CODE_INTERPRETER_H

class Interpreter {
public:
Interpreter()= default;
Interpreter(DatalogProgram DPpassalong);
void EvaluateSchemes(std::string name, std::vector<std::string> newHeader);
void EvaluateFacts(std::vector<std::string> tuplePass, std::string key);
//make a function in the interpreter that evaluates ONE query predicate and returns a relation:
Relation EvaluatePredicate (Predicate *predicate);
void EvaluateRule(Rule *rule);
//make a function that calls the above function as many times as necessary
private:
    DatalogProgram datLog;
    Database *database;
};

#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
