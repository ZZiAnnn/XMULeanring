#pragma once
#include <string>
#include <iomanip>
#include <iostream>
#include "lexical.hpp"
#define VISUALIZE
class Tree
{
public:
    std::string data;
    std::vector<Tree> son;
    Tree();
    Tree(const std::string);
    void add_son(Tree);
    void printTree(const std::string& prefix, bool isLast) const;
};
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
}E, T, F, R, P, D, K;

token get_next_token();
void parse(std::vector<token>);
void match(int, std::string);
void error();
bool token_cmp(int, std::string);
std::string get_new_label();
std::string gen(std::string);
Tree parse_S(S&);
Tree parse_C(C&);
Tree parse_E(E&);
Tree parse_T(T&);
Tree parse_P(P&);
Tree parse_R(R&);
Tree parse_F(F&);
