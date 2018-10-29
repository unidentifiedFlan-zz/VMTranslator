#include "stdafx.h"
#include "pushTranslator.h"


pushTranslator::pushTranslator(std::fstream &fileStream, std::string &currentFile, std::string &segment, std::string &command, int &argTwo) : 
							   asmFile(fileStream), currentCommand(command), arg2(argTwo)
{
	if (segment == "constant") {
		pushConstant();
	}
	else if (segment == "local") {
		pushLocal();
	}
	else if (segment == "argument") {
		pushArgument();
	}
	else if (segment == "this") {
		pushThis();
	}
	else if (segment == "that") {
		pushThat();
	}
	else if (segment == "temp") {
		pushTemp();
	}
	else if (segment == "static") {
		pushStatic(currentFile);
	}
	else if (segment == "pointer") {
		pushPointer();
	}

	else
		std::cout << "Error: memory segment invalid";

	//Add to stack and shift stack pointer
	asmFile << "@SP" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "M=D" << '\n';
	asmFile << "@SP" << '\n';
	asmFile << "M=M+1" << '\n';
}

void pushTranslator::pushConstant() {
	asmFile << '@' << arg2 << '\t' << "//" << currentCommand << '\n';
	asmFile << "D=A" << '\n';
}

void pushTranslator::pushLocal() {
	asmFile << "@" << arg2 << '\t' << "//" << currentCommand << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@LCL" << '\n';
	asmFile << "A=M+D" << '\n';
	asmFile << "D=M" << '\n';
}

void pushTranslator::pushArgument() {
	asmFile << "@" << arg2 << '\t' << "//" << currentCommand << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@ARG" << '\n';
	asmFile << "A=M+D" << '\n';
	asmFile << "D=M" << '\n';
}

void pushTranslator::pushThis() {
	asmFile << "@" << arg2 << '\t' << "//" << currentCommand << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@THIS" << '\n';
	asmFile << "A=M+D" << '\n';
	asmFile << "D=M" << '\n';
}

void pushTranslator::pushThat() {
	asmFile << "@" << arg2 << '\t' << "//" << currentCommand << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@THAT" << '\n';
	asmFile << "A=M+D" << '\n';
	asmFile << "D=M" << '\n';
}

void pushTranslator::pushTemp() {
	asmFile << "@" << arg2 << '\t' << "//" << currentCommand << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@5" << '\n';
	asmFile << "A=A+D" << '\n';
	asmFile << "D=M" << '\n';
}

void pushTranslator::pushStatic(std::string &currentFile) {
	asmFile << "@" << currentFile << "." << arg2 << '\t' << "//" << currentCommand << '\n';
	asmFile << "D=M" << '\n';
}

void pushTranslator::pushPointer() {
	if (arg2 == 0)
		asmFile << '@' << "THIS" << '\t' << "//" << currentCommand << '\n';

	if (arg2 == 1)
		asmFile << '@' << "THAT" << '\t' << "//" << currentCommand << '\n';

	asmFile << "D=M" << '\n';
}

pushTranslator::~pushTranslator()
{
}
