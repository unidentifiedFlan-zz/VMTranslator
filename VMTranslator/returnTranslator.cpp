#include "stdafx.h"
#include "returnTranslator.h"


returnTranslator::returnTranslator(std::fstream &fileStream, std::string &currCmd) : asmFile(fileStream), currentCommand(currCmd)
{
	setEndFrame();
	setReturnAddr();
	returnOutputToArg();

	//Restore LCL, ARG, THIS, THAT pointer locations
	restorePointers();

	asmFile << "@R14" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "0;JMP" << '\n';

	asmFile << "@SP" << '\n';
}

void returnTranslator::setEndFrame() {
	asmFile << "@LCL" << '\t' << "//" << currentCommand << '\n';
	asmFile << "D=M" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "M=D" << '\n';
}

void returnTranslator::setReturnAddr() {
	asmFile << "@5" << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@R13" << '\n';
	asmFile << "A=M-D" << '\n';
	asmFile << "D=M" << '\n';
	asmFile << "@R14" << '\n';
	asmFile << "M=D" << '\n';
}

void returnTranslator::returnOutputToArg() {
	asmFile << "@SP" << '\n';
	asmFile << "A=M-1" << '\n';
	asmFile << "D=M" << '\n';
	asmFile << "@ARG" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "M=D" << '\n';
	asmFile << "A=A+1" << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@SP" << '\n';
	asmFile << "M=D" << '\n';
}

void returnTranslator::restorePointers() {
	for (int i = 1; i < 5; i++) {

		asmFile << "@" << i << '\n';
		asmFile << "D=A" << '\n';
		asmFile << "@R13" << '\n';
		asmFile << "A=M-D" << '\n';
		asmFile << "D=M" << '\n';
		asmFile << "@" << (5 - i) << '\n';
		asmFile << "M=D" << '\n';
	}
}

returnTranslator::~returnTranslator()
{
}
