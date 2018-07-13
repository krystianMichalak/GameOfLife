#include "NormalCell.h"

NormalCell::NormalCell() {}

NormalCell::NormalCell(int state) : Cell(state) {}

void NormalCell::Evolve(int aliveCells)
{
	if (state == dead && aliveCells == 3)	//JEZELI KOMORKA JEST MARTWA I MA 3 ZYWYCH SASIADOW TO ZMIENIA SIE W ZYWA
	{
		newState = alive;
	}
	else if (state == alive && (aliveCells == 2 || aliveCells == 3))	//JEZELI KOMORKA JEST ZYWA I MA 2 LUB 3 ZYWYCH SASIADOW TO POZOSTAJE ZYWA
	{
		newState = alive;
	}
	else	//JEZELI KOMORKA JEST ZYWA (LUB MARTWA) I MA MNIEJ LUB WIECEJ NIZ 2 LUB 3 ZYWYCH SASIADOW TO UMIERA (POZOSTAJE MARTWA)
	{
		newState = dead;
	}
}

bool NormalCell::IsRestricted()
{
	return false;
}

std::string NormalCell::GetTypeState()
{
	std::string chState = "";
	(state == dead) ? chState = "0" : chState = "1";
	return "N " + chState;
}

NormalCell::~NormalCell() { }
