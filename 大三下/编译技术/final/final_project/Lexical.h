#pragma once
#include <string>
#include <unordered_map>

/*词法分析*/
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

    /*关键字*/
    extern std::unordered_map<std::string, Symbol> keywordMap;

    /*单字符*/
    extern std::unordered_map<char, Symbol> singleChar;

    class Analyzer {
    public:
        Symbol sym;
        std::string id;
        int num;
        static int idx;
        std::string str; /*待解析的字符串*/

        char getNextChar();
        int getSymbol();
    };
}
extern lexical::Analyzer* g_lexicalAnalyzer; /*全局变量实现单例*/