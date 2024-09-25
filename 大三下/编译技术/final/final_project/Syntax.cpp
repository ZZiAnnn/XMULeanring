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
* ���ɴ���
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
	int offset = 3;                /* ���ַ��䵽����Ե�ַ */
	int tableStart = lastIndex; /* ��¼�������ֱ�ĳ�ʼλ�� */
	table[lastIndex].address = codeLastIndex;

	genCode(Opcode::JMP, 0, 0);
	do {
		if (g_lexicalAnalyzer->sym == lexical::Symbol::ConstSym)     /* �յ������������ţ���ʼ���������� */
		{
			getSymbolDo;
			if (constDeclaration(lastIndex, level, offset) == -1) return -1;
			while (g_lexicalAnalyzer->sym == lexical::Symbol::Comma) /*���ż�������*/
			{
				getSymbolDo;
				if (constDeclaration(lastIndex, level, offset) == -1) return -1;
			}
			if (g_lexicalAnalyzer->sym == lexical::Symbol::Semicolon) /*�ֺŽ�������*/
			{
				getSymbolDo;
			}
			else
			{
				exit(5);   /*©���˶��Ż��߷ֺ�*/
			}
		}
		if (g_lexicalAnalyzer->sym == lexical::Symbol::VarSym)  /* �յ������������ţ���ʼ����������� */
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
		while (g_lexicalAnalyzer->sym == lexical::Symbol::ProcSym) /* �յ������������ţ���ʼ����������� */
		{
			getSymbolDo;
			if (g_lexicalAnalyzer->sym == lexical::Symbol::Ident)
			{
				enter(Object::Procedur, lastIndex, level, offset);
				getSymbolDo;
			}
			else
			{
				exit(4);   /* procedure��ӦΪ��ʶ�� */
			}

			if (g_lexicalAnalyzer->sym == lexical::Symbol::Semicolon)
			{
				getSymbolDo;
			}
			else
			{
				exit(5);   /* ©���˷ֺ� */
			}

			if (-1 == block(level + 1, lastIndex))
			{
				return -1;  /* �ݹ���� */
			}

			if (g_lexicalAnalyzer->sym == lexical::Symbol::Semicolon)
			{
				getSymbolDo;
			}
			else
			{
				exit(5);   /* ©���˷ֺ� */
			}
		}
	} while (g_lexicalAnalyzer->sym == lexical::Symbol::ConstSym ||
			 g_lexicalAnalyzer->sym == lexical::Symbol::VarSym ||
			 g_lexicalAnalyzer->sym == lexical::Symbol::ProcSym); /* ֱ��û���������� */

	code[table[tableStart].address].a = codeLastIndex;    /* ��ʼ���ɵ�ǰ���̴��� */
	table[tableStart].address = codeLastIndex;            /* ��ǰ���̴����ַ */
	table[tableStart].size = offset;     /* ����������ÿ����һ�����������offset����1�����������Ѿ�������offset���ǵ�ǰ�������ݵ�size */
	int codeStart = codeLastIndex;
	genCode(Opcode::INT, 0, offset);             /* ���ɷ����ڴ���� */

	if (statement(level, lastIndex) == -1) return-1;

	genCode(Opcode::OPR, 0, 0);             /* ÿ�����̳��ڶ�Ҫʹ�õ��ͷ����ݶ�ָ�� */
	return 0;
}
void syntax::Analyzer::enter(Object type, int& lastIndex, int level, int& offset)
{
	lastIndex++;
	table[lastIndex].name = g_lexicalAnalyzer->id;
	table[lastIndex].type = type;
	switch (type)
	{
	case Object::Constant:       /* �������� */
		if (g_lexicalAnalyzer->num > ADDRESS_MAX)
		{
			exit(31);           /* ��Խ�� */
			g_lexicalAnalyzer->num = 0;
		}
		table[lastIndex].val = g_lexicalAnalyzer->num;
		break;
	case Object::Variable:       /* �������� */
		table[lastIndex].level = level;
		table[lastIndex].address = offset;
		offset++;
		break;
	case Object::Procedur:       /*���������֡�*/
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
	if (g_lexicalAnalyzer->sym == lexical::Symbol::Ident)   /* ��ֵ��䴦�� */
	{
		int nameIndex = position(g_lexicalAnalyzer->id);
		if (nameIndex == -1)
		{
			exit(11);  /* ����δ�ҵ� */
		}
		else
		{
			if (table[nameIndex].type != Object::Variable)
			{
				exit(12);  /* ��ֵ����ʽ���� */
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
					exit(13);  /* û�м�⵽��ֵ���� */
				}
				if (expression(level, lastIndex) == -1)return -1; /* ����ֵ�����Ҳ���ʽ */
				if (nameIndex != -1)
				{
					/* expression��ִ��һϵ��ָ������ս�����ᱣ����ջ����ִ��sto������ɸ�ֵ */
					genCode(Opcode::STO, level - table[nameIndex].level, table[nameIndex].address);
				}
			}
		}
	}
	else if (g_lexicalAnalyzer->sym == lexical::Symbol::ReadSym) /* read��䴦�� */
	{
		getSymbolDo;
		if (g_lexicalAnalyzer->sym != lexical::Symbol::LParen)
		{
			exit(34);  /* ��ʽ����Ӧ�������� */
		}
		else
		{
			do {
				getSymbolDo;
				int nameIndex;
				if (g_lexicalAnalyzer->sym == lexical::Symbol::Ident)
				{
					nameIndex = position(g_lexicalAnalyzer->id); /* ����Ҫ���ı��� */
				}
				else
				{
					nameIndex = -1;
				}

				if (nameIndex == -1)
				{
					exit(35);  /* read()��Ӧ���������ı����� */
				}
				else if (table[nameIndex].type != Object::Variable)
				{
					exit(32);	/* read()������ı�ʶ�����Ǳ���, thanks to amd */
				}
				else
				{
					genCode(Opcode::OPR, 0, 16);  /* ��������ָ���ȡֵ��ջ�� */
					genCode(Opcode::STO, level - table[nameIndex].level, table[nameIndex].address);
				}
				getSymbolDo;

			} while (g_lexicalAnalyzer->sym == lexical::Symbol::Comma); /* һ��read���ɶ�������� */
		}
		if (g_lexicalAnalyzer->sym != lexical::Symbol::RParen)
		{
			exit(33);  /* ��ʽ����Ӧ�������� */
		}
		else
		{
			getSymbolDo;
		}
	}
	else if (g_lexicalAnalyzer->sym == lexical::Symbol::WriteSym)    /* ׼������write��䴦����read���� */
	{ 
		getSymbolDo;
		if (g_lexicalAnalyzer->sym == lexical::Symbol::LParen)
		{
			do {
				getSymbolDo;
				if (expression(level, lastIndex) == -1) return-1; /* ���ñ��ʽ�����˴���read��ͬ��readΪ��������ֵ */
				genCode(Opcode::OPR, 0, 14);  /* �������ָ����ջ����ֵ */
			} while (g_lexicalAnalyzer->sym == lexical::Symbol::Comma);
			if (g_lexicalAnalyzer->sym != lexical::Symbol::RParen)
			{
				exit(33);  /* write()��ӦΪ�������ʽ */
			}
			else
			{
				getSymbolDo;
			}
		}
		genCode(Opcode::OPR, 0, 15);  /* ������� */
	}
	else if (g_lexicalAnalyzer->sym == lexical::Symbol::CallSym) /* call��䴦�� */
	{
		getSymbolDo;
		if (g_lexicalAnalyzer->sym != lexical::Symbol::Ident)
		{
			exit(14);  /* call��ӦΪ��ʶ�� */
		}
		else
		{
			int nameIndex = position(g_lexicalAnalyzer->id);
			if (nameIndex == -1)
			{
				exit(11);  /* ����δ�ҵ� */
			}
			else
			{
				if (table[nameIndex].type == Object::Procedur)
				{
					genCode(Opcode::CAL, level - table[nameIndex].level, table[nameIndex].address);   /* ����callָ�� */
				}
				else
				{
					exit(15);  /* call���ʶ��ӦΪ���� */
				}
			}
			getSymbolDo;
		}
	}
	else if (g_lexicalAnalyzer->sym == lexical::Symbol::IfSym)   /* if��䴦�� */
	{
		getSymbolDo;
		if (condition(level, lastIndex) == -1) return -1; /* �������������߼����㣩���� */
		if (g_lexicalAnalyzer->sym == lexical::Symbol::ThenSym)
		{
			getSymbolDo;
		}
		else
		{
			exit(16);  /* ȱ��then */
		}
		int codeSize = code.size();   /* ���浱ǰָ���ַ */
		genCode(Opcode::JPC, 0, 0);   /* ����������תָ���ת��ַδ֪����ʱд0 */
		if (statement(level, lastIndex) == -1) return -1;    /* ����then������ */
		code[codeSize].a = code.size();   /* ��statement�����cxΪthen�����ִ�����λ�ã�������ǰ��δ������ת��ַ */
	}
	else if (g_lexicalAnalyzer->sym == lexical::Symbol::BeginSym)    /* ׼�����ո�����䴦�� */
	{
		getSymbolDo;

		/* ѭ��������䴦������ֱ����һ�����Ų�����俪ʼ���Ż��յ�end */
		if (statement(level, lastIndex) == -1) return -1;

		while (true)
		{
			if (g_lexicalAnalyzer->sym == lexical::Symbol::EndSym)
			{
				getSymbolDo;
				break;
			}
			/*�ֺż���*/
			getSymbolDo;
			if (statement(level, lastIndex) == -1) return -1;
		}
	}
	else if (g_lexicalAnalyzer->sym == lexical::Symbol::WhileSym)    /* ׼������while��䴦�� */
	{
		int codeSize1 = codeLastIndex;    /* �����ж�����������λ�� */
		getSymbolDo;
		if (condition(level, lastIndex) == -1) return -1;  /* ������������ */
		int codeSize2 = codeLastIndex;   /* ����ѭ����Ľ�������һ��λ�� */
		genCode(Opcode::JPC, 0, 0);   /* ����������ת��������ѭ���ĵ�ַδ֪ */
		if (g_lexicalAnalyzer->sym == lexical::Symbol::DoSym)
		{
			getSymbolDo;
		}
		else
		{
			exit(18);  /* ȱ��do */
		}
		if (statement(level, lastIndex) == -1) return -1;    /* ѭ���� */
		genCode(Opcode::JMP, 0, codeSize1); /* ��ͷ�����ж����� */
		code[codeSize2].a = codeLastIndex;   /* ��������ѭ���ĵ�ַ����if���� */
	}
	return 0;
}

