//
// Created by Marcus Smiley on 10/21/21.
//
#include <map>
#include "Relation.h"
#ifndef PROJECT1_STARTER_CODE_DATABASE_H
#define PROJECT1_STARTER_CODE_DATABASE_H


class Database {
public:
    Database(){}
    std::map <std::string, Relation*>& GetMap(){return primDB;}
private:
    std::map <std::string, Relation*> primDB; //for primary database
};

#endif //PROJECT1_STARTER_CODE_DATABASE_H
