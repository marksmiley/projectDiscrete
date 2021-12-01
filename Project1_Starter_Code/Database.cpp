//
// Created by Marcus Smiley on 10/21/21.
//

#include "Database.h"

int Database::Count(){
    int numTuples = 0;
    std::map<std::string, Relation*>::iterator it;
    for (it = primDB.begin(); it != primDB.end(); ++it){
        numTuples += it->second->GetTupleInt();
    }
    return numTuples;
}