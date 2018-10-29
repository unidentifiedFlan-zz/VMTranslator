#pragma once
class popTranslator
{
	std::fstream &asmFile;
	int &arg2;
	std::string &currentCommand;

public:
	popTranslator(std::fstream &fileStream, std::string &currFile, std::string &segment, std::string &currCmd, int &argTwo);
	void popConstant();
	void popLocal();
	void popArgument();
	void popThis();
	void popThat();
	void popTemp();
	void popStatic(std::string &currentfile);
	void popPointer();
	~popTranslator();
};

