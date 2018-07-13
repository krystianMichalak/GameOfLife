#include "RestrictedCell.h"

RestrictedCell::RestrictedCell() {}

RestrictedCell::RestrictedCell(char state) :Cell(state) {}

void RestrictedCell::Evolve(int aliveCells)
{
	if (state == dead && aliveCells == 3)	//JEZELI KOMORKA JEST MARTWA I MA 3 ZYWYCH SASIADOW TO ZMIENIA SIE W ZYWA
	{
		newState = alive;
	}
	else if (state == alive && (aliveCells == 2 || aliveCells == 3))	//JEZELI KOMORKA JEST ZYWA I MA 2 LUB 3 ZYWYCH SASIADOW TO POZOSTAJE ZYWA
	{
		newState = alive;
	}
	else	//JEZELI KOMORKA JEST ZYWA I MA MNIEJ LUB WIECEJ NIZ 2 LUB 3 ZYWYCH SASIADOW TO UMIERA
	{
		newState = dead;
	}
}

std::string RestrictedCell::GetTypeState()
{
	std::string chState = "";
	(state == dead) ? chState = "0" : chState = "1";
	return "O " + chState;
}

bool RestrictedCell::IsRestricted()
{
	return true;
}

RestrictedCell::~RestrictedCell() {}
