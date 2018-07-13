#include "CommandLine.h"

CommandLine::CommandLine() {}

void CommandLine::SetData(char * tab[], int length)
{
	std::string temp = "";
	for (int i = 0; i < length - 1; i++)
	{
		temp = tab[i];
		if (temp.compare("-i") == 0)
		{
			sourcePath = tab[i + 1];
			continue;
		}
		if (temp.compare("-p") == 0)
		{
			iterations = std::stoi(tab[i + 1]);
			if (iterations < 0)
			{
				UserInputException ex;
				throw ex;
			}
			continue;
		}
		if (temp.compare("-o") == 0)
		{
			resultPath = tab[i + 1];
			continue;
		}
	}
}

std::string CommandLine::GetSourcePath()
{
	return sourcePath;
}

std::string CommandLine::GetResultPath()
{
	return resultPath;
}

int CommandLine::GetIterations()
{
	return iterations;
}

CommandLine::~CommandLine()
{
}
