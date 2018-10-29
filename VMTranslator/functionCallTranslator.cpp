#include "stdafx.h"
#include "functionCallTranslator.h"


functionCallTranslator::functionCallTranslator(std::fstream &fileStream, std::string &currCmd, std::string &argOne, int &argTwo, int &count) : 
												asmFile(fileStream), currentCommand(currCmd), arg1(argOne), arg2(argTwo), callCount(count)
{
	saveReturnAddr();

	//save LCL, ARG, THIS, THAT on stack
	saveVariables();

	assignNewArg();
	assignNewLocal();
	createReturnLabel();

}

void functionCallTranslator::saveReturnAddr() {
	asmFile << "@" << arg1 << "$ret." << callCount << '\t' << "//" << currentCommand << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@SP" << '\n';
	asmFile << "M=M+1" << '\n';
	asmFile << "A=M-1" << '\n';
	asmFile << "M=D" << '\n';
}

void functionCallTranslator::saveVariables() {
	for (int i = 1; i < 5; i++) {
		asmFile << "@" << i << '\n';
		asmFile << "D=M" << '\n';
		asmFile << "@SP" << '\n';
		asmFile << "M=M+1" << '\n';
		asmFile << "A=M-1" << '\n';
		asmFile << "M=D" << '\n';
	}
}

void functionCallTranslator::assignNewArg() {
	asmFile << "@5" << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "M=D" << '\n';
	asmFile << "@" << arg2 << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "D=M+D" << '\n';
	asmFile << "@SP" << '\n';
	asmFile << "D=M-D" << '\n';
	asmFile << "@ARG" << '\n';
	asmFile << "M=D" << '\n';
}

void functionCallTranslator::assignNewLocal() {
	asmFile << "@SP" << '\n';
	asmFile << "D=M" << '\n';
	asmFile << "@LCL" << '\n';
	asmFile << "M=D" << '\n';
}

void functionCallTranslator::createReturnLabel() {
	asmFile << "@" << arg1 << '\n';
	asmFile << "0;JMP" << '\n';
	asmFile << "(" << arg1 << "$ret." << callCount << ")" << '\n';
}

functionCallTranslator::~functionCallTranslator()
{
}
