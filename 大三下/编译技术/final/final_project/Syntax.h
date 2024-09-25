#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <bitset>
#include <fstream>
#include "Lexical.h"

/*�﷨�������*/
namespace syntax
{
    const int ADDRESS_MAX = 2047;   /* ��ַ�Ͻ�*/
    const int TABLE_MAX_LEN = 1024;

    /* ���ֱ��е����� */
    enum class Object {
        Constant,
        Variable,
        Procedur,
    };

    /* ��������� */
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

    /* ���������ṹ */
    struct instruction
    {
        Opcode f; /* ���������ָ�� */
        int l;      /* ���ò���������Ĳ�β� */
        int a;      /* ����f�Ĳ�ͬ����ͬ */
    };

    extern std::unordered_map<Opcode, std::string> mnemonic;

    class TableItem {
    public:
        std::string name;   /* ���� */
        Object type;        /* ���ͣ�const, var, or procedure */
        int val;            /* ��ֵ����constʹ�� */
        int level;          /* �����㣬��const��ʹ�� */
        int address;        /* ��ַ����const��ʹ�� */
        int size;           /* ��Ҫ������������ռ�, ��procedureʹ�� */
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