int syntax::Analyzer::expression(int level, int& lastIndex)
{
	lexical::Symbol addop;  /* ���ڱ��������� */
	if (g_lexicalAnalyzer->sym == lexical::Symbol::Plus || g_lexicalAnalyzer->sym == lexical::Symbol::Minus)
	{
		addop = g_lexicalAnalyzer->sym;    /* ���濪ͷ�������� */
		getSymbolDo;
		if (term(level,lastIndex) == -1) return -1;   /* ������ */
		if (addop == lexical::Symbol::Minus)
		{
			genCode(Opcode::OPR, 0, 1); /* �����ͷΪ��������ȡ��ָ�� */
		}
	}
	else    /* ��ʱ���ʽ��������ļӼ� */
	{
		if (term(level,lastIndex) == -1) return -1;   /* ������ */
	}
	while (g_lexicalAnalyzer->sym == lexical::Symbol::Plus || g_lexicalAnalyzer->sym == lexical::Symbol::Minus)
	{
		addop = g_lexicalAnalyzer->sym;
		getSymbolDo;
		if (term(level,lastIndex) == -1) return -1;  /* ������ */
		if (addop == lexical::Symbol::Plus)
		{
			genCode(Opcode::OPR, 0, 2);   /* ���ɼӷ�ָ�� */
		}
		else
		{
			genCode(Opcode::OPR, 0, 3);   /* ���ɼ���ָ�� */
		}
	}
	return 0;
}

