#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <bitset>
#include <fstream>
#include "Lexical.h"

/*语法语义分析*/
namespace syntax
{
    const int ADDRESS_MAX = 2047;   /* 地址上界*/
    const int TABLE_MAX_LEN = 1024;

    /* 名字表中的类型 */
    enum class Object {
        Constant,
        Variable,
        Procedur,
    };

    /* 虚拟机代码 */
    enum class Opcode {
        LIT, // Load a literal
        OPR, // Execute an operation
        LOD, // Load a variable
        STO, // Store a variable
        CAL, // Call a procedure
        INT, // Increment the stack pointer
        JMP, // Jump to an address
        JPC  // Jump to an address if the condition is false
    };

    /* 虚拟机代码结构 */
    struct instruction
    {
        Opcode f; /* 虚拟机代码指令 */
        int l;      /* 引用层与声明层的层次差 */
        int a;      /* 根据f的不同而不同 */
    };

    extern std::unordered_map<Opcode, std::string> mnemonic;

    class TableItem {
    public:
        std::string name;   /* 名字 */
        Object type;        /* 类型：const, var, or procedure */
        int val;            /* 数值，仅const使用 */
        int level;          /* 所处层，仅const不使用 */
        int address;        /* 地址，仅const不使用 */
        int size;           /* 需要分配的数据区空间, 仅procedure使用 */
    };
    class Analyzer {
    private:
        int codeLastIndex = 0;
        void listCode(int start);
        std::vector<TableItem> table;
        void enter(Object type, int& lastIndex, int level, int& offset);
        int position(std::string name);
        int factor(int level, int& lastIndex );
        int gen(Opcode, int l, int a);
        int expression(int level, int& lastIndex);
        int condition(int level, int& lastIndex);
        int block(int level, int& lastIndex );
        int term(int level,int& lastIndex );
        int statement(int level, int& lastIndex );
        int test(std::bitset<lexical::SYM_NUM> s1, std::bitset<lexical::SYM_NUM> s2, int n);
        std::vector<instruction> code;
        int constDeclaration(int& lastIndex, int level, int& offset);
        int varDeclaration(int& lastIndex, int level, int& offset);
    public:
        Analyzer();
        std::fstream tableFile;
        std::fstream opCodeFile;
        void start();
    };
}