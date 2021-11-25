#include "Header.h"

Header::Header(std::vector<std::string> headerPass){
    for (unsigned int i = 0; i < headerPass.size(); i++){
        headerVec.push_back(headerPass.at(i));
    }
}

void Header::AddHeader(int index, Header* oldHeader) {
    headerVec.push_back(oldHeader->at(index));
}

std::string Header::at(int index){
    return headerVec.at(index);
}

void Header::AddAttribute(std::string addedAttribute) {
    return headerVec.push_back(addedAttribute);
}

Header* Header::AddHeader2(std::vector<int> intMarker, Header* oldHeader) {
    Header* newHeader = new Header();
    for (unsigned int i = 0; i < intMarker.size(); ++i) {
        newHeader->AddHeader(intMarker.at(i), oldHeader);
    }
    return newHeader;
}

void Header::RenameHeader(std::vector<std::string> newNames){
    headerVec = newNames;
}
