#include "grammatical.hpp"
std::vector<token> seq;
token look_ahead;
Tree::Tree()
{

}
Tree::Tree(const std::string str)
{
	data = str;
}
void Tree::add_son(Tree s)
{
	son.push_back(s);
};
void Tree::printTree(const std::string& prefix, bool isLast) const {
	std::cout << prefix << (isLast ? "+--- " : "|--- ") << data;
	/*if (son.size() == 1) {
		std::cout << " ";
		son[0].printTree("", false);
	}
	else {*/
		std::cout << std::endl;
		for (size_t i = 0; i < son.size(); ++i) {
			son[i].printTree(prefix + (isLast ? "     " : "|    "), i == son.size() - 1);
		}
	//}
}
void parse(std::vector<token> seq_input)
{
	std::string res;
	seq = seq_input;
	look_ahead = get_next_token();
	S s;
	do
	{
		s.next = get_new_label();
		Tree p = parse_S(s);
		res += s.code;
		if (look_ahead.type != END)
		{
			match(SPLIT, ";");
		}
#ifdef VISUALIZE
		p.printTree("", true);
#endif 
		res += s.next + " :";
	} while (look_ahead.type != END);
	res += "\t//S.next";
	std::cout << "\n\nThree Address Code:" << std::endl;
	std::cout << res;
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
int idx = 0;
token get_next_token()
{
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
		std::cout << "Error at match token " << idx << " " << look_ahead.data << "\n";
		exit(-1);
	}
}
bool token_cmp(int type, std::string data) {
	if (type != look_ahead.type) return false;
	if (type == KEY) return look_ahead.data == data;
	else if (type == SPLIT) return data[0] == look_ahead.data[0];
	else return true;
}
Tree parse_S(S& s)
{
	Tree tr("S");
	if (token_cmp(KEY, "if")) {

		match(KEY, "if");
		tr.add_son(Tree("if"));

		C c ;
		c._true = get_new_label();
		c._false = "@";//回填

		tr.add_son(parse_C(c));

		match(KEY, "then");
		tr.add_son(Tree("then"));

		S s1;
		s1.next = s.next;
		s1.begin = c._true; //解决if语句后面直接跟随while语句会出现应该共用标号的情况
		tr.add_son(parse_S(s1));

		if(token_cmp(KEY, "else")) {

			match(KEY, "else");
			tr.add_son(Tree("else"));

			// S -> if C then S1 else S2
			//std::cout << "s -> if C then s1 else s2" << std::endl;
			S s2;
			s2.next = s.next;

			tr.add_son(parse_S(s2));

			c._false = get_new_label();
			c.code.replace(c.code.find('@'), 1, c._false);
			s.code = c.code + gen(c._true + " :") + s1.code + gen("\tgoto " + s.next) + gen(c._false + " :") + s2.code;
		}
		else {
			// S -> if C then S1
			//std::cout << "s -> if C then s1" << std::endl;
			c._false = s.next;	
			s1.next = s.next;
			c.code.replace(c.code.find('@'), 1, c._false);
			s.code = c.code + gen(c._true + " :") + s1.code;
		}
	}
	else if (token_cmp(IDN, "id")) {
		std::string id = look_ahead.data;

		match(IDN, "id");
		tr.add_son(Tree(id));

		match(SPLIT, "=");
		tr.add_son(Tree("="));

		E e;
		tr.add_son(parse_E(e));

		match(SPLIT, ";");
		tr.add_son(Tree(";"));

		s.code = e.code + gen("\t" + id + " := " + e.place);
	}
	else if (token_cmp(KEY, "while")) {
		//S -> while C do S1 
		//std::cout << "S -> while C do S1 " << std::endl;
		bool s_begin_empty = (s.begin == "");
		if(s_begin_empty) s.begin = get_new_label();

		match(KEY, "while");
		tr.add_son(Tree("while"));

		C c;
		c._true = get_new_label();
		c._false = s.next;

		tr.add_son(parse_C(c));

		match(KEY, "do");
		tr.add_son(Tree("do"));

		S s1;
		s1.next = s.begin;
		tr.add_son(parse_S(s1));

		s.code = (s_begin_empty ? gen(s.begin + " :") : "") + c.code + gen(c._true + " :") + s1.code + gen("\tgoto " + s.begin);
	}	
	return tr;
}
Tree parse_C(C& c)
{
	Tree tr("C");
	E e1;
	tr.add_son(parse_E(e1));
	if (token_cmp(SPLIT, ">")) {
		//std::cout << "C -> E1 > E2" << std::endl;
		match(SPLIT, ">");
		tr.add_son(Tree(">"));

		E e2;
		parse_E(e2);
		c.code = e1.code + e2.code + gen("\tif " + e1.place + " > " + e2.place + " goto " + c._true) + gen("\tgoto " + c._false);
	}
	else if (token_cmp(SPLIT, "<")) {
		//std::cout << "C -> E1 < E2" << std::endl;
		match(SPLIT, "<");
		tr.add_son(Tree("<"));

		E e2;
		tr.add_son(parse_E(e2));

		c.code = e1.code + e2.code + gen("\tif " + e1.place + " < " + e2.place + " goto " + c._true) + gen("\tgoto " + c._false);
	}
	else if (token_cmp(SPLIT, "=")) {
		//std::cout << "C -> E1 = E2" << std::endl;
		match(SPLIT, "=");
		tr.add_son(Tree("="));

		E e2;
		tr.add_son(parse_E(e2));

		c.code = e1.code + e2.code + gen("\tif " + e1.place + " = " + e2.place + " goto " + c._true) + gen("\tgoto " + c._false);
	}
	else {
		error();
	}
	return tr;
}
Tree parse_E(E& e)
{
	Tree tr("E");
	// E -> TR
	//std::cout << "E -> TR" << std::endl;
	T t;
	tr.add_son(parse_T(t));
	R r;
	r.code = t.code;
	r.place = t.place;

	tr.add_son(parse_R(r));
	e.code = r.code;
	e.place = r.place;
	return tr;
}
Tree parse_T(T& t)
{
	Tree tr("T");
	// T -> FP
	//std::cout << "T -> FP" << std::endl;
	F f;
	tr.add_son(parse_F(f));
	P p;
	p.code = f.code;
	p.place = f.place;
	tr.add_son(parse_P(p));
	t.code = p.code;
	t.place = p.place;
	return tr;
}
Tree parse_P(P& p)
{
	Tree tr("P");
	if (token_cmp(SPLIT, "*")) {
		//P -> * FP1
		//std::cout << "P -> * FP1" << std::endl;
		match(SPLIT, "*");
		tr.add_son(Tree("*"));

		F f1;
		tr.add_son(parse_F(f1));

		std::string p_place = p.place;
		p.place = get_new_temp();
		p.code = f1.code + p.code + gen("\t" + p.place + " := " + p_place + " * " + f1.place);

		P p1 = p;
		tr.add_son(parse_P(p1));

		p.code = p1.code;
		p.place = p1.place;
	}
	else if (token_cmp(SPLIT, "/")) {
		//P -> / FP1
		//std::cout << "P -> / FP1" << std::endl;
		match(SPLIT, "/");
		tr.add_son(Tree("/"));

		F f1;
		tr.add_son(parse_F(f1));

		std::string p_place = p.place;
		p.place = get_new_temp();
		p.code = f1.code + p.code + gen("\t" + p.place + " := " + p_place + " / " + f1.place);

		P p1 = p;
		parse_P(p1);
		tr.add_son(parse_P(p1));

		p.code = p1.code;
		p.place = p1.place;
	}
	else {
		//std::cout << "P -> ε" << std::endl;
		tr.add_son(Tree("ε"));
	}
	return tr;
}
Tree parse_R(R& r)
{
	Tree tr("R");
	if (token_cmp(SPLIT, "+")) {
		//R -> + TR1
		//std::cout << "R -> + TR1" << std::endl;
		match(SPLIT, "+");
		tr.add_son(Tree("+"));

		T t1;
		tr.add_son(parse_T(t1));

		std::string r_place = r.place;
		r.place = get_new_temp();
		r.code = t1.code + r.code + gen("\t" + r.place + " := " + r_place + " + " + t1.place);
		R r1 = r;
		tr.add_son(parse_R(r1));

		r.code = r1.code;
		r.place = r1.place;
	}
	else if (token_cmp(SPLIT, "-")) {
		//R -> - TR1
		//std::cout << "R -> - TR1" << std::endl;
		match(SPLIT, "-");
		tr.add_son(Tree("-"));

		T t1;
		tr.add_son(parse_T(t1));

		std::string r_place = r.place;
		r.place = get_new_temp();
		r.code = t1.code + r.code + gen("\t" + r.place + " := " + r_place + " - " + t1.place);

		R r1 = r;
		tr.add_son(parse_R(r1));

		r.code = r1.code;
		r.place = r1.place;
	}
	else {
		//std::cout << "R -> ε" << std::endl;
		tr.add_son(Tree("ε"));
	}
	return tr;
}
Tree parse_F(F& f) {
	Tree tr("F");
	if ((token_cmp(SPLIT, "(")))
	{
		// F -> (E)
		//std::cout << "F -> (E)" << std::endl;
		match(SPLIT, "(");
		tr.add_son(Tree("("));

		E e;
		tr.add_son(parse_E(e));

		f.place = e.place;
		f.code = e.code;

		match(SPLIT, ")");
		tr.add_son(Tree(")"));
	}
	else if ((token_cmp(IDN, "id")))
	{
		// F -> id
		//std::cout << "F -> id" << std::endl;
		std::string id = look_ahead.data;
		match(IDN, "id");

		Tree son("id");
		son.add_son(id);
		tr.add_son(son);
		f.place = id;
		f.code = "";
	}
	else if (token_cmp(INT, "int"))
	{
		std::string data = look_ahead.data;
		//F -> int
		//std::cout << "F -> int" << std::endl;
		match(INT, "int");

		Tree son("int");
		son.add_son(data);
		tr.add_son(son);

		f.place = data;
		f.code = "";
	}
	else {
		error();
	}
	return tr;
}
void error()
{
	std::cout << "Error at parse, the next token is " << idx << " " << look_ahead.data << std::endl;
	exit(-1);
}

