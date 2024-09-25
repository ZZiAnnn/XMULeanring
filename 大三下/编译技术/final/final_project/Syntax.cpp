#include "Syntax.h"
#define getSymbolDo       if (g_lexicalAnalyzer->getSymbol() == -1) return -1;
#define genCode(a, b, c)  if(-1 == gen(a, b, c)) return -1
namespace syntax {
	std::unordered_map<Opcode, std::string> mnemonic = {
		{Opcode::LIT, "lit"},
		{Opcode::OPR, "opr"},
		{Opcode::LOD, "lod"},
		{Opcode::STO, "sto"},
		{Opcode::CAL, "cal"},
		{Opcode::INT, "int"},
		{Opcode::JMP, "jmp"},
		{Opcode::JPC, "jpc"}
	};
}
/*
* 生成代码
* x: instruction.f;
* y: instruction.l;
* z: instruction.a;
*/
int syntax::Analyzer::gen(Opcode op, int l, int a)
{
	code[codeLastIndex].f = op;
	code[codeLastIndex].l = l;
	code[codeLastIndex].a = a;
	codeLastIndex++;
	return 0;
}


int syntax::Analyzer::block(int level, int& lastIndex)
{
	int offset = 3;                /* 名字分配到的相对地址 */
	int tableStart = lastIndex; /* 记录本层名字表的初始位置 */
	table[lastIndex].address = codeLastIndex;

	genCode(Opcode::JMP, 0, 0);
	do {
		if (g_lexicalAnalyzer->sym == lexical::Symbol::ConstSym)     /* 收到常量声明符号，开始处理常量声明 */
		{
			getSymbolDo;
			if (constDeclaration(lastIndex, level, offset) == -1) return -1;
			while (g_lexicalAnalyzer->sym == lexical::Symbol::Comma) /*逗号继续解析*/
			{
				getSymbolDo;
				if (constDeclaration(lastIndex, level, offset) == -1) return -1;
			}
			if (g_lexicalAnalyzer->sym == lexical::Symbol::Semicolon) /*分号结束解析*/
			{
				getSymbolDo;
			}
			else
			{
				exit(5);   /*漏掉了逗号或者分号*/
			}
		}
		if (g_lexicalAnalyzer->sym == lexical::Symbol::VarSym)  /* 收到变量声明符号，开始处理变量声明 */
		{
			getSymbolDo;
			if (varDeclaration(lastIndex, level, offset) == -1) return -1;
			while (g_lexicalAnalyzer->sym == lexical::Symbol::Comma)
			{
				getSymbolDo;
				if (varDeclaration(lastIndex, level, offset) == -1) return -1;
			}
			if (g_lexicalAnalyzer->sym == lexical::Symbol::Semicolon)
			{
				getSymbolDo;
			}
			else
			{
				exit(5);
			}
		}
		while (g_lexicalAnalyzer->sym == lexical::Symbol::ProcSym) /* 收到过程声明符号，开始处理过程声明 */
		{
			getSymbolDo;
			if (g_lexicalAnalyzer->sym == lexical::Symbol::Ident)
			{
				enter(Object::Procedur, lastIndex, level, offset);
				getSymbolDo;
			}
			else
			{
				exit(4);   /* procedure后应为标识符 */
			}

			if (g_lexicalAnalyzer->sym == lexical::Symbol::Semicolon)
			{
				getSymbolDo;
			}
			else
			{
				exit(5);   /* 漏掉了分号 */
			}

			if (-1 == block(level + 1, lastIndex))
			{
				return -1;  /* 递归调用 */
			}

			if (g_lexicalAnalyzer->sym == lexical::Symbol::Semicolon)
			{
				getSymbolDo;
			}
			else
			{
				exit(5);   /* 漏掉了分号 */
			}
		}
	} while (g_lexicalAnalyzer->sym == lexical::Symbol::ConstSym ||
			 g_lexicalAnalyzer->sym == lexical::Symbol::VarSym ||
			 g_lexicalAnalyzer->sym == lexical::Symbol::ProcSym); /* 直到没有声明符号 */

	code[table[tableStart].address].a = codeLastIndex;    /* 开始生成当前过程代码 */
	table[tableStart].address = codeLastIndex;            /* 当前过程代码地址 */
	table[tableStart].size = offset;     /* 声明部分中每增加一条声明都会给offset增加1，声明部分已经结束，offset就是当前过程数据的size */
	int codeStart = codeLastIndex;
	genCode(Opcode::INT, 0, offset);             /* 生成分配内存代码 */

	if (statement(level, lastIndex) == -1) return-1;

	genCode(Opcode::OPR, 0, 0);             /* 每个过程出口都要使用的释放数据段指令 */
	return 0;
}
void syntax::Analyzer::enter(Object type, int& lastIndex, int level, int& offset)
{
	lastIndex++;
	table[lastIndex].name = g_lexicalAnalyzer->id;
	table[lastIndex].type = type;
	switch (type)
	{
	case Object::Constant:       /* 常量名字 */
		if (g_lexicalAnalyzer->num > ADDRESS_MAX)
		{
			exit(31);           /* 数越界 */
			g_lexicalAnalyzer->num = 0;
		}
		table[lastIndex].val = g_lexicalAnalyzer->num;
		break;
	case Object::Variable:       /* 变量名字 */
		table[lastIndex].level = level;
		table[lastIndex].address = offset;
		offset++;
		break;
	case Object::Procedur:       /*　过程名字　*/
		table[lastIndex].level = level;
		break;
	}
}

