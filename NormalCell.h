#pragma once
#include "Cell.h"

class NormalCell : public Cell
{
public:
	NormalCell();

	NormalCell(int state);

	void Evolve(int aliveCells);

	bool IsRestricted();
	
	std::string GetTypeState();

	~NormalCell();
};

