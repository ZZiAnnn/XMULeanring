#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Syntax.h"
int main()
{
	std::string sourceCodePath = "./test.txt";
	std::string tableFilePath = "./name_table.txt";/* Êä³öÃû×Ö±í */
	std::string opCodePath = "./opcode.txt";

	std::fstream file;
	file.open(sourceCodePath);

	if (!file.is_open()) {
		std::cout << "Can't open file!" << std::endl;
		return 1;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	g_lexicalAnalyzer->str = buffer.str();

	file.close(); 

	syntax::Analyzer syntaxAnalyzer;
	syntaxAnalyzer.tableFile.open(tableFilePath);
	syntaxAnalyzer.opCodeFile.open(opCodePath);

	syntaxAnalyzer.start();
	return 0;
}