#include "HibernatedCell.h"

HibernatedCell::HibernatedCell() {}

HibernatedCell::HibernatedCell(char state) : Cell(state), isHibernated(false) {}

void HibernatedCell::Hibernate()		//USTAWIENIE STANU HIBERNACJI KOMORKI
{
	isHibernated = true;
	newState = dead;
	cycles = (std::rand() % 10) + 0;	//LOSOWANIE ILOSCI CYKLOW HIBERNACJI
}

void HibernatedCell::Evolve(int aliveCells)
{
	if (isHibernated)	//SPRAWDZENIE CZY KOMORKA JEST ZAHIBERNOWANA
	{
		cycles--;	//JEZELI TAK TO ZMNIEJSZAMY ILOSC CYKLOW HIBERNACJI
		if (cycles == 0 && aliveCells == 2 && aliveCells == 3)	//JEZELI LICZBA CYKLI HIBERNACJI KOMORKI OSIAGNELA 0 TO SPRAWDZAMY CZY MA POZSTAC ZYWA CZY MARTWA
		{
			newState = alive;
			isHibernated = false;
		}
		else if (cycles == 0 && aliveCells != 2 && aliveCells != 3)
		{
			isHibernated = false;
		}
		return;
	}
	if (state == dead && aliveCells == 3)	//JEZELI KOMORKA JEST MARTWA I MA 3 ZYWYCH SASIADOW TO ZMIENIA SIE W ZYWA
	{
		newState = alive;
	}
	else if (state == alive && (aliveCells == 2 || aliveCells == 3))	//JEZELI KOMORKA JEST ZYWA I MA 2 LUB 3 ZYWYCH SASIADOW TO POZOSTAJE ZYWA
	{
		newState = alive;
	}
	else if (state == alive && aliveCells != 2 && aliveCells != 3)	//JEZELI KOMORKA JEST ZYWA I MA MNIEJ LUB WIECEJ NIZ 2 LUB 3 ZYWYCH SASIADOW TO HIBERNUJE
	{
		Hibernate();
	}
	else
	{
		newState = state;
	}
}

bool HibernatedCell::IsRestricted()
{
	return false;
}

std::string HibernatedCell::GetTypeState()
{
	std::string chState = "";
	(state == dead) ? chState = "0" : chState = "1";
	return "H " + chState;
}

HibernatedCell::~HibernatedCell() {}