int syntax::Analyzer::position(std::string name)
{
	for (int i = 0; i < table.size();++i)
	{
		if (table[i].name == name) return i;
	}
	return -1;
}

void syntax::Analyzer::listCode(int start)
{
	for (int i = start; i < codeLastIndex; ++i) {
		std::cout << i << " " << mnemonic[code[i].f] << " " << code[i].l << " " << code[i].a << std::endl;
		opCodeFile << i << " " << mnemonic[code[i].f] << " " << code[i].l << " " << code[i].a << std::endl;
	}
}

syntax::Analyzer::Analyzer()
{
	table.resize(TABLE_MAX_LEN);
	code.resize(TABLE_MAX_LEN);
}
int syntax::Analyzer::statement(int level,int &lastIndex)
{
	if (g_lexicalAnalyzer->sym == lexical::Symbol::Ident)   /* 赋值语句处理 */
	{
		int nameIndex = position(g_lexicalAnalyzer->id);
		if (nameIndex == -1)
		{
			exit(11);  /* 变量未找到 */
		}
		else
		{
			if (table[nameIndex].type != Object::Variable)
			{
				exit(12);  /* 赋值语句格式错误 */
				nameIndex = -1;
			}
			else
			{
				getSymbolDo;
				if (g_lexicalAnalyzer->sym == lexical::Symbol::Becomes)
				{
					getSymbolDo;
				}
				else
				{
					exit(13);  /* 没有检测到赋值符号 */
				}
				if (expression(level, lastIndex) == -1)return -1; /* 处理赋值符号右侧表达式 */
				if (nameIndex != -1)
				{
					/* expression将执行一系列指令，但最终结果将会保存在栈顶，执行sto命令完成赋值 */
					genCode(Opcode::STO, level - table[nameIndex].level, table[nameIndex].address);
				}
			}
		}
	}
	else if (g_lexicalAnalyzer->sym == lexical::Symbol::ReadSym) /* read语句处理 */
	{
		getSymbolDo;
		if (g_lexicalAnalyzer->sym != lexical::Symbol::LParen)
		{
			exit(34);  /* 格式错误，应是左括号 */
		}
		else
		{
			do {
				getSymbolDo;
				int nameIndex;
				if (g_lexicalAnalyzer->sym == lexical::Symbol::Ident)
				{
					nameIndex = position(g_lexicalAnalyzer->id); /* 查找要读的变量 */
				}
				else
				{
					nameIndex = -1;
				}

				if (nameIndex == -1)
				{
					exit(35);  /* read()中应是声明过的变量名 */
				}
				else if (table[nameIndex].type != Object::Variable)
				{
					exit(32);	/* read()参数表的标识符不是变量, thanks to amd */
				}
				else
				{
					genCode(Opcode::OPR, 0, 16);  /* 生成输入指令，读取值到栈顶 */
					genCode(Opcode::STO, level - table[nameIndex].level, table[nameIndex].address);
				}
				getSymbolDo;

			} while (g_lexicalAnalyzer->sym == lexical::Symbol::Comma); /* 一条read语句可读多个变量 */
		}
		if (g_lexicalAnalyzer->sym != lexical::Symbol::RParen)
		{
			exit(33);  /* 格式错误，应是右括号 */
		}
		else
		{
			getSymbolDo;
		}
	}
	else if (g_lexicalAnalyzer->sym == lexical::Symbol::WriteSym)    /* 准备按照write语句处理，与read类似 */
	{ 
		getSymbolDo;
		if (g_lexicalAnalyzer->sym == lexical::Symbol::LParen)
		{
			do {
				getSymbolDo;
				if (expression(level, lastIndex) == -1) return-1; /* 调用表达式处理，此处与read不同，read为给变量赋值 */
				genCode(Opcode::OPR, 0, 14);  /* 生成输出指令，输出栈顶的值 */
			} while (g_lexicalAnalyzer->sym == lexical::Symbol::Comma);
			if (g_lexicalAnalyzer->sym != lexical::Symbol::RParen)
			{
				exit(33);  /* write()中应为完整表达式 */
			}
			else
			{
				getSymbolDo;
			}
		}
		genCode(Opcode::OPR, 0, 15);  /* 输出换行 */
	}
	else if (g_lexicalAnalyzer->sym == lexical::Symbol::CallSym) /* call语句处理 */
	{
		getSymbolDo;
		if (g_lexicalAnalyzer->sym != lexical::Symbol::Ident)
		{
			exit(14);  /* call后应为标识符 */
		}
		else
		{
			int nameIndex = position(g_lexicalAnalyzer->id);
			if (nameIndex == -1)
			{
				exit(11);  /* 过程未找到 */
			}
			else
			{
				if (table[nameIndex].type == Object::Procedur)
				{
					genCode(Opcode::CAL, level - table[nameIndex].level, table[nameIndex].address);   /* 生成call指令 */
				}
				else
				{
					exit(15);  /* call后标识符应为过程 */
				}
			}
			getSymbolDo;
		}
	}
	else if (g_lexicalAnalyzer->sym == lexical::Symbol::IfSym)   /* if语句处理 */
	{
		getSymbolDo;
		if (condition(level, lastIndex) == -1) return -1; /* 调用条件处理（逻辑运算）函数 */
		if (g_lexicalAnalyzer->sym == lexical::Symbol::ThenSym)
		{
			getSymbolDo;
		}
		else
		{
			exit(16);  /* 缺少then */
		}
		int codeSize = code.size();   /* 保存当前指令地址 */
		genCode(Opcode::JPC, 0, 0);   /* 生成条件跳转指令，跳转地址未知，暂时写0 */
		if (statement(level, lastIndex) == -1) return -1;    /* 处理then后的语句 */
		code[codeSize].a = code.size();   /* 经statement处理后，cx为then后语句执行完的位置，它正是前面未定的跳转地址 */
	}
	else if (g_lexicalAnalyzer->sym == lexical::Symbol::BeginSym)    /* 准备按照复合语句处理 */
	{
		getSymbolDo;

		/* 循环调用语句处理函数，直到下一个符号不是语句开始符号或收到end */
		if (statement(level, lastIndex) == -1) return -1;

		while (true)
		{
			if (g_lexicalAnalyzer->sym == lexical::Symbol::EndSym)
			{
				getSymbolDo;
				break;
			}
			/*分号继续*/
			getSymbolDo;
			if (statement(level, lastIndex) == -1) return -1;
		}
	}
	else if (g_lexicalAnalyzer->sym == lexical::Symbol::WhileSym)    /* 准备按照while语句处理 */
	{
		int codeSize1 = codeLastIndex;    /* 保存判断条件操作的位置 */
		getSymbolDo;
		if (condition(level, lastIndex) == -1) return -1;  /* 调用条件处理 */
		int codeSize2 = codeLastIndex;   /* 保存循环体的结束的下一个位置 */
		genCode(Opcode::JPC, 0, 0);   /* 生成条件跳转，但跳出循环的地址未知 */
		if (g_lexicalAnalyzer->sym == lexical::Symbol::DoSym)
		{
			getSymbolDo;
		}
		else
		{
			exit(18);  /* 缺少do */
		}
		if (statement(level, lastIndex) == -1) return -1;    /* 循环体 */
		genCode(Opcode::JMP, 0, codeSize1); /* 回头重新判断条件 */
		code[codeSize2].a = codeLastIndex;   /* 反填跳出循环的地址，与if类似 */
	}
	return 0;
}

