#pragma once
#include "Cell.h"
class HardToReviveCell : public Cell
{
private:
	unsigned int cycles;
	bool isReborning;
public:
	HardToReviveCell();

	HardToReviveCell(char state);

	void Evolve(int aliveCells);

	std::string GetTypeState();

	bool IsRestricted();

	~HardToReviveCell();
};

