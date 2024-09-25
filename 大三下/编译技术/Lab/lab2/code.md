```assembly
L1: t1 := a3 + 15                           
	if t1 > 10 goto L2                           
	goto L0                                       
L2: if x2 = 7 goto L3                            
	goto L1                                     
L3: if y < z goto L4                       
	goto L1 
L4: t2 := x * y 
	t3 := t2 / z 
	y := t3
	goto L3 
	goto L1 
L0: // S.next 
```

| 产生式                      | 语义规则                                                     |
| --------------------------- | ------------------------------------------------------------ |
| S → id =  E;                | S.code = E.code \|\| gen(id.place ':=' E.place)              |
| S → if C then S1;           | C.true = newlabel; C.false = S.next; S1.next = S.next;         S.code = C.code \|\| gen(C.true ':' ) \|\| S1.code |
| S → if C then S1   else S2; | C.true = newlabel; C.false = newlabel;                      S1.next = S2.next = S.next;                                   S.code = C.code \|\| gen(C.true ':') \|\| S1.code \|\|          gen('goto' S.next) \|\| gen(C.false ':' ) \|\| S2.code; |
| S → while C do S1;          | S.begin = newlabel; C.true = newlabel; C.false = S.next;      S1.next = S.begin;                                            S.code = gen(S.begin ':') \|\| C.code \|\|  gen(C.true ':') \|\| S1.code \|\| gen('goto' S.begin) |
| C → E1 >  E2                | C.code = E1.code \|\| E2.code \|\|                              gen('if' E1.place '>' E2.place 'goto' C.true) \|\|         gen('goto' C.false) |
| C → E1 < E2                 | C.code = E1.code \|\| E2.code \|\|                              gen('if' E1.place '<' E2.place 'goto' C.true) \|\|         gen('goto' C.false) |
| C → E1 = E2                 | C.code = E1.code \|\| E2.code \|\|                              gen('if' E1.place '=' E2.place 'goto' C.true) \|\|         gen('goto' C.false) |
| E → E1 + T                  | E.place = newtemp;                                              E.code = E1.code \|\| T.code \|\|                           gen(E.place ':=' E1.place '+' T.place) |
| E → E1 - T                  | E.place = newtemp;                                              E.code = E1.code \|\| T.code \|\|                           gen(E.place ':=' E1.place '-' T.place) |
| E → T                       | E.place = T.place;  E.code = T.code                          |
| T → F                       | T.place = F.place;  T.code = F.code                          |
| T → T1 * F                  | T.place = newtemp;                                             T.code = T1.code \|\| F.code \|\|                               gen(T.place ':=' T1.place '*' F.place) |
| T → T1 / F                  | T.place = newtemp;                                            T.code = T1.code \|\| F.code \|\|                            gen(T.place ':=' T1.place '/' F.place) |
| F → ( E )                   | F.place = E.place;       F.code = E.code                     |
| F → id                      | F.place = id.name;       F.code = ' '                        |
| F → int8                    | F.place = int8.value;    F.code = ' '                        |
| F → int10                   | F.place = int10.value;   F.code = ' '                        |
| F → int16                   | F.place = int16.value;   F.code = ' '                        |







```c
while (a3+15)>0xa do 
    if x2 = 7 then 
        while y<z do y = x * y / z; 
```

```cpp
std::string gen(std::string code) {
	std::string s = code;
	if (code.back() != ':') s += '\n';
	return move(s);
}
```