int syntax::Analyzer::expression(int level, int& lastIndex)
{
	lexical::Symbol addop;  /* 用于保存正负号 */
	if (g_lexicalAnalyzer->sym == lexical::Symbol::Plus || g_lexicalAnalyzer->sym == lexical::Symbol::Minus)
	{
		addop = g_lexicalAnalyzer->sym;    /* 保存开头的正负号 */
		getSymbolDo;
		if (term(level,lastIndex) == -1) return -1;   /* 处理项 */
		if (addop == lexical::Symbol::Minus)
		{
			genCode(Opcode::OPR, 0, 1); /* 如果开头为负号生成取负指令 */
		}
	}
	else    /* 此时表达式被看作项的加减 */
	{
		if (term(level,lastIndex) == -1) return -1;   /* 处理项 */
	}
	while (g_lexicalAnalyzer->sym == lexical::Symbol::Plus || g_lexicalAnalyzer->sym == lexical::Symbol::Minus)
	{
		addop = g_lexicalAnalyzer->sym;
		getSymbolDo;
		if (term(level,lastIndex) == -1) return -1;  /* 处理项 */
		if (addop == lexical::Symbol::Plus)
		{
			genCode(Opcode::OPR, 0, 2);   /* 生成加法指令 */
		}
		else
		{
			genCode(Opcode::OPR, 0, 3);   /* 生成减法指令 */
		}
	}
	return 0;
}

