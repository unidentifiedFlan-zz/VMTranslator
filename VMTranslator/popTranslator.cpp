#include "stdafx.h"
#include "popTranslator.h"


popTranslator::popTranslator(std::fstream &fileStream, std::string &currentFile, std::string &segment, std::string &currCmd, int &argTwo) : 
							asmFile(fileStream), currentCommand(currCmd), arg2(argTwo)
{

	if (segment == "constant") {
		popConstant();
	}
	else if (segment == "local") {
		popLocal();
	}
	else if (segment == "argument") {
		popArgument();
	}
	else if (segment == "this") {
		popThis();
	}
	else if (segment == "that") {
		popThat();
	}
	else if (segment == "temp") {
		popTemp();
	}
	else if (segment == "static") {
		popStatic(currentFile);
	}
	else if (segment == "pointer") {
		popPointer();
	}

	asmFile << "@SP" << '\n';
}

void popTranslator::popConstant() {
	asmFile << "M=M-1" << '\t' << "//" << currentCommand << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "D=M" << '\n';
	asmFile << '@' << arg2 << '\n';
	asmFile << "M=D" << '\n';
}

void popTranslator::popLocal() {
	asmFile << "@" << arg2 << '\t' << "//" << currentCommand << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@LCL" << '\n';
	asmFile << "A=M+D" << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "M=D" << '\n';
	asmFile << "@SP" << '\n';
	asmFile << "M=M-1" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "D=M" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "M=D" << '\n';
}

void popTranslator::popArgument() {
	asmFile << "@" << arg2 << '\t' << "//" << currentCommand << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@ARG" << '\n';
	asmFile << "A=M+D" << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "M=D" << '\n';
	asmFile << "@SP" << '\n';
	asmFile << "M=M-1" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "D=M" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "M=D" << '\n';
}

void popTranslator::popThis() {
	asmFile << "@" << arg2 << '\t' << "//" << currentCommand << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@THIS" << '\n';
	asmFile << "A=M+D" << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "M=D" << '\n';
	asmFile << "@SP" << '\n';
	asmFile << "M=M-1" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "D=M" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "M=D" << '\n';
}

void popTranslator::popThat() {
	asmFile << "@" << arg2 << '\t' << "//" << currentCommand << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@THAT" << '\n';
	asmFile << "A=M+D" << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "M=D" << '\n';
	asmFile << "@SP" << '\n';
	asmFile << "M=M-1" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "D=M" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "M=D" << '\n';
}

void popTranslator::popTemp() {
	asmFile << "@" << arg2 << '\t' << "//" << currentCommand << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@5" << '\n';
	asmFile << "A=A+D" << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "M=D" << '\n';
	asmFile << "@SP" << '\n';
	asmFile << "M=M-1" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "D=M" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "M=D" << '\n';
}

void popTranslator::popStatic(std::string &currentFile) {
	asmFile << "@" << currentFile << "." << arg2 << '\t' << "//" << currentCommand << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "M=D" << '\n';
	asmFile << "@SP" << '\n';
	asmFile << "M=M-1" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "D=M" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "M=D" << '\n';
}

void popTranslator::popPointer() {
	asmFile << "M=M-1" << '\t' << "//" << currentCommand << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "D=M" << '\n';

	std::cout << "arg2 =" << arg2 << std::endl;
	if (arg2 == 0)
		asmFile << "@THIS" << '\n';

	else if (arg2 == 1)
		asmFile << "@THAT" << '\n';

	else
		std::cout << "Error: Pointer not identified" << std::endl;

	asmFile << "M=D" << '\n';
}

popTranslator::~popTranslator()
{
}