```pseudocode
function match(target)
    if look_ahead == target
        look_ahead = get_next_token()
    else
        error

function parse_S()
    if look_ahead == "if"
        match("if")
        parse_C()
        match("then")
        parse_S()
        if look_ahead == "else"
            parse_S()
        match(";")
    else if look_ahead == "id" 
        match("id")
        match("=")
        parse_E()
        match(";")
    else if look_ahead == "while"
        match("while")
        parse_C()
        match("do")
        parse_S()
        match(";")
    else
        error()


function parse_C()
    parse_E()
    if look_ahead == ">"
        match(">")
    else if look_ahead == "<"
        match("<")
    else if look_ahead == "="
        match("=")
    else
        error()
    parse_E()

function parse_E()
    parse_T()
    parse_R()

function parse_T()
    parse_F()
    parse_P()

function parse_P()
    if look_ahead == "*"
        match("*")
    else if look_ahead == "/"
        match("/")
    else
        return
    parse_F()
    parse_P()

function parse_R()
    if look_ahead == "+"
        match("+")
    else if look_ahead == "-"
        match("-")
    else
        return
    parse_T()
    parse_R()

function parse_F()
    if look_ahead == "("
        match("(")
        parse_E()
        match(")")
    else if look_ahead == "id" 
        match("id")
    else if look_ahead == "int" 
        match("int")
    else
        error()

```



```cpp
		else {
			// s -> if C then s1
			c._false = s.next;	
			s1.next = s.next;
			c.code.replace(c.code.find('@'), 1, c._false);
			s.code = c.code + gen(c._true + " :") + s1.code;
		}
```

```cpp
	else if (token_cmp(IDN, "id")) {
		std::string id = look_ahead.data;
		match(IDN, "id");
		match(SPLIT, "=");
		E e = parse_E();
		match(SPLIT, ";");
		s.code = e.code + gen("\t" + id + " := " + e.place);
	}
```

```cpp
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

	s.code = (s_begin_empty ? gen(s.begin + " :") : "") 
        + c.code + gen(c._true + " :") + s1.code + gen("\tgoto " + s.begin);
}	
return s;
```

```cpp
C parse_C(C c)
{
	E e1 = parse_E();
	if (token_cmp(SPLIT, ">")) {
		match(SPLIT, ">");
		E e2 = parse_E();
		c.code = e1.code + e2.code + gen("\tif " + e1.place + " > " 
                 + e2.place + " goto " + c._true) + gen("\tgoto " + c._false);
	}
	else if (token_cmp(SPLIT, "<")) {
		match(SPLIT, "<");
		E e2 = parse_E();
		c.code = e1.code + e2.code + gen("\tif " + e1.place + " < "
                 + e2.place + " goto " + c._true) + gen("\tgoto " + c._false);
	}
	else if (token_cmp(SPLIT, "=")) {
		match(SPLIT, "=");
		E e2 = parse_E();
		c.code = e1.code + e2.code + gen("\tif " + e1.place + " = " 
                 + e2.place + " goto " + c._true) + gen("\tgoto " + c._false);
	}
	else {
		error();
	}
	return c;
}
```

```cpp
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
```

```cpp
R parse_R(T t)
{
	R r;
	if (token_cmp(SPLIT, "+")) {
		//R -> + TR1
		match(SPLIT, "+");
		T t1 = parse_T();

		r.place = get_new_temp();
		r.code = t.code + t1.code + 
            gen("\t" + r.place + " := " + t.place + " + " + t1.place);

		R r1 = parse_R(r);
		r.code = r1.code;
		r.place = r1.place;
	}
	else if (token_cmp(SPLIT, "-")) {
		//R -> - TR1
		match(SPLIT, "-");
		T t1 = parse_T();

		r.place = get_new_temp();
		r.code = t.code + t1.code + 
            gen("\t" + r.place + " := " + t.place + " - " + t1.place);

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
```



| 产生式                     | 语义规则                                                     |
| -------------------------- | ------------------------------------------------------------ |
| S → id = E;                | S.code = E.code \|\| gen(id.place ':=' E.place)              |
| S → if C then S1           | C.true = newlabel; C.false = S.next; S1.next = S.next;         S.code = C.code \|\| gen(C.true ':' ) \|\| S1.code |
| S → if C then S1   else S2 | C.true = newlabel; C.false = newlabel;                      S1.next = S2.next = S.next;                                   S.code = C.code \|\| gen(C.true ':') \|\| S1.code \|\|          gen('goto' S.next) \|\| gen(C.false ':' ) \|\| S2.code; |
| S → while C do S1          | S.begin = newlabel; C.true = newlabel; C.false = S.next;      S1.next = S.begin;                                            S.code = gen(S.begin ':') \|\| C.code \|\| gen(C.true ':') \|\| S1.code \|\| gen('goto' S.begin); |
| C → E1 >  E2               | C.code = E1.code \|\| E2.code \|\|                              gen('if' E1.place '>' E2.place 'goto' C.true) \|\|         gen('goto' C.false) |
| C → E1 < E2                | C.code = E1.code \|\| E2.code \|\|                              gen('if' E1.place '<' E2.place 'goto' C.true) \|\|         gen('goto' C.false) |
| C → E1 = E2                | C.code = E1.code \|\| E2.code \|\|                              gen('if' E1.place '=' E2.place 'goto' C.true) \|\|         gen('goto' C.false) |
| E → T R                    | E.code = R.code; E.place = R.code;                           |
| R → + T1 R1                | R.place = newtemp()                                         R.code = T.code \|\| T1.code \|\|                                   gen(R.place ':=' T.place '+' T1.place);                         R.code = R1.code; R.place = R1.place; |
| R → - T1 R1                | R.place = newtemp()                                         R.code = T.code \|\|T1.code \|\|                                        gen(R.place ':=' T.place '-' T1.place);                         R.code = R1.code; R.place = R1.place; |
| R1 → ε                     | R1.code = T.code; R1.place = T.place;                        |
| T → F P                    | T.code = P.code; T.place = P.place;                          |
| P → * F1 P1                | P.place = newtemp()                                         P.code = F.code \|\|F1.code \|\|                            gen(P.place ':=' F.place '*' F.place);                         P.code = P1.code; P.place = P1.place; |
| P → / FP1                  | P.place = newtemp()                                         P.code = F.code \|\|F1.code \|\|                                    gen(P.place ':=' F.place '/' F.place);                         P.code = P1.code; P.place = P1.place; |
| P1 → ε                     | P1.code = F.code; P1.place = F.place;                        |
| F → ( E )                  | F.place = E.place;       F.code = E.code                     |
| F → id                     | F.place = id.name;       F.code = ' '                        |
| F → int8                   | F.place = int8.value;    F.code = ' '                        |
| F → int10                  | F.place = int10.value;   F.code = ' '                        |
| F → int16                  | F.place = int16.value;   F.code = ' '                        |

```c
while ( id + int ) > int do if id = int then while id < id do id = id * id / id;
```

```c
void match(char* target)
{
	if (!strcmp(look_ahead, target)) {
		look_ahead = get_next_token();
	}
	else {
		printf("error!\n");
		exit(-1);
	}

```

```c
char s[1024];
void parse(char str[])
{
	strcpy(s, str);
	look_ahead = get_next_token();
	parse_S();
}
```

```c
char* look_ahead;
char* get_next_token()
{
	static int idx = 0;
	char* token = (char*)malloc(10 * sizeof(char));
	if (s[idx] == '\0') {
		return NULL;
	}
	int i = 0;
	while (s[idx] != ' ' && s[idx] != '\0') {  
		token[i++] = s[idx++];
	}
	token[i] = '\0'; 
	if (s[idx] == ' ') idx++;
	return token;
}
```

```c
void match(char* target)
{
	if (!strcmp(look_ahead, target)) {
		look_ahead = get_next_token();
	}
	else {
		printf("error!\n");
		exit(-1);
	}
}
```

