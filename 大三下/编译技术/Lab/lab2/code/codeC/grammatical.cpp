#include "grammatical.hpp"
std::vector<token> seq;
token look_ahead;
void parse(std::vector<token> seq_input)
{
	seq = seq_input;
	look_ahead = get_next_token();
	S s;
	do
	{
		s.next = get_new_label();
		s = parse_S(s);
		std::cout << s.code;
		if (look_ahead.type != END)
		{
			match(SPLIT, ";");
		}
		std::cout << s.next << " :";
	} while (look_ahead.type != END);
	std::cout << "\t//S.next" << std::endl;
}
std::string get_new_label()
{
	static int label_count = 0;
	return move(std::string("L") + std::to_string(label_count++));
}
std::string get_new_temp()
{
	static int label_count = 1;
	return move(std::string("t") + std::to_string(label_count++));
}
std::string gen(std::string code) {
	std::string s = code;
	if (code.back() != ':') s += '\n';
	return move(s);
}

token get_next_token()
{
	static int idx = 0;
	if (idx > seq.size()) {
		std::cout << "Error of wrong token length \n";
		exit(-1);
	}
	if (idx == seq.size()) return {END,"END"};
	return seq[idx++];
}
void match(int type, std::string target)
{
	if(token_cmp(type, target)){
		look_ahead = get_next_token();
	}
	else {
		std::cout << "Error at match token " << look_ahead.data << "\n";
		exit(-1);
	}
}
bool token_cmp(int type, std::string data) {
	if (type != look_ahead.type) return false;
	if (type == KEY) return look_ahead.data == data;
	else if (type == SPLIT) return data[0] == look_ahead.data[0];
	else return true;
}
S parse_S(S s)
{
	if (token_cmp(KEY, "if")) {
		match(KEY, "if");

		C c ;
		c._true = get_new_label();
		c._false = "@";//回填
		c = parse_C(c);
		match(KEY, "then");
		S s1;
		s1.next = s.next;
		s1.begin = c._true; //解决if语句后面直接跟随while语句会出现应该共用标号的情况
		s1 = parse_S(s1);
		if(token_cmp(KEY, "else")) {
			match(KEY, "else");
			// s -> if C then s1 else s2
			S s2;
			s2.next = s.next;
			s2 = parse_S(s2);
			c._false = get_new_label();
			c.code.replace(c.code.find('@'), 1, c._false);
			s.code = c.code + gen(c._true + " :") + s1.code + gen("\tgoto " + s.next) + gen(c._false + " :") + s2.code;
		}
		else {
			// s -> if C then s1
			c._false = s.next;	
			s1.next = s.next;
			c.code.replace(c.code.find('@'), 1, c._false);
			s.code = c.code + gen(c._true + " :") + s1.code;
		}
	}
	else if (token_cmp(IDN, "id")) {
		std::string id = look_ahead.data;
		match(IDN, "id");
		match(SPLIT, "=");
		E e = parse_E();
		match(SPLIT, ";");
		s.code = e.code + gen("\t" + id + " := " + e.place);
	}
	else if (token_cmp(KEY, "while")) {
		//S -> while C do S1 
		bool s_begin_empty = s.begin == "";
		if(s_begin_empty) s.begin = get_new_label();
		match(KEY, "while");

		C c;
		c._true = get_new_label();
		c._false = s.next;

		c = parse_C(c);
		match(KEY, "do");

		S s1;
		s1.next = s.begin;
		s1 = parse_S(s1);

		s.code = (s_begin_empty ? gen(s.begin + " :") : "") + c.code + gen(c._true + " :") + s1.code + gen("\tgoto " + s.begin);
	}	
	return s;
}
C parse_C(C c)
{
	E e1 = parse_E();
	if (token_cmp(SPLIT, ">")) {
		match(SPLIT, ">");
		E e2 = parse_E();
		c.code = e1.code + e2.code + gen("\tif " + e1.place + " > " + e2.place + " goto " + c._true) + gen("\tgoto " + c._false);
	}
	else if (token_cmp(SPLIT, "<")) {
		match(SPLIT, "<");
		E e2 = parse_E();
		c.code = e1.code + e2.code + gen("\tif " + e1.place + " < " + e2.place + " goto " + c._true) + gen("\tgoto " + c._false);
	}
	else if (token_cmp(SPLIT, "=")) {
		match(SPLIT, "=");
		E e2 = parse_E();
		c.code = e1.code + e2.code + gen("\tif " + e1.place + " = " + e2.place + " goto " + c._true) + gen("\tgoto " + c._false);
	}
	else {
		error();
	}
	return c;
}
E parse_E()
{
	// E -> TR
	E e;
	T t = parse_T();
	R r;
	r = parse_R(t);
	e.code = r.code;
	e.place = r.place;
	return e;
}
T parse_T()
{
	// T -> FP
	T t;
	F f = parse_F();
	P p = parse_P(f);
	t.code = p.code;
	t.place = p.place;
	return t;
}
P parse_P(F f)
{
	P p;
	if (token_cmp(SPLIT, "*")) {
		//P -> * FP1
		match(SPLIT, "*");
		F f1 = parse_F();

		p.place = get_new_temp();
		p.code = f.code + f1.code + gen("\t" + p.place + " := " + f.place + " * " + f1.place);

		P p1 = parse_P(p);

		p.code = p1.code;
		p.place = p1.place;
	}
	else if (token_cmp(SPLIT, "/")) {
		//P -> / FP1
		match(SPLIT, "/");
		F f1 = parse_F();

		p.place = get_new_temp();
		p.code = f.code + f1.code + gen("\t" + p.place + " := " + f.place + " / " + f1.place);

		P p1 = parse_P(p);

		p.code = p1.code;
		p.place = p1.place;
	}
	else {
		p.code = f.code;
		p.place = f.place;
	}
	return p;
}
R parse_R(T t)
{
	R r;
	if (token_cmp(SPLIT, "+")) {
		//R -> + TR1
		match(SPLIT, "+");
		T t1 = parse_T();

		r.place = get_new_temp();
		r.code = t.code + t1.code + gen("\t" + r.place + " := " + t.place + " + " + t1.place);

		R r1 = parse_R(r);

		r.code = r1.code;
		r.place = r1.place;
	}
	else if (token_cmp(SPLIT, "-")) {
		//R -> - TR1
		match(SPLIT, "-");
		T t1 = parse_T();

		r.place = get_new_temp();
		r.code = t.code + t1.code + gen("\t" + r.place + " := " + t.place + " - " + t1.place);

		R r1 = parse_R(r);

		r.code = r1.code;
		r.place = r1.place;
	}
	else {
		r.code = t.code;
		r.place = t.place;
	}
	return r;
}
F parse_F() {
	F f;
	if ((token_cmp(SPLIT, "(")))
	{
		// F -> (E)
		match(SPLIT, "(");

		E e = parse_E();
		f.place = e.place;
		f.code = e.code;

		match(SPLIT, ")");
	}
	else if ((token_cmp(IDN, "id")))
	{
		// F -> id
		std::string id = look_ahead.data;
		match(IDN, "id");
		f.place = id;
		f.code = "";
	}
	else if (token_cmp(INT, "int"))
	{
		std::string data = look_ahead.data;
		//F -> int
		match(INT, "int");
		f.place = data;
		f.code = "";
	}
	else {
		error();
	}
	return f;
}
void error()
{
	std::cout << "Error at parse, the next token is " << look_ahead.data << std::endl;
	exit(-1);
}

