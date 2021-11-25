//
// Created by Marcus Smiley on 10/21/21.
//
#include <vector>
#include <string>
#ifndef PROJECT1_STARTER_CODE_TUPLE_H
#define PROJECT1_STARTER_CODE_TUPLE_H


class Tuple {
public:
    Tuple(){}
    Tuple(std::vector <std::string> tuplePass);
    std::string GetTuple(int index);
    void SetTuple(std::string addString);
    void AddToTuple(std::string tupleToBeAdded){tuple.push_back(tupleToBeAdded);}
    Tuple ProjectTuple(std::vector<int> indices);
    int GetValueIndex();
    void ToString();
    int GetTupleSize(){return tuple.size();}
    bool operator< (const Tuple &rhs) const {
        return tuple < rhs.tuple;}
private:
    std::vector <std::string> tuple;
};


#endif //PROJECT1_STARTER_CODE_TUPLE_H
