#pragma once

#include "stdafx.h"

class parser {

	std::fstream fileStream;
	std::string currentCommand;
	std::string commType;
	std::string command;
	std::vector<std::string> fileList;
	std::vector<std::string>::iterator fileIterator;

public:
	parser(std::string file);
	bool moreFiles(std::string file);
	std::string currentFile();
	bool hasMoreCommands();
	void advance();
	std::string commandType();
	std::string arg1();
	int arg2();
	void endStream();
	std::string getCommand();
	std::string getFullCommand();
};


bool try_stoi(int & i, const std::string & s);

void getFilesList(std::string filePath, std::string extension, std::vector<std::string> & returnFileName);