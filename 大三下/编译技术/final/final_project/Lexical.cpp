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

lexical::Analyzer* g_lexicalAnalyzer = new lexical::Analyzer; /*ȫ�ֱ�������*/
inline char lexical::Analyzer::getNextChar()
{
	if (idx < str.size()) return str[idx++];
}
int lexical::Analyzer::getSymbol()
{
	char ch = ' ';
	std::string tmp;
	while (ch == ' ' || ch == '\n' || ch == '\t') /* ���Կո񡢻��С��س���TAB */
	{
		ch = getNextChar();
	}
	if (ch >= 'a' && ch <= 'z') /* ���ֻ�������a..z��ͷ */
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
	else if (ch >= '0' && ch <= '9') /* ����Ƿ�Ϊ���֣���0..9��ͷ */
	{
		num = 0;
		sym = Symbol::Number;
		do {
			num = 10 * num + ch - '0';
			ch = getNextChar();
		} while (ch >= '0' && ch <= '9'); /* ��ȡ���ֵ�ֵ */
	}
	else if (ch == ':') /* ��⸳ֵ���� */
	{
		ch = getNextChar();
		if (ch == '=')
		{
			sym = Symbol::Becomes;
			ch = getNextChar();
		}
		else
		{
			sym = Symbol::Nul; /* ����ʶ��ķ��� */
		}
     }
	else if (ch == '<')    /* ���С�ڻ�С�ڵ��ڷ��� */
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
	else if (ch == '>')        /* �����ڻ���ڵ��ڷ��� */
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
		sym = singleChar[ch];    /* �����Ų�������������ʱ��ȫ�����յ��ַ����Ŵ���*/
		if (sym != Symbol::Period)
		{
			ch = getNextChar();
		}
	}
	idx--;
	return 0;
}