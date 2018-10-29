// VMTranslator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VMparser.h"
#include "codeWriter.h"


int main() {

	std::string file;
	std::cout << "Please input a file to assemble:" << std::endl;
	std::cin >> file;

	parser parse(file);
	codeWriter code(file);

	if (file.find(".vm") == std::string::npos)
		code.writeInit();
	
	//LOOP over files to be parsed using vector of files found by Windows, fileList...
	while (parse.moreFiles(file)) {
		while (parse.hasMoreCommands()) {

			std::cout << "Parsing..." << std::endl;
			parse.advance();

			if (parse.commandType() == "C_ARITHMETIC")
				code.writeArithmetic(parse.getCommand(), parse.getFullCommand());
			else if (parse.commandType() == "C_PUSH" || parse.commandType() == "C_POP")
				code.writePushPop(parse.commandType(), parse.arg1(), parse.arg2(), parse.currentFile(), parse.getFullCommand());
			else if (parse.commandType() == "C_LABEL")
				code.writeLabel(parse.arg1(), parse.getFullCommand());
			else if (parse.commandType() == "C_GOTO")
				code.writeGoto(parse.arg1(), parse.getFullCommand());
			else if (parse.commandType() == "C_IF")
				code.writeIf(parse.arg1(), parse.getFullCommand());
			else if (parse.commandType() == "C_FUNCTION")
				code.writeFunction(parse.arg1(), parse.arg2(), parse.getFullCommand());
			else if (parse.commandType() == "C_CALL")
				code.writeCall(parse.arg1(), parse.arg2(), parse.getFullCommand());
			else if (parse.commandType() == "C_RETURN")
				code.writeReturn(parse.getFullCommand());
			else
				std::cout << "Error: invalid command type" << std::endl;
		}
		parse.endStream();
	} 
	code.close();

	return 0;
}



