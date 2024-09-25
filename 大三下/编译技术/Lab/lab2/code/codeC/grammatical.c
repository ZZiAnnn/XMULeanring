#include "grammatical.h"
token_seq* seq;
token* look_ahead;
token* get_next_token()
{
	static int idx = 0;
	if (idx >= seq->token_size) {
		return NULL;
	}
	return &(seq->seq[idx++]);
}
void parse(token_seq* seq_input)
{
	seq = seq_input;
	look_ahead = get_next_token();
	parse_S();
}
void match(int type, char* target)
{
	if(token_cmp(type, target)){
		look_ahead = get_next_token();
	}
	else {
		printf("error at match token %s \n", look_ahead->data);
		exit(-1);
	}
}
bool token_cmp(int type, char* data) {
	if (type != look_ahead->type) return false;
	if (type == KEY) return !strcmp(look_ahead->data, data);
	else if (type == SPLIT) return data[0] == look_ahead->data[0];
	else return true;
}
void parse_S()
{
	if (token_cmp(KEY, "if")) {
		match(KEY, "if");
		parse_C();
		match(KEY, "then");
		parse_S();
		if(token_cmp(KEY, "else")) {
			parse_S();
		}
	}
	else if (token_cmp(IDN, "id")) {
		match(IDN, "id");
		match(SPLIT, "=");
		parse_E();
	}
	else if (token_cmp(KEY, "while")) {
		match(KEY, "while");
		parse_C();
		match(KEY, "do");
		parse_S();
	}
	else {
		error();
	}
	match(SPLIT, ";");
}
void parse_C()
{
	parse_E();
	if (token_cmp(SPLIT, ">")) {
		match(SPLIT, ">");
	}
	else if (token_cmp(SPLIT, "<")) {
		match(SPLIT,"<");
	}
	else if (token_cmp(SPLIT, "=")) {
		match(SPLIT, "=");
	}
	else {
		error();
	}
	parse_E();
}
void parse_E()
{
	parse_T();
	parse_R();
}
void parse_T()
{
	parse_F();
	parse_P();
}
void parse_P()
{
	if (token_cmp(SPLIT, "*")) {
		match(SPLIT, "*");
	}
	else if (token_cmp(SPLIT, "/")) {
		match(SPLIT, "/");
	}
	else return;
	parse_F();
	parse_P();
}
void parse_R()
{
	if (token_cmp(SPLIT, "+")) {
		match(SPLIT, "+");
	}
	else if (token_cmp(SPLIT, "-")) {
		match(SPLIT, "-");
	}
	else return;
	parse_T();
	parse_R();
}
void parse_F() {
	if ((token_cmp(SPLIT, "(")))
	{
		match(SPLIT, "(");
		parse_E();
		match(SPLIT, ")");
	}
	else if ((token_cmp(IDN, "id")))
	{
		match(IDN, "id");
	}
	else if (token_cmp(INT, "int"))
	{
		match(INT, "int");
	}
	else {
		error();
	}
}
void error()
{
	printf("Error at parse, the next token is \"%s\" \n", look_ahead->data);
	exit(-1);
}