#include <string>
#include <set>
#include <utility>
#ifndef PROJECT1_STARTER_CODE_RELATION_H
#define PROJECT1_STARTER_CODE_RELATION_H
#include "Header.h"
#include "Tuple.h"
#include "Rule.h"

class Relation {
public:
    Relation(){header = new Header();}
    Relation(std::string namePass, std::vector<std::string> headerPass);
    Relation(std::string namePass, Header *headerPass);
    Relation(std::string namePass);

    Relation SelectOne(int index, std::string value);
    Relation SelectTwo (int inde1, int index2);
    Relation Project(std::vector<int> intMarker);
    Relation Rename(std::vector<std::string> newNames);

    Relation Join(Relation otherRelation);
        Header* CombineHeaders(Relation& otherRelation);
        Header* SetHeader(Header* newHeader){return header = newHeader;}
        bool IsJoinable(Tuple t1, Tuple t2);
        Tuple CombineTuples(Tuple t1, Tuple t2);
    std::vector<int> ProjectRule(std::vector<Parameter> headPredVals);
    bool Unionize(Relation otherRelation);

    std::set<Tuple> GetTuples();
    void SetRelName(std::string newName){name = newName;}
    Header* GetHeader(){return header;}
    void AddTuple(Tuple newTuple);
    int GetTupleInt(){return tuples.size();}
    std::string ReturnRelationName(){return name;}
    void ToStringQuery();
    void ToStringRule();

private:
    std::string name;
    Header* header; //just a vector of strings (list of attribute names)
    std::set<Tuple> tuples; //not vectors!! (list of attribute values)
    std::vector <std::pair<int,int>> matchingAttributes; // 1st int is in result, 2nd is in relation that you pass in
};

#endif //PROJECT1_STARTER_CODE_RELATION_H
