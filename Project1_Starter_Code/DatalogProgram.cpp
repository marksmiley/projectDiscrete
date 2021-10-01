#include "DatalogProgram.h"
#include "Rule.h"
#include <sstream>
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
        ParseRule();
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
    std::string initId = tokens.at(index - 1)->ReturnValue();
    Match(tokens.at(index)->ReturnType(), TokenType::LEFT_PAREN);
    tempParameters.push_back(Parameter(tokens.at(index)->ReturnValue()));
    Match(tokens.at(index)->ReturnType(), TokenType::ID);
    IdList();
    pschemes.push_back(new Predicate(initId,tempParameters));
    tempParameters.clear();
    Match(tokens.at(index)->ReturnType(), TokenType::RIGHT_PAREN);
}

void DatalogProgram::Fact(){
//fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    Match(tokens.at(index)->ReturnType(), TokenType::ID);
    std::string initId = tokens.at(index - 1)->ReturnValue(); // this fixes warning 2.
    Match(tokens.at(index)->ReturnType(), TokenType::LEFT_PAREN);
    tempParameters.push_back(Parameter(tokens.at(index)->ReturnValue()));
    Match(tokens.at(index)->ReturnType(), TokenType::STRING);
    domain.insert(tokens.at(index - 1)->ReturnValue());
    StringList();
    //domain.insert(tokens.at(index - 1)->ReturnValue());
    pfacts.push_back(new Predicate(initId, tempParameters));
    tempParameters.clear();
    /*warnings:
     * 1 - be careful about where and when you clear.
     * 2 - can potentially can go out of bounds on tokens vector.
     * */
    Match(tokens.at(index)->ReturnType(), TokenType::RIGHT_PAREN);
    Match(tokens.at(index)->ReturnType(), TokenType::PERIOD);
}

void DatalogProgram::ParseRule(){
//rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
    std::string initId;
    Predicate headPredicate;
    HeadPredicate(headPredicate);
    Match(tokens.at(index)->ReturnType(), TokenType::COLON_DASH);
    pRules.push_back(ParsePredicate(initId));
    tempParameters.clear();
    PredicateList();
    ruleVector.push_back(new Rule(headPredicate, pRules));
    pRules.clear();
    Match(tokens.at(index)->ReturnType(), TokenType::PERIOD);
}

void DatalogProgram::Query(){
//query	        ->      predicate Q_MARK
    std::string initId;
    ParsePredicate(initId);
    pquery.push_back(new Predicate(initId, tempParameters));
    tempParameters.clear();
    Match(tokens.at(index)->ReturnType(), TokenType::Q_MARK);
}

void DatalogProgram::HeadPredicate(Predicate &headPredicate) {
//headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
    Match(tokens.at(index)->ReturnType(), TokenType::ID);
    std::string initId = tokens.at(index - 1)->ReturnValue();
    Match(tokens.at(index)->ReturnType(), TokenType::LEFT_PAREN);
    tempParameters.push_back(Parameter(tokens.at(index)->ReturnValue()));
    Match(tokens.at(index)->ReturnType(), TokenType::ID);
    IdList();
    headPredicate = Predicate(initId,tempParameters);
    tempParameters.clear();
    Match(tokens.at(index)->ReturnType(), TokenType::RIGHT_PAREN);
}

Predicate* DatalogProgram::ParsePredicate(std::string &initId) {
//predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    Match(tokens.at(index)->ReturnType(), TokenType::ID);
    initId = tokens.at(index - 1)->ReturnValue();
    Match(tokens.at(index)->ReturnType(), TokenType::LEFT_PAREN);
    parameter();
    ParameterList();
    Match(tokens.at(index)->ReturnType(), TokenType::RIGHT_PAREN);
    return new Predicate (initId, tempParameters);
}

void DatalogProgram::PredicateList() {
//predicateList	->	COMMA predicate predicateList | lambda
    if(tokens.at(index)->ReturnType() == TokenType::COMMA) {
        Match(tokens.at(index)->ReturnType(), TokenType::COMMA);
        std::string initId;
        pRules.push_back(ParsePredicate(initId));
        tempParameters.clear();
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
        parameter();
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
        tempParameters.push_back(Parameter(tokens.at(index)->ReturnValue()));
        Match(tokens.at(index)->ReturnType(), TokenType::STRING);
        domain.insert(tokens.at(index - 1)->ReturnValue());
        //predicate.addParameters(tokens.at(index)->ReturnValue());
        StringList();
    }
    else{
        return;
    }
}

/*create a new vector of parameters in stringlist - or make a universal vector
 * add as many parameters to the vector as necessary
 * then add them to the predicate when it returns
 * and then clear the vector
 * so we can keep using said vector
 * */


void DatalogProgram::IdList() {
//idList  	-> 	COMMA ID idList | lambda
    if(tokens.at(index)->ReturnType() == TokenType::COMMA){
        Match(tokens.at(index)->ReturnType(), TokenType::COMMA);
        tempParameters.push_back(Parameter(tokens.at(index)->ReturnValue()));
        Match(tokens.at(index)->ReturnType(), TokenType::ID);
        IdList();
    }
    else{
        return;
    }
}

void DatalogProgram::parameter() {
//parameter	->	STRING | ID
    if(tokens.at(index)->ReturnType() == TokenType::STRING){
        Match(tokens.at(index)->ReturnType(), TokenType::STRING);
        tempParameters.push_back(Parameter(tokens.at(index - 1)->ReturnValue()));
    }
    else if (tokens.at(index)->ReturnType() == TokenType::ID){
        Match(tokens.at(index)->ReturnType(), TokenType::ID);
        tempParameters.push_back(Parameter(tokens.at(index - 1)->ReturnValue()));
    }
    else{
        return;
    }
}

std::string DatalogProgram::ToString(){
    std::stringstream returnString;
    returnString << "Schemes(" << pschemes.size() << "):" << std::endl;
    for (int i = 0; i < pschemes.size(); i++){
        returnString << "  " << pschemes.at(i)->ToString(*pschemes.at(i)) << std::endl;
    }
    returnString << "Facts(" << pfacts.size() << "):" << std::endl;
    for (int i = 0; i < pfacts.size(); ++i){
        returnString << "  " << pfacts.at(i)->ToString(*pfacts.at(i)) << "." << std::endl;
    }
    returnString << "Rules(" << ruleVector.size() << "):" << std::endl;
    for (int i = 0; i < ruleVector.size(); i++){
        returnString << "  " << ruleVector.at(i)->ToString() << std::endl;
    }
    returnString << "Queries(" << pquery.size() << "):" << std::endl;
    for (int i = 0; i < pquery.size(); ++i){
        returnString << "  " << pquery.at(i)->ToString(*pquery.at(i)) << "?" << std::endl;
    }
    returnString << "Domain(" << domain.size() << "):" << std::endl;
    for (auto i = domain.begin(); i != domain.end(); i++){
        returnString << "  " << *i << std::endl;
    }
    return returnString.str();
}
