#pragma once
#include <vector>

class Matrix
{
private:
	std::vector< std::vector<char> > matrix;

public:
	Matrix(std::vector< std::vector<char> > matrix);

	void ConvertMatrix(int cycles);

	~Matrix();
};

