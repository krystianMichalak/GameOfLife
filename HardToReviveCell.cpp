#include "HardToReviveCell.h"

HardToReviveCell::HardToReviveCell() {}

HardToReviveCell::HardToReviveCell(char state) : Cell(state), cycles(3), isReborning(false) {}

void HardToReviveCell::Evolve(int aliveCells)
{
	if (state == dead && aliveCells == 3)	//JEZELI KOMORKA JEST MARTWA I MA 3 ZYWYCH SASIADOW TO SPRAWDZMY CZY TAK BEDZIE PRZEZ 3 CYKLE
	{
		isReborning = true;
		cycles--;
		if (cycles == 0)
		{
			newState = alive;
			isReborning = false;
			cycles = 3;
			return;
		}
		newState = state;
	}
	else if (state == alive && (aliveCells == 2 || aliveCells == 3))	//JEZELI KOMORKA JEST ZYWA I MA 2 LUB 3 ZYWYCH SASIADOW TO POZOSTAJE ZYWA
	{
		newState = alive;
		isReborning = false;
		cycles = 3;
	}
	else	//JEZELI KOMORKA JEST ZYWA (LUB MARTWA) I MA MNIEJ LUB WIECEJ NIZ 2 LUB 3 ZYWYCH SASIADOW TO UMIERA (POZOSTAJE MARTWA)
	{
		newState = dead;
		isReborning = false;
		cycles = 3;
	}
}

std::string HardToReviveCell::GetTypeState()
{
	std::string chState = "";
	(state == dead) ? chState = "0" : chState = "1";
	return "T " + chState;
}

bool HardToReviveCell::IsRestricted()
{
	return false;
}

HardToReviveCell::~HardToReviveCell() {}