int syntax::Analyzer::term(int level,int& lastIndex)
{
	lexical::Symbol mulop;  /* 用于保存乘除法符号 */

	if(factor(level,lastIndex) == -1) return -1; /* 处理因子 */
	while (g_lexicalAnalyzer->sym == lexical::Symbol::Times || g_lexicalAnalyzer->sym == lexical::Symbol::Slash)
	{
		mulop = g_lexicalAnalyzer->sym;
		getSymbolDo;
		if (factor(level,lastIndex) == -1) return -1; /* 处理因子 */
		if (mulop == lexical::Symbol::Times)
		{
			genCode(Opcode::OPR, 0, 4);   /* 生成乘法指令 */
		}
		else
		{
			genCode(Opcode::OPR, 0, 5);    /* 生成除法指令 */
		}
	}
	return 0;
}

int syntax::Analyzer::factor(int level,int &lastIndex)
{
	if (g_lexicalAnalyzer->sym == lexical::Symbol::Ident)
	{
		int nameIndex = position(g_lexicalAnalyzer->id);
		if (nameIndex == -1)
		{
			exit(11);  /* 标识符未声明 */
		}
		else
		{
			switch (table[nameIndex].type)
			{
			case Object::Constant:  /* 名字为常量 */
				genCode(Opcode::LIT, 0, table[nameIndex].val);    /* 直接把常量的值入栈 */
				break;
			case Object::Variable:  /* 名字为变量 */
				genCode(Opcode::LOD, level - table[nameIndex].level, table[nameIndex].address);   /* 找到变量地址并将其值入栈 */
				break;
			case Object::Procedur:  /* 名字为过程 */
				exit(21);  /* 不能为过程 */
				break;
			}
		}
		getSymbolDo;
	}
	else if (g_lexicalAnalyzer->sym == lexical::Symbol::Number)
	{
		genCode(Opcode::LIT, 0, g_lexicalAnalyzer->num);
		getSymbolDo;
	}
	else if (g_lexicalAnalyzer->sym == lexical::Symbol::LParen)
	{
		getSymbolDo;
		if (expression(level,lastIndex) == -1) return -1;
		if (g_lexicalAnalyzer->sym == lexical::Symbol::RParen)
		{
			getSymbolDo;
		}
		else
		{
			exit(22);  /* 缺少右括号 */
		}
	}
	return 0;
}

