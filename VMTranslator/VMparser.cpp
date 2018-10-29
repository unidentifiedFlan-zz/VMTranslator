#include "stdafx.h"
#include "VMparser.h"


parser::parser(std::string file) {

	if (file.find(".vm") == std::string::npos) {
		
		std::string inputFolderPath = file.append("\\");
		getFilesList(inputFolderPath, "*.vm*", fileList);

		//fileList.insert(fileList.begin(), "sys.vm");
	}

	else 
		fileList.push_back(file);

	fileIterator = fileList.begin();

}


bool parser::moreFiles(std::string file) {

	if (fileIterator != fileList.end()) {

		std::string newAsm = file;

		if (file.find(".vm") == std::string::npos)
			newAsm = file + "\\" + fileList[fileIterator - fileList.begin()];

		fileStream.open(newAsm, std::fstream::in);

		fileIterator++;

		return 1;
	}


	return 0;

}

std::string parser::currentFile() {
	
	std::string file = fileList[fileIterator - 1 - fileList.begin()];

	// Remove ".vm" from file name
	file.erase (file.end()-3, file.end());

	return file;
}

bool parser::hasMoreCommands() {

	fileStream >> std::ws;

	while (fileStream.peek() == '/' || fileStream.peek() == '\n') {

		fileStream.ignore(256, '\n');
		fileStream >> std::ws;

	}

	if (fileStream.eof())
		return false;

	return true;
}


void parser::advance() {

	currentCommand[0] = '\0';

	std::getline(fileStream, currentCommand);

	for (unsigned int i = 0; i < currentCommand.size(); i++) {

		if (currentCommand[i] == '\n' || currentCommand[i] == '//')
			currentCommand[i] = '\0';
	}

	std::cout << currentCommand << std::endl;
}

std::string parser::commandType() {

	//C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL
	
	command.clear();
	
	int i = 0;

	for (std::string::iterator it = currentCommand.begin(); it != currentCommand.end() &&
		currentCommand[i] != '\n' && currentCommand[i] != ' '; it++) {
		
		command.push_back(currentCommand[i]);
		i++;
	}
	
	if (command == "add" || command == "sub" || command == "neg" || command == "eq" ||
		command == "gt" || command == "lt" || command == "and" || command == "or" || command == "not")
		commType = "C_ARITHMETIC";


	else if (command == "push")
		commType = "C_PUSH";

	else if (command == "pop")
		commType = "C_POP";

	else if (command == "label")
		commType = "C_LABEL";

	else if (command == "goto")
		commType = "C_GOTO";

	else if (command == "if-goto")
		commType = "C_IF";

	else if (command == "function")
		commType = "C_FUNCTION";

	else if (command == "return")
		commType = "C_RETURN";

	else if (command == "call")
		commType = "C_CALL";

	else
		std::cout << "Invalid command type." << std::endl;

	return commType;
}



std::string parser::getCommand() {

	return command;
}


std::string parser::arg1() {

	std::string arg1;
	int i = 0;

	while (currentCommand[i] != ' ') {
		i++;
	}

	i++;

	if (commType == "C_ARITHMETIC")
		i = 0;
	
	while (currentCommand[i] != '\n' && currentCommand[i] != ' ' && currentCommand[i] != '\0') {

		arg1.push_back(currentCommand[i]);
		i++;

	}

	return arg1;
}

int parser::arg2() {

	std::string arg2;
	int i = 0;

	for (int j = 0; j < 2; j++) {

		while (currentCommand[i] != ' ') 
			i++;
		i++;
	}

	while (currentCommand[i] != '\0' && currentCommand[i] != '\n' && currentCommand[i] != '/') {
		arg2.push_back(currentCommand[i]);
		i++;
	}
	
	int arg;
	try_stoi(arg, arg2);

	return arg;
}

std::string parser::getFullCommand() {

	return currentCommand;
}

void parser::endStream() {

	fileStream.close();
}


//Returns string as integer
bool try_stoi(int & i, const std::string & s) {
	try {
		size_t pos;
		i = stoi(s, &pos);
		return pos == s.size();
	}
	catch (const std::invalid_argument&) {
		return false;
	}
}


void getFilesList(std::string filePath, std::string extension, std::vector<std::string> & returnFileName)
{
	WIN32_FIND_DATA fileInfo;
	HANDLE hFind;
	std::string  fullPath = filePath + extension;
	hFind = FindFirstFile(fullPath.c_str(), &fileInfo);
	if (hFind != INVALID_HANDLE_VALUE) {
		returnFileName.push_back(fileInfo.cFileName);
		while (FindNextFile(hFind, &fileInfo) != 0) {
			returnFileName.push_back(fileInfo.cFileName);
		}
	}
}