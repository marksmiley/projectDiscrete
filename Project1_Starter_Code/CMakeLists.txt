cmake_minimum_required(VERSION 3.16.3)
project(Project1_Starter_Code)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include_directories(.)

add_executable(projectOne
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.h
        ColonDashAutomaton.cpp
        Lexer.h
        Lexer.cpp
        Token.h
        Token.cpp
        main.cpp
        CommaAutomaton.cpp
        CommaAutomaton.h
        PeriodAutomaton.cpp
        PeriodAutomaton.h
        Q_MarkAutomaton.cpp
        Q_MarkAutomaton.h
        Left_ParenAutomaton.cpp
        Left_ParenAutomaton.h
        Right_ParenAutomaton.cpp
        Right_ParenAutomaton.h MultiplyAutomaton.cpp MultiplyAutomaton.h SchemesAutomaton.cpp SchemesAutomaton.h FactsAutomaton.cpp FactsAutomaton.h RulesAutomaton.cpp RulesAutomaton.h QueriesAutomaton.cpp QueriesAutomaton.h IDAutomaton.cpp IDAutomaton.h CommentAutomata.cpp StringAutomaton.cpp StringAutomaton.h CommentAutomata.h AddAutomaton.h AddAutomaton.cpp DatalogProgram.cpp DatalogProgram.h Predicate.cpp Predicate.h Parameter.cpp Parameter.h Rule.cpp Rule.h Database.cpp Database.h Relation.cpp Relation.h Header.cpp Header.h Tuple.cpp Tuple.h Interpreter.cpp Interpreter.h)
