#pragma once
#include <string>

#include "UserInputException.h"
class CommandLine
{
private:
	std::string sourcePath = "";
	std::string resultPath = "";
	int iterations = -1;

public:
	CommandLine();

	void SetData(char * tab[], int length);

	std::string GetSourcePath();
	std::string GetResultPath();
	int GetIterations();

	~CommandLine();
};

