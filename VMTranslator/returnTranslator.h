#pragma once
class returnTranslator
{
	std::fstream &asmFile;
	std::string &currentCommand;

public:
	returnTranslator(std::fstream &fileStream, std::string &currentCommand);
	void setEndFrame();
	void setReturnAddr();
	void returnOutputToArg();
	void restorePointers();
	~returnTranslator();
};

