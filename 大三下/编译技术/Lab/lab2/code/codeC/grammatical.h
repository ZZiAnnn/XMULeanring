#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexical.h"
char* look_head;
token* get_next_token();
void parse(token_seq*);
void match(int, char*);
void parse_S();
void error();
bool token_cmp(int, char*);
void parse_C();
void parse_E();
void parse_T();
void parse_P();
void parse_R();
void parse_F();