```c
void parse_S()
{
	if (!strcmp(look_ahead, "if")) {
		match("if");
		parse_C();
		match("then");
		parse_S();
		if(strcmp(look_ahead, "else")) {
			parse_S();
		}
		match(";");
	}
	else if (!strcmp(look_ahead, "id")) {
		match("id");
		match("=");
		parse_E();
		match(";");
	}
	else if (!strcmp(look_ahead, "while")) {
		match("while");
		parse_C();
		match("do");
		parse_S();
		match(";");
	}
	else printf("error\n");
}
void parse_C()
{
	parse_E();
	if (!strcmp(look_ahead, ">")) {
		match(">");
		parse_E();
	}
	else if (!strcmp(look_ahead, "<")) {
		match("<");
		parse_E();
	}
	else if (!strcmp(look_ahead, "=")) {
		match("=");
		parse_E();
	}
	else exit(-1);	
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
	if (!strcmp(look_ahead, "*")) {
		match("*");
		parse_F();
		parse_P();
	}
	else if (!strcmp(look_ahead, "/")) {
		match("/");
		parse_F();
		parse_P();
	}
	else return;
}
void parse_R()
{
	if (!strcmp(look_ahead, "+")) {
		match("+");
		parse_T();
		parse_R();
	}
	else if (!strcmp(look_ahead, "-")) {
		match("-");
		parse_T();
		parse_R();
	}
	else return;
}
void parse_F() {
	if (!strcmp(look_ahead ,"("))
	{
		match("(");
		parse_E();
		match(")");
	}
	else if (!strcmp(look_ahead, "id"))
	{
		match("id");
	}
	else if (!strcmp(look_ahead, "int"))
	{
		match("int");
	}
	else exit(-1);
}
```

```c
#include "grammatical.h"
int main()
{
    FILE* fp;
    char filename[] = "test.txt";
    char buffer[2024];
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("failed to open file:%s\n", filename);
        exit(1);
    }
    int line = 1;
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        parse(buffer);
    }
    fclose(fp);
    return 0;
}
```

```c
extern enum {
    INT,
    FLOAT,
    IDN,
    KEY,
    SPLIT
};
typedef struct {
    int type;
    char str_ret[50];
    int int_ret;
    double float_ret;
}token;
token* scan(char s[]);
```

```c
token_seq* scan(char s[])
{
    token* seq = malloc(sizeof(token) * 1024);
    int j = 0, i = 0, seq_size = 0;
    while (s[j]) {
        int T = 0, finished = 0;
        for (i = j; s[i]; ++i) {
            int next_T = get_next(s[i], T);
            if (next_T == -2) {
                finished = 1;
                break;
            }
            else if (next_T == 0) {
                T = next_T;
                ++j;
            }
            else T = next_T;
        }
        if (!s[i]) finished = 1;
        if (T == 0) continue;
        if (finished) {
            get_type(T, s, j, i - 1,&seq[seq_size++]);
            j = i;
        }
    }
    token_seq* ret = (token_seq*)malloc(sizeof(token_seq));
    ret->token_size = seq_size;
    ret->seq = seq;
    return ret;
}
```

```c
void get_type(int T, char s[], int start_idx, int end_idx, token* t)
{
    switch (T)
    {
        case  1:
        case  2: ret_str  (s, start_idx, end_idx, t);break;
        case  3:
        case  4: ret_int  (s, start_idx, end_idx, 10, t);break;
        case  6: ret_float(s, start_idx, end_idx, 10, t);break;
        case  8: ret_int  (s, start_idx, end_idx, 8,  t);break;
        case 10: ret_float(s, start_idx, end_idx, 8,  t);break;
        case 12: ret_int  (s, start_idx, end_idx, 16, t);break;
        case 14: ret_float(s, start_idx, end_idx, 16, t);break;
        case 15: ret_split(s, start_idx, t);break;
    }
}
```

```c
void ret_int(char s[], int i, int j, int p, token* t)
{
    if (p != 10) i += 2;
    int x = 0;
    for (int k = i; k <= j; ++k) {
        x = x * p + s[k] - (isdigit(s[k]) ? '0' : ('a' - 10));
    }
    t->type = INT;
    sprintf(t->data, "%d", x);
}
```

```c
extern enum {
    INT, FLOAT, IDN, KEY, SPLIT
};
typedef struct {
    int type;
    char data[50];
}token;
typedef struct {
    int token_size;
    token* seq;
}token_seq;
```