int syntax::Analyzer::condition(int level,int& lastIndex)
{
	if (g_lexicalAnalyzer->sym == lexical::Symbol::OddSym)   /* odd运算处理 */
	{
		getSymbolDo;
		if (expression(level,lastIndex) == -1) return -1;
		genCode(Opcode::OPR, 0, 6);   /* 生成odd指令 */
	}
	else
	{
		/* 逻辑表达式处理 */
		if (expression(level, lastIndex) == -1) return -1;

		lexical::Symbol relop = g_lexicalAnalyzer->sym;
		getSymbolDo;
		if (expression(level, lastIndex) == -1) return -1;

		switch (relop)
		{
		case lexical::Symbol::Eql:
			genCode(Opcode::OPR, 0, 8);
			break;
		case lexical::Symbol::Neq:
			genCode(Opcode::OPR, 0, 9);
			break;
		case lexical::Symbol::Lss:
			genCode(Opcode::OPR, 0, 10);
			break;
		case lexical::Symbol::Geq:
			genCode(Opcode::OPR, 0, 11);
			break;
		case lexical::Symbol::Gtr:
			genCode(Opcode::OPR, 0, 12);
			break;
		case lexical::Symbol::Leq:
			genCode(Opcode::OPR, 0, 13);
			break;
		default:
			exit(20);
		}
	}
	return 0;
}

int syntax::Analyzer::constDeclaration(int& lastIndex, int level,int& offset)
{
	if (g_lexicalAnalyzer->sym == lexical::Symbol::Ident)
	{
		getSymbolDo;
		if (g_lexicalAnalyzer->sym == lexical::Symbol::Eql|| g_lexicalAnalyzer->sym == lexical::Symbol::Becomes)
		{
			if (g_lexicalAnalyzer->sym == lexical::Symbol::Becomes)
			{
				exit(1);   /* 把=写成了:= */
			}
			getSymbolDo;
			if (g_lexicalAnalyzer->sym == lexical::Symbol::Number)
			{
				enter(Object::Constant, lastIndex, level, offset);
				getSymbolDo;
			}
			else
			{
				exit(2);   /* 常量说明=后应是数字 */
			}
		}
		else
		{
			exit(3);   /* 常量说明标识后应是= */
		}
	}
	else
	{
		exit(4);   /* const后应是标识 */
	}
	return 0;
}

int syntax::Analyzer::varDeclaration(int& lastIndex, int level, int& offset)
{
	if (g_lexicalAnalyzer->sym == lexical::Symbol::Ident)
	{
		enter(Object::Variable, lastIndex, level, offset);
		getSymbolDo;
	}
	else
	{
		exit(4);   /* var后应是标识 */
	}
	return 0;
}

void syntax::Analyzer::start()
{
	int tableIndex = 0;
	if (g_lexicalAnalyzer->getSymbol() != -1)
	{
		if (-1 == block(0, tableIndex))   /* 调用编译程序 */
		{
			printf("\n");
			return;
		}
		if (g_lexicalAnalyzer->sym != lexical::Symbol::Period)
		{
			exit(9);
		}
	}
	std::cout << "TABLE:" << std::endl;    /* 输出名字表 */
	for (int i = 0; i <= tableIndex; ++i) {
		const TableItem& entry = table[i];
		switch (entry.type) {
		case Object::Constant:
			std::cout << "    " << i << " const " << entry.name << " ";
			std::cout << "val=" << entry.val << std::endl;
			tableFile << "    " << i << " const " << entry.name << " ";
			tableFile << "val=" << entry.val << std::endl;
			break;
		case Object::Variable:
			std::cout << "    " << i << " var   " << entry.name << " ";
			std::cout << "lev=" << entry.level << " addr=" << entry.address << std::endl;
			tableFile << "    " << i << " var   " << entry.name << " ";
			tableFile << "lev=" << entry.level << " addr=" << entry.address << std::endl;
			break;
		case Object::Procedur:
			std::cout << "    " << i << " proc  " << entry.name << " ";
			std::cout << "lev=" << entry.level << " addr=" << entry.address << " size=" << entry.size << std::endl;
			tableFile << "    " << i << " proc  " << entry.name << " ";
			tableFile << "lev=" << entry.level << " addr=" << entry.address << " size=" << entry.size << std::endl;
			break;
		}
	}
	std::cout << std::endl;
	std::cout << "P-Code:" << std::endl;
	listCode(0);                    /* 输出代码 */
}
