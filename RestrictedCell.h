#pragma once
#include "Cell.h"
class RestrictedCell : public Cell
{
public:
	RestrictedCell();

	RestrictedCell(char state);

	void Evolve(int aliveCells);

	std::string GetTypeState();

	bool IsRestricted();

	~RestrictedCell();
};