```c
void ret_str(char str[], int i, int j, token* t)
{
    char sub[1024];
    strncpy(sub, str + i, j - i + 1);
    sub[j - i + 1] = '\0';

    int is_keyword = 0;
    for (int k = 0; k < sizeof(keywords) / sizeof(keywords[0]); k++) {
        if (strcmp(sub, keywords[k]) == 0) {
            is_keyword = 1;break;
        }
    }
    if (is_keyword) {
        for (int k = 0; k < strlen(sub); ++k) sub[k] = tolower(sub[k]);
        t->type = KEY;
        memcpy(t->data, sub, sizeof(sub));
    }
    else {
        t->type = IDN;
        memcpy(t->data, sub, sizeof(sub));
    }
}
```

```c
token_seq* seq;
token* look_ahead;
void parse(token_seq* seq_input)
{
	seq = seq_input;
	look_ahead = get_next_token();
	parse_S();
}
token* get_next_token()
{
	static int idx = 0;
	if (idx >= seq->token_size) {
		printf("Error of wrong token length \n");
		exit(-1);
	}
	return &(seq->seq[idx++]);
}
void match(int type, char* target)
{
	if(token_cmp(type, target)){
		look_ahead = get_next_token();
	}
	else {
		printf("Error at match token %s \n", look_ahead->data);
		exit(-1);
	}
}
bool token_cmp(int type, char* data) {
	if (type != look_ahead->type) return false;
	if (type == KEY) return !strcmp(look_ahead->data, data);
	else if (type == SPLIT) return data[0] == look_ahead->data[0];
	else return true;
}
```

```c
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
```

```c
#include <stdio.h>
#include <stdlib.h>
#include "grammatical.h"
int main()
{
    FILE* fp;
    char filename[] = "test.txt";
    char buffer[2024];
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("failed to open file:%s\n", filename);
        exit(1);
    }
    int line = 1;
    token_seq* tokens = (token_seq*)malloc(sizeof(token_seq));
    tokens->seq = (token*)malloc(sizeof(token) * 1024);
    tokens->token_size = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        token_seq* res = scan(buffer);
        for (int i = 0; i < res->token_size; ++i)
        {
            (tokens->seq[tokens->token_size]).type = (res->seq)[i].type;
            strcpy((tokens->seq[tokens->token_size++]).data, (res->seq[i]).data);
        }
        free(res);
    }
    printf("%d\n", tokens->token_size);
    for (int i = 0; i < tokens->token_size; ++i)
    {
        printf("%s ", tokens->seq[i].data);
    }
    puts("");
    parse(tokens);
    free(tokens->seq);
    free(tokens);
    fclose(fp);
    return 0;
}
```

```
while (a3+15)>0xa do 
	if x2 = 7 then 
		while y<z  do 
			y = x * y / z;
		;
	;
;
```

```cpp
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
```

```cpp
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
```

```cpp
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
			s.code = c.code + gen(c._true + " :") 
                + s1.code + gen("\tgoto " + s.next) + gen(c._false + " :") + s2.code;
		}

```

```cpp
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
```

```cpp
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
```

```cpp
#include "grammatical.hpp"
int main()
{
    std::string filename = "test.txt";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 1;
    }

    std::vector<token> tokens;
    std::string buffer;

    std::cout << "Input file: " << std::endl;
    while (std::getline(file, buffer)) {
        std::cout << buffer << std::endl;
        std::vector<token> res = scan(buffer);
        tokens.insert(tokens.end(), res.begin(), res.end());
    }

    file.close();

    std::cout << "\nToken size: " << tokens.size() << std::endl;
    std::cout << "\nTokens: ";
    for (const auto& tok : tokens) {
        std::cout << tok.data << " ";
    }
    std::cout << "\n\nThree Address Code:" << std::endl;
    parse(tokens);

    return 0;
}
```

```c

a = b + 1 / c - 1 + d;
;
a = b + 1 / c - (1 + d);
;
if a < b then
    a = b + 1 / c - (1 + d);
else
    c = d;
```

