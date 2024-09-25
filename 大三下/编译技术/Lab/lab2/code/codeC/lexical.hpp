#pragma once
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
extern enum {
    INT, FLOAT, IDN, KEY, SPLIT, END
};
typedef struct {
    int type;
    std::string data;
}token;
bool is_split(char );
int get_next(char , int );//return -1 means error,return -2 means terminal
token ret_str(const std::string&, int, int);
token ret_int(const std::string&, int, int, int);
token ret_float(const std::string&, int, int, int);
token ret_split(const std::string&, int);
token get_type(int, const std::string&, int, int);
std::vector<token> scan(const std::string);