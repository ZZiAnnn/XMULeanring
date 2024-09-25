#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
extern enum {
    INT, FLOAT, IDN, KEY, SPLIT, END
};
typedef struct {
    int type;
    char data[50];
}token;
typedef struct {
    int token_size;
    token* seq;
}token_seq;
bool is_split(char );
int get_next(char , int );//return -1 means error,return -2 means terminal
void ret_str(char[], int , int , token* );
void ret_int(char[], int, int, int, token*);
void ret_float(char[], int, int, int, token*);
void ret_split(char [], int, token*);
void get_type(int, char [], int, int, token*);
token_seq* scan(char[]);