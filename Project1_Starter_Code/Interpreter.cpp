#include "Interpreter.h"
#include <iostream>

Interpreter::Interpreter(DatalogProgram DPpassalong){
this->database = new Database();
std::vector <Predicate*> schemeVec = DPpassalong.ReturnSchemes();
std::vector <Predicate*> factVec = DPpassalong.ReturnFacts();
std::vector <Predicate*> queryVec = DPpassalong.ReturnQueries();
std::vector <Rule*> ruleVec = DPpassalong.ReturnRules();

    //evaluating schemes
    for (unsigned int i = 0; i < schemeVec.size(); ++i){
        EvaluateSchemes(schemeVec.at(i)->getInitId()/*name*/,schemeVec.at(i)->GetParamValues(schemeVec.at(i)->getParameters()));
    }

    //Evaluating facts
    for (unsigned int i = 0; i < factVec.size(); ++i){
        EvaluateFacts(factVec.at(i)->GetParamValues(factVec.at(i)->getParameters()), factVec.at(i)->getInitId());
        }

    //evaluating rules
    EvaluateRules(ruleVec);

    //evaluating queries
    for(unsigned int i = 0; i < queryVec.size(); ++i){
        Relation newRelation = EvaluatePredicate(queryVec.at(i));
        //std::cout << std::endl << "Query Evaluation" << std::endl;
        std::cout << queryVec.at(i)->ToString(*queryVec.at(i)) << "? ";
        newRelation.ToStringQuery();
    }
}


void Interpreter::EvaluateSchemes(std::string name, std::vector<std::string> newHeader ) {
    database->GetMap().insert({name, new Relation(name,newHeader)});
}

void Interpreter::EvaluateFacts(std::vector<std::string> tuplePass, std::string key) {
    Tuple newTuple(tuplePass);
    database->GetMap()[key]->AddTuple(newTuple);
}

 Relation Interpreter::EvaluatePredicate(Predicate *predicate) {
    Relation newRelation = *database->GetMap()[predicate->getInitId()];
    std::vector<std::string> predVals = predicate->GetParamValues(predicate->getParameters());
    std::map <std::string, int> valueMarker;
    std::vector<int> intMarker;
    std::vector<std::string> stringMarker;
    //The select portion of EvaluatePredicate
    for (unsigned int i = 0; i < predVals.size(); i++){
        if(predVals.at(i)[0] == '\''){//if it's a constant
            newRelation = newRelation.SelectOne(i, predVals.at(i));
        }
        else {
            std::map<std::string, int>::iterator it = valueMarker.find(predVals.at(i)); //if it's a variable
            if (it == valueMarker.end()){//if we haven't seen it b4, store the values
                valueMarker.insert({predVals.at(i),i});
                intMarker.push_back(i);
                stringMarker.push_back(predVals.at(i));
            }
            else{// if we have seen it before
                newRelation = newRelation.SelectTwo( it->second , i);
            }
        }
    }
    newRelation = newRelation.Project(intMarker);
    newRelation = newRelation.Rename(stringMarker);
    return newRelation;
}

void Interpreter::EvaluateRules(std::vector<Rule*> ruleVec){
    int preCount = 0; //counting ALL tuples in my database
    int postCount = 0; // count all tuples at the end of the algorithm to check against
    int numPasses = 0;

    std::cout << "Rule Evaluation" << std::endl;
    do{
        preCount = database->Count();
        for (unsigned int i = 0; i < ruleVec.size(); ++i) {
            if (i == 0) {
                //std::cout << std::endl;
                std::cout << ruleVec.at(i)->ToString();
                std::cout << std::endl;
            }
            else {
                //std::cout << std::endl;
                std::cout << ruleVec.at(i)->ToString();
                //std::cout << std::endl;
            }
            EvaluateRule(ruleVec.at(i));
        }
        ++numPasses;
        postCount = database->Count();
    }

    while(preCount != postCount);
    std::cout << std::endl << "Schemes populated after " << numPasses << " passes through the Rules." << std::endl << std::endl;

}

void Interpreter::EvaluateRule(Rule *rule){
    std::vector<Relation> relations; //create a vector of relations
    Predicate headPred = rule->GetHeadPredicate(); //create a head predicate
    std::vector<Predicate*> rightPreds = rule->GetBodyPredicates(); //create a vector of right-side predicates

    for (unsigned int i = 0; i < rightPreds.size(); i++){//create loop and evaluate the predicate
        relations.push_back(EvaluatePredicate(rightPreds.at(i)));
    }
    Relation result;
    if (relations.size() != 1) {
        for (unsigned int i = 0; i < relations.size() - 1; ++i) {
            if (i == 0) {
                result = relations.at(i).Join(relations.at(i + 1));
            } else {
                result = result.Join(relations.at(i + 1));
            }
        }
    }
    else {
        result = relations.front();
        //result.ToStringRule();
    }
    result = result.Project(result.ProjectRule(rule->GetHeadPredicate().getParameters()));
    result.SetRelName(rule->GetHeadPredicate().getInitId());
    database->GetMap()[result.ReturnRelationName()]->Unionize(result);
}