#pragma once
class arithmeticTranslator
{
	std::fstream &asmFile;
	int boolCompNum = 0;
	std::string &currentCommand;
	std::string &arithmeticOp;

public:
	arithmeticTranslator(std::fstream &asmFile, std::string &command, std::string &currentCommand);
	void commonArithmeticStart();
	void add();
	void sub();
	void neg();
	void commonComparatorEnd();
	void equal();
	void greaterThan();
	void lessThan();
	void andOp();
	void orOp();
	void notOp();
	~arithmeticTranslator();
};

