//
// Created by Marcus Smiley on 10/21/21.
//

#include "Tuple.h"
#include <iostream>

Tuple::Tuple(std::vector <std::string> tuplePass){
    for (unsigned int i = 0; i < tuplePass.size(); i++){
        tuple.push_back(tuplePass.at(i));
    }
}

std::string Tuple::GetTuple(int index) {
    return tuple.at(index);
}

void Tuple::SetTuple(std::string addString){
    tuple.push_back(addString);
}

Tuple Tuple::ProjectTuple(std::vector<int> indices) {
    std::vector<std::string> newTuple;
    for(unsigned int i = 0; i < indices.size(); ++i) {
        newTuple.push_back(tuple.at(indices.at(i)));
    }
    return Tuple(newTuple); // seg fault after 37 iterations
}

void Tuple::ToString() {
   // std::cout << tuple;
}