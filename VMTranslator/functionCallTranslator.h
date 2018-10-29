#pragma once

#include "stdafx.h"

class functionCallTranslator
{
	std::fstream &asmFile;
	std::string &currentCommand;
	std::string &arg1;
	int &arg2;
	int &callCount;

public:
	functionCallTranslator(std::fstream &streamFile, std::string &currCmd, std::string &argOne, int &argTwo, int &callCount);
	void saveReturnAddr();
	void saveVariables();
	void assignNewArg();
	void assignNewLocal();
	void createReturnLabel();
	~functionCallTranslator();
};

