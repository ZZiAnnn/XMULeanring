#pragma once
#include <string>
#include <unordered_map>

/*�ʷ�����*/
namespace lexical {
    enum class Symbol {
        Nul, Ident, Number, Plus, Minus,
        Times, Slash, OddSym, Eql, Neq,
        Lss, Leq, Gtr, Geq, LParen,
        RParen, Comma, Semicolon, Period, Becomes,
        BeginSym, EndSym, IfSym, ThenSym, WhileSym,
        WriteSym, ReadSym, DoSym, CallSym, ConstSym,
        VarSym, ProcSym, PlusPlus, MinusMinus
    };
    const int SYM_NUM = 34;

    /*�ؼ���*/
    extern std::unordered_map<std::string, Symbol> keywordMap;

    /*���ַ�*/
    extern std::unordered_map<char, Symbol> singleChar;

    class Analyzer {
    public:
        Symbol sym;
        std::string id;
        int num;
        static int idx;
        std::string str; /*���������ַ���*/

        char getNextChar();
        int getSymbol();
    };
}
extern lexical::Analyzer* g_lexicalAnalyzer; /*ȫ�ֱ���ʵ�ֵ���*/