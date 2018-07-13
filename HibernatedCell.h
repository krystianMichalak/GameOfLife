#pragma once
#include "Cell.h"

class HibernatedCell : public Cell
{
private:
	bool isHibernated;
	unsigned int cycles;

	void Hibernate();	//USTAWIENIE STANU HIBERNACJI KOMORKI
public:
	HibernatedCell();

	HibernatedCell(char state);

	void Evolve(int aliveCells);

	bool IsRestricted();

	std::string GetTypeState();

	~HibernatedCell();
};

