#pragma once
#include <string>
#include <iomanip>
#include <iostream>
#include "lexical.hpp"
class S{
public :
    std::string place, code, begin, next;
};
class C {
public:
    std::string _true,_false,code;
};
typedef class {
public:
    std::string code, place;
}E, T, F, R, P;

token get_next_token();
void parse(std::vector<token>);
void match(int, std::string);
std::string get_new_label();
std::string gen(std::string);
S parse_S(S);
void error();
bool token_cmp(int,std::string);
C parse_C(C);
E parse_E();
T parse_T();
P parse_P(F f);
R parse_R(T t);
F parse_F();
