#include "Lexical.h"
namespace lexical {
	std::unordered_map<std::string, Symbol> keywordMap = {
		{"begin", Symbol::BeginSym},
		{"call", Symbol::CallSym},
		{"const", Symbol::ConstSym},
		{"do", Symbol::DoSym},
		{"end", Symbol::EndSym},
		{"if", Symbol::IfSym},
		{"odd", Symbol::OddSym},
		{"procedure", Symbol::ProcSym},
		{"read", Symbol::ReadSym},
		{"then", Symbol::ThenSym},
		{"var", Symbol::VarSym},
		{"while", Symbol::WhileSym},
		{"write", Symbol::WriteSym}
	};

	std::unordered_map<char, Symbol> singleChar = {
		{'+', Symbol::Plus},
		{'-', Symbol::Minus},
		{'*', Symbol::Times},
		{'/', Symbol::Slash},
		{'(', Symbol::LParen},
		{')', Symbol::RParen},
		{'=', Symbol::Eql},
		{',', Symbol::Comma},
		{'.', Symbol::Period},
		{'#', Symbol::Neq},
		{';', Symbol::Semicolon}
	};
	int Analyzer::idx = 0;
}

lexical::Analyzer* g_lexicalAnalyzer = new lexical::Analyzer; /*全局变量定义*/
inline char lexical::Analyzer::getNextChar()
{
	if (idx < str.size()) return str[idx++];
}
int lexical::Analyzer::getSymbol()
{
	char ch = ' ';
	std::string tmp;
	while (ch == ' ' || ch == '\n' || ch == '\t') /* 忽略空格、换行、回车和TAB */
	{
		ch = getNextChar();
	}
	if (ch >= 'a' && ch <= 'z') /* 名字或保留字以a..z开头 */
	{
		do {
			tmp += ch;
			ch = getNextChar();
		} while (ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9');
		id = tmp;

		if (keywordMap.count(id))
		{
			sym = keywordMap[id];
		}
		else
		{
			sym = Symbol::Ident;
		}
	}
	else if (ch >= '0' && ch <= '9') /* 检测是否为数字：以0..9开头 */
	{
		num = 0;
		sym = Symbol::Number;
		do {
			num = 10 * num + ch - '0';
			ch = getNextChar();
		} while (ch >= '0' && ch <= '9'); /* 获取数字的值 */
	}
	else if (ch == ':') /* 检测赋值符号 */
	{
		ch = getNextChar();
		if (ch == '=')
		{
			sym = Symbol::Becomes;
			ch = getNextChar();
		}
		else
		{
			sym = Symbol::Nul; /* 不能识别的符号 */
		}
     }
	else if (ch == '<')    /* 检测小于或小于等于符号 */
	{
		ch = getNextChar();
		if (ch == '=')
		{
			sym = Symbol::Eql;
			ch = getNextChar();
		}
		else
		{
			sym = Symbol::Lss;
		}
	}
	else if (ch == '>')        /* 检测大于或大于等于符号 */
	{
		ch = getNextChar();
		if (ch == '=')
		{
			sym = Symbol::Geq;
			ch = getNextChar();
		}
		else
		{
			sym = Symbol::Gtr;
		}
	}
	else
	{
		sym = singleChar[ch];    /* 当符号不满足上述条件时，全部按照单字符符号处理*/
		if (sym != Symbol::Period)
		{
			ch = getNextChar();
		}
	}
	idx--;
	return 0;
}