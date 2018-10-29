#pragma once
#include "stdafx.h"

class codeWriter {

	std::fstream asmFile;
	std::string currentFunction;
	std::map<std::string, int> funcCallCount;

public:
	codeWriter(std::string file);
	void writeInit();

	void writeArithmetic(std::string command, std::string currCmd);
	void writePushPop(std::string commType, std::string arg1, int arg2, std::string currentFile, std::string currCmd);
	void writeLabel(std::string label, std::string FullCommand);
	void writeGoto(std::string label, std::string FullCommand);
	void writeIf(std::string label, std::string FullCommand);
	void writeFunction(std::string arg1, int arg2, std::string FullCommand);
	void writeCall(std::string arg1, int arg2, std::string FullCommand);
	void writeReturn(std::string FullCommand);
	void close();
};
