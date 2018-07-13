#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include "functions.h"

using namespace std;

vector<vector<char>> GetInputData(string pathName)
{
	ifstream file;
	file.open(pathName);

	vector<vector<char>> matrix;
	if (file.is_open())
	{
		string line = "";
		while (file)
		{
			getline(file, line);
			if (line != "endFile")
				matrix.push_back(ConvertStrToVect(line));
			line = "endFile";
		}
		file.close();
	}
	return matrix;
}