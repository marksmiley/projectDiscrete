#include <vector>
#include <string>
#include <utility>
#ifndef PROJECT1_STARTER_CODE_HEADER_H
#define PROJECT1_STARTER_CODE_HEADER_H


class Header {
public:
    Header(){}
    Header(std::vector <std::string> headerPass);
    void AddHeader(int index, Header* oldHeader);
    Header* AddHeader2(std::vector<int> intMarker, Header* oldHeader);
    void AddAttribute(std::string addedAttribute);
    std::vector<std::string> ReturnHeaderVec() {return headerVec;}
    std::string at (int index);
    void RenameHeader(std::vector<std::string> newNames);
    int HeaderSize() {return headerVec.size();}
private:
    std::vector <std::string> headerVec;
};


#endif //PROJECT1_STARTER_CODE_HEADER_H