int syntax::Analyzer::term(int level,int& lastIndex)
{
	lexical::Symbol mulop;  /* ���ڱ���˳������� */

	if(factor(level,lastIndex) == -1) return -1; /* �������� */
	while (g_lexicalAnalyzer->sym == lexical::Symbol::Times || g_lexicalAnalyzer->sym == lexical::Symbol::Slash)
	{
		mulop = g_lexicalAnalyzer->sym;
		getSymbolDo;
		if (factor(level,lastIndex) == -1) return -1; /* �������� */
		if (mulop == lexical::Symbol::Times)
		{
			genCode(Opcode::OPR, 0, 4);   /* ���ɳ˷�ָ�� */
		}
		else
		{
			genCode(Opcode::OPR, 0, 5);    /* ���ɳ���ָ�� */
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
			exit(11);  /* ��ʶ��δ���� */
		}
		else
		{
			switch (table[nameIndex].type)
			{
			case Object::Constant:  /* ����Ϊ���� */
				genCode(Opcode::LIT, 0, table[nameIndex].val);    /* ֱ�Ӱѳ�����ֵ��ջ */
				break;
			case Object::Variable:  /* ����Ϊ���� */
				genCode(Opcode::LOD, level - table[nameIndex].level, table[nameIndex].address);   /* �ҵ�������ַ������ֵ��ջ */
				break;
			case Object::Procedur:  /* ����Ϊ���� */
				exit(21);  /* ����Ϊ���� */
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
			exit(22);  /* ȱ�������� */
		}
	}
	return 0;
}

int syntax::Analyzer::condition(int level,int& lastIndex)
{
	if (g_lexicalAnalyzer->sym == lexical::Symbol::OddSym)   /* odd���㴦�� */
	{
		getSymbolDo;
		if (expression(level,lastIndex) == -1) return -1;
		genCode(Opcode::OPR, 0, 6);   /* ����oddָ�� */
	}
	else
	{
		/* �߼����ʽ���� */
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
				exit(1);   /* ��=д����:= */
			}
			getSymbolDo;
			if (g_lexicalAnalyzer->sym == lexical::Symbol::Number)
			{
				enter(Object::Constant, lastIndex, level, offset);
				getSymbolDo;
			}
			else
			{
				exit(2);   /* ����˵��=��Ӧ������ */
			}
		}
		else
		{
			exit(3);   /* ����˵����ʶ��Ӧ��= */
		}
	}
	else
	{
		exit(4);   /* const��Ӧ�Ǳ�ʶ */
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
		exit(4);   /* var��Ӧ�Ǳ�ʶ */
	}
	return 0;
}

void syntax::Analyzer::start()
{
	int tableIndex = 0;
	if (g_lexicalAnalyzer->getSymbol() != -1)
	{
		if (-1 == block(0, tableIndex))   /* ���ñ������ */
		{
			printf("\n");
			return;
		}
		if (g_lexicalAnalyzer->sym != lexical::Symbol::Period)
		{
			exit(9);
		}
	}
	std::cout << "TABLE:" << std::endl;    /* ������ֱ� */
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
	listCode(0);                    /* ������� */
}
