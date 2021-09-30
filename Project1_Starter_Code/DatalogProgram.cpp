#include "DatalogProgram.h"
DatalogProgram::DatalogProgram(std::vector<Token*> allTokens) {
    for (unsigned int i = 0; i < allTokens.size(); ++i){
        tokens.push_back(allTokens.at(i));
    }
}

bool DatalogProgram::Match (TokenType currToken, TokenType requiredToken){
    if (currToken == requiredToken){
        ++index;
        return true;
    }
    else{
        throw tokens.at(index);
    }
}

void DatalogProgram::DatalogProgramInit() {
    //datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON factList
    //                      RULES COLON ruleList QUERIES COLON query queryList EOF
    Match(tokens.at(index)->ReturnType(), TokenType::SCHEMES);
    Match(tokens.at(index)->ReturnType(), TokenType::COLON);
    Scheme();
    SchemeList();
    Match(tokens.at(index)->ReturnType(), TokenType::FACTS);
    Match(tokens.at(index)->ReturnType(), TokenType::COLON);
    FactList();
    Match(tokens.at(index)->ReturnType(), TokenType::RULES);
    Match(tokens.at(index)->ReturnType(), TokenType::COLON);
    RuleList();
    Match(tokens.at(index)->ReturnType(), TokenType::QUERIES);
    Match(tokens.at(index)->ReturnType(), TokenType::COLON);
    Query();
    QueryList();
    Match(tokens.at(index)->ReturnType(), TokenType::ENDOFFILE);
}

void DatalogProgram::SchemeList(){
    //schemeList	->	scheme schemeList | lambda
    if (tokens.at(index)->ReturnType() == TokenType::ID){
        Scheme();
        SchemeList();
    }
    else{
        return;
    }
}

void DatalogProgram::FactList(){
    //factList	->	fact factList | lambda
    if (tokens.at(index)->ReturnType() == TokenType::ID) {
        Fact();
        FactList();
    }
    else{
        return;
    }
}

void DatalogProgram::RuleList() {
    //ruleList	->	rule ruleList | lambda
    if (tokens.at(index)->ReturnType() == TokenType::ID) {
        Rule();
        RuleList();
    }
    else{
        return;
    }
}

void DatalogProgram::QueryList() {
    //queryList	->	query queryList | lambda
    if (tokens.at(index)->ReturnType() == TokenType::ID) {
        Query();
        QueryList();
    }
    else{
        return;
    }
}

void DatalogProgram::Scheme(){
//scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN

    Match(tokens.at(index)->ReturnType(), TokenType::ID);
    Match(tokens.at(index)->ReturnType(), TokenType::LEFT_PAREN);
    Match(tokens.at(index)->ReturnType(), TokenType::ID);
    IdList();
    Match(tokens.at(index)->ReturnType(), TokenType::RIGHT_PAREN);

}

void DatalogProgram::Fact(){
//fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    Predicate predicate;
    predicate.setInitId(tokens.at(index)->ReturnValue());
    Match(tokens.at(index)->ReturnType(), TokenType::ID);
    Match(tokens.at(index)->ReturnType(), TokenType::LEFT_PAREN);
    //create a setParameter function
    Match(tokens.at(index)->ReturnType(), TokenType::STRING);
    StringList();
    Match(tokens.at(index)->ReturnType(), TokenType::RIGHT_PAREN);
    Match(tokens.at(index)->ReturnType(), TokenType::PERIOD);
}

void DatalogProgram::Rule(){
//rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
    HeadPredicate();
    Match(tokens.at(index)->ReturnType(), TokenType::COLON_DASH);
    ParsePredicate();
    PredicateList();
    Match(tokens.at(index)->ReturnType(), TokenType::PERIOD);
}

void DatalogProgram::Query(){
//query	        ->      predicate Q_MARK
    ParsePredicate();
    Match(tokens.at(index)->ReturnType(), TokenType::Q_MARK);
}

void DatalogProgram::HeadPredicate() {
//headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
    Match(tokens.at(index)->ReturnType(), TokenType::ID);
    Match(tokens.at(index)->ReturnType(), TokenType::LEFT_PAREN);
    Match(tokens.at(index)->ReturnType(), TokenType::ID);
    IdList();
    Match(tokens.at(index)->ReturnType(), TokenType::RIGHT_PAREN);
}

void DatalogProgram::ParsePredicate() {
//predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    Match(tokens.at(index)->ReturnType(), TokenType::ID);
    Match(tokens.at(index)->ReturnType(), TokenType::LEFT_PAREN);
    Parameter();
    ParameterList();
    Match(tokens.at(index)->ReturnType(), TokenType::RIGHT_PAREN);

}

void DatalogProgram::PredicateList() {
//predicateList	->	COMMA predicate predicateList | lambda
    if(tokens.at(index)->ReturnType() == TokenType::COMMA) {
        Match(tokens.at(index)->ReturnType(), TokenType::COMMA);
        ParsePredicate();
        PredicateList();
    }
    else{
        return;
    }
}

void DatalogProgram::ParameterList() {
//parameterList	-> 	COMMA parameter parameterList | lambda
    if(tokens.at(index)->ReturnType() == TokenType::COMMA){
        Match(tokens.at(index)->ReturnType(), TokenType::COMMA);
        Parameter();
        ParameterList();
    }
    else{
        return;
    }
}

void DatalogProgram::StringList() {
//stringList	-> 	COMMA STRING stringList | lambda
    if(tokens.at(index)->ReturnType() == TokenType::COMMA){
        Match(tokens.at(index)->ReturnType(), TokenType::COMMA);

        Match(tokens.at(index)->ReturnType(), TokenType::STRING);
        StringList();
    }
    else{
        return;
    }
}

/*create a new vector of parameters in stringlist
 * add as many parameters to the vector as necessary
 * then add them to the predicate when it returns
 * and then clear the vector
 * so we can keep using said vector
 * */


void DatalogProgram::IdList() {
//idList  	-> 	COMMA ID idList | lambda
    if(tokens.at(index)->ReturnType() == TokenType::COMMA){
        Match(tokens.at(index)->ReturnType(), TokenType::COMMA);
        Match(tokens.at(index)->ReturnType(), TokenType::ID);
        IdList();
    }
    else{
        return;
    }
}

void DatalogProgram::Parameter() {
//parameter	->	STRING | ID
    if(tokens.at(index)->ReturnType() == TokenType::STRING){
        Match(tokens.at(index)->ReturnType(), TokenType::STRING);
    }
    else if (tokens.at(index)->ReturnType() == TokenType::ID){
        Match(tokens.at(index)->ReturnType(), TokenType::ID);
    }
    else{
        return;
    }
}