#include <utility>
#include <iostream>
#include <map>
#include "Relation.h"

Relation::Relation(std::string namePass, std::vector<std::string> headerPass){ // for the function EvaluateSchemes
    name = namePass;
    header = new Header(headerPass);
    //tuples = tuplesPass;
}

Relation::Relation(std::string namePass, Header *headerPass){
    name = namePass;
    header = headerPass;
}

Relation::Relation(std::string namePass){
    name = namePass;
}

void Relation::AddTuple(Tuple newTuple) {
    tuples.insert(newTuple);
}

Relation Relation::SelectOne(int index, std::string value){ // for the functions Rename, Select, and Project
    Relation newRelation(name, header);
    for (auto elem : tuples){
        if (elem.GetTuple(index) == value){
            newRelation.AddTuple(elem);
        }
    }
    return newRelation;
}

Relation Relation::SelectTwo(int index1, int index2){
    Relation newRelation(name, header);
    for (auto elem : tuples){
        if (elem.GetTuple(index1) == elem.GetTuple(index2)){
            newRelation.AddTuple(elem);
        }
    }
    return newRelation;
}

std::set<Tuple> Relation::GetTuples() {
    return tuples;
}

Relation Relation::Project(std::vector<int> intMarker){
    //Add code that switches the order of the values in the header
    Header* newHeader = new Header();
    newHeader = newHeader->AddHeader2(intMarker, header);
    Relation newRelation = Relation(name, newHeader);
    for (Tuple elem : tuples) {
        Tuple newTuple;
        newTuple = elem.ProjectTuple(intMarker);
        newRelation.AddTuple(newTuple);
    }
    return newRelation;
}

std::vector<int> Relation::ProjectRule(std::vector<Parameter> headPredVals){
    std::vector<int> correctIndices;
    for (unsigned int i = 0; i < headPredVals.size(); ++i){
        for (int j = 0; j < header->HeaderSize(); ++j){
            if (headPredVals.at(i).ToString() == header->at(j)){
                correctIndices.push_back(j);
            }
        }
    }
    return correctIndices;
}

Relation Relation::Rename(std::vector<std::string> newNames){
    header->RenameHeader(newNames);
    Relation newRelation(name, header);
    for (auto elem : tuples){
        newRelation.AddTuple(elem);
    }
    return newRelation;
}

bool Relation::Unionize(Relation otherRelation){
    Relation newRelation;
    for (auto elem : otherRelation.tuples){
        if (tuples.insert(elem).second) {
            AddTuple(elem);
            for ( int i = 0; i < header->HeaderSize(); ++i) {
                if (i==0) {
                    std::cout << "  " << header->at(i) << "=" << elem.GetTuple(i);
                    if(header->HeaderSize()==1){
                        std::cout << std::endl;
                    }
                }
                else{
                    std::cout << ", " << header->at(i) << "=" << elem.GetTuple(i);
                    if (i == header->HeaderSize()-1){
                        std::cout << std::endl;
                    }
                }
            }
            //std::cout << std::endl;
        }
    }
    return true;
}

Relation Relation::Join(Relation otherRelation){
    Relation newRelation;
    newRelation.SetHeader(CombineHeaders(otherRelation)); // add the header to the relation
    for (auto elem1 : tuples) {
        for (auto elem2: otherRelation.tuples) {
            if (IsJoinable(elem1, elem2)) {
                newRelation.AddTuple(CombineTuples(elem1,elem2));
            }
        }
    }
    return newRelation;
}

bool Relation::IsJoinable(Tuple t1, Tuple t2){
    if (!matchingAttributes.empty()){
        for (unsigned int i = 0; i < matchingAttributes.size(); ++i){
            if (t1.GetTuple(matchingAttributes.at(i).first) != t2.GetTuple(matchingAttributes.at(i).second)){
                return false;
            }
        }
    }
    return true;
}

Header* Relation::CombineHeaders(Relation& otherRelation){
    Header* newHeader = header;
    unsigned int headerSize = otherRelation.GetHeader()->HeaderSize();
    for (unsigned int i = 0; i < headerSize; ++i){
        bool attributeMatch = false;
        for (int j = 0; j < newHeader->HeaderSize(); ++j){
            if (otherRelation.GetHeader()->at(i)==newHeader->at(j)){ //Loading the matchingAttributes data member
                attributeMatch = true;
                matchingAttributes.push_back(std::make_pair(j,i));
            }
        }
        if (!attributeMatch){
            newHeader->AddAttribute(otherRelation.header->at(i));
        }
    }
    std::cout << std::endl;
    return newHeader;
}

Tuple Relation::CombineTuples(Tuple t1, Tuple t2) {
    Tuple newTuple = t1;
    for (int i = 0; i < t2.GetTupleSize(); ++i) {
        bool isMatch = false;
        for (int j = 0; j < int(matchingAttributes.size()); ++j) {
            if (matchingAttributes.at(j).second == i) {
                isMatch = true;
            }
        }
        if(!isMatch){
            newTuple.AddToTuple(t2.GetTuple(i));
        }
    }
    return newTuple;
}
//newTuple.AddToTuple(t2.GetTuple(i));

void Relation::ToStringQuery() {
    if (tuples.empty()) {
        std::cout << "No" << std::endl;
    } else {
        std::cout << "Yes(" << tuples.size() << ")" << std::endl;
        for (auto elem : tuples){
            for (int i = 0; i < header->HeaderSize(); ++i){
                if(i==0){
                    std::cout << "  " << header->at(i) << "=" << elem.GetTuple(i);
                    if(header->HeaderSize()==1){
                        std::cout << std::endl;
                    }
                }
                else{
                    std::cout << ", " << header->at(i) << "=" << elem.GetTuple(i);
                    if(i == header->HeaderSize()-1) {
                        std::cout << std::endl;
                    }
                }
            }
        }
    }
}

void Relation::ToStringRule() {
    for (auto elem : tuples){
        for (int i = 0; i < header->HeaderSize(); ++i){
            if(i==0){
                std::cout << "  " << header->at(i) << "=" << elem.GetTuple(i);
                if(header->HeaderSize()==1){
                    std::cout << std::endl;
                }
            }
            else{
                std::cout << ", " << header->at(i) << "=" << elem.GetTuple(i);
                if(i == header->HeaderSize()-1) {
                    std::cout << std::endl;
                }
            }
        }
    }
}


