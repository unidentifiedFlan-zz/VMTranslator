#include "stdafx.h"
#include "codeWriter.h"
#include "arithmeticTranslator.h"
#include "pushTranslator.h"
#include "popTranslator.h"
#include "functionCallTranslator.h"
#include "returnTranslator.h"


codeWriter::codeWriter(std::string file) {

	std::string typeVM (".vm");

	if (file.find(typeVM) != std::string::npos)
		file.replace(file.find(typeVM), typeVM.length(), ".asm");

	else
		file.append(".asm"); 
	
	asmFile.open(file, std::fstream::out); 
}

void codeWriter::writeInit() {

	asmFile << "@256" << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@SP" << '\n';
	asmFile << "M=D" << '\n';

	writeCall("Sys.init", 0, "System Boot");
}


void codeWriter::writeArithmetic(std::string command, std::string currCmd) {

	arithmeticTranslator ArithmeticTranslator(asmFile, command, currCmd);
}


void codeWriter::writePushPop(std::string commType, std::string segment, int arg2, std::string currentFile, std::string currCmd) {

	if (commType == "C_PUSH") {
		pushTranslator PushTranslator(asmFile, currentFile, segment, currCmd, arg2);
	}

	else if (commType == "C_POP") {
		popTranslator PopTranslator(asmFile, currentFile, segment, currCmd, arg2);
	}
}

void codeWriter::writeLabel(std::string label, std::string FullCommand) {

	asmFile << "(" << currentFunction << "$" << label << ")" << '\t' << "//" << FullCommand << '\n';
	asmFile << "@SP" << '\n';

}

void codeWriter::writeGoto(std::string label, std::string FullCommand) {

	asmFile << "@" << currentFunction << "$" << label << '\t' << "//" << FullCommand << '\n';
	asmFile << "0;JMP" << '\n';
	asmFile << "@SP" << '\n';

}

void codeWriter::writeIf(std::string label, std::string FullCommand) {

	asmFile << "M=M-1" << '\t' << "//" << FullCommand << '\n';
	asmFile << "A=M" << '\n';
	asmFile << "D=M" << '\n';
	asmFile << "@" << currentFunction << "$" << label << '\n';
	asmFile << "D;JNE" << '\n';
	asmFile << "@SP" << '\n';
}

void codeWriter::writeFunction(std::string arg1, int arg2, std::string FullCommand){

	currentFunction = arg1;

	asmFile << "(" <<  arg1 << ")" << '\t' << "//" << FullCommand << '\n';

	for (int i = 0; i < arg2; i++) {
		asmFile << "@" << i << '\n';
		asmFile << "D=A" << '\n';
		asmFile << "@LCL" << '\n';
		asmFile << "A=M+D" << '\n';
		asmFile << "M=0" << '\n';
	}

	asmFile << "@" << arg2 << '\n';
	asmFile << "D=A" << '\n';
	asmFile << "@SP" << '\n';
	asmFile << "M=M+D" << '\n';

}

void codeWriter::writeCall(std::string arg1, int arg2, std::string FullCommand) {

	int callCount = 0;

	//get return label number
	if (funcCallCount.find(arg1) != funcCallCount.end()) {
		callCount = funcCallCount[arg1];
	}
	else {
		funcCallCount.emplace(arg1, 0);
	}

	functionCallTranslator FunctionCallTranslator(asmFile, FullCommand, arg1, arg2, callCount);

	callCount++;
	funcCallCount.at(arg1) = callCount;
}

void codeWriter::writeReturn(std::string FullCommand) {

	returnTranslator ReturnTranslator(asmFile, FullCommand);
}


void codeWriter::close() {

	asmFile.close();
}