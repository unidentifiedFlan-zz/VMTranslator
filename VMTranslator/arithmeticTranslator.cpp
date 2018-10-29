#include "stdafx.h"
#include "arithmeticTranslator.h"


arithmeticTranslator::arithmeticTranslator(std::fstream &streamFile, std::string &op, std::string &currCmd) : asmFile(streamFile), 
																	arithmeticOp(op), currentCommand(currCmd) {

	if (arithmeticOp == "add") {
		add();
	}
	else if (arithmeticOp == "sub") {
		sub();
	}
	else if (arithmeticOp == "neg") {
		neg();
	}
	else if (arithmeticOp == "eq") {
		equal();
	}
	else if (arithmeticOp == "gt") {
		greaterThan();
	}
	else if (arithmeticOp == "lt") {
		lessThan();
	}
	else if (arithmeticOp == "and") {
		andOp();
	}
	else if (arithmeticOp == "or") {
		orOp();
	}
	else if (arithmeticOp == "not") {
		notOp();
	}

	asmFile << "@SP" << '\n';
}

void arithmeticTranslator::commonArithmeticStart() {
	asmFile << "@SP" << '\t' << "//" << currentCommand << '\n';
	asmFile << "M=M-1" << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "D=M" << '\n';
	asmFile << "A=A-1" << '\n';
}

void arithmeticTranslator::add() {
	commonArithmeticStart();
	asmFile << "M=M+D" << '\n';
}

void arithmeticTranslator::sub() {
	commonArithmeticStart();
	asmFile << "M=M-D" << '\n';
}

void arithmeticTranslator::neg() {
	asmFile << "@SP" << '\t' << "//" << currentCommand << '\n';
	asmFile << "A=M-1" << '\n';
	asmFile << "M=-M" << '\n';
}

void arithmeticTranslator::commonComparatorEnd() {
	asmFile << "@SP" << '\n';
	asmFile << "A=M-1" << '\n';
	asmFile << "M=0" << '\n';
	asmFile << "(boolComp" << boolCompNum << ")" << '\n';
	boolCompNum++;
}

void arithmeticTranslator::equal() {

	commonArithmeticStart();
	asmFile << "D=M-D" << '\n';
	asmFile << "M=-1" << '\n';
	asmFile << "@boolComp" << boolCompNum << '\n';
	asmFile << "D;JEQ" << '\n';
	commonComparatorEnd();
}

void arithmeticTranslator::greaterThan() {

	commonArithmeticStart();
	asmFile << "D=M-D" << '\n';
	asmFile << "M=-1" << '\n';
	asmFile << "@boolComp" << boolCompNum << '\n';
	asmFile << "D;JGT" << '\n';
	commonComparatorEnd();
}

void arithmeticTranslator::lessThan() {

	commonArithmeticStart();
	asmFile << "D=M-D" << '\n';
	asmFile << "M=-1" << '\n';
	asmFile << "@boolComp" << boolCompNum << '\n';
	asmFile << "D;JLT" << '\n';
	commonComparatorEnd();
}

void arithmeticTranslator::andOp() {
	commonArithmeticStart();
	asmFile << "M=M&D" << '\n';
}
void arithmeticTranslator::orOp() {
	commonArithmeticStart();
	asmFile << "M=M|D" << '\n';
}

void arithmeticTranslator::notOp() {
	asmFile << "@SP" << '\t' << "//" << currentCommand << '\n';
	asmFile << "A=M-1" << '\n';
	asmFile << "M=!M" << '\n';
}

arithmeticTranslator::~arithmeticTranslator()
{
}
