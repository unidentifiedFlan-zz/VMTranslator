#pragma once
class pushTranslator
{
	std::fstream &asmFile;
	std::string &currentCommand;
	int &arg2;
public:
	pushTranslator(std::fstream &fileStream, std::string &currentFile, std::string &segment, std::string &command, int &arg2);
	void pushConstant();
	void pushLocal();
	void pushArgument();
	void pushThis();
	void pushThat();
	void pushTemp();
	void pushStatic(std::string &currentFile);
	void pushPointer();
	~pushTranslator();
};

