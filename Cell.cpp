#include "Cell.h"

Cell::Cell() {}

Cell::Cell(char state)	
{
	if (state != '0' && state != '1')
	{
		FileReadWriteException ex(1);
		throw ex;
	}
	(state == '0') ? this->state = dead : this->state = alive;	//USTAWIENIE STANU KOMORKI NA PODSTAWIE ARGUMENTU, STAN KOMORKI TO ENUM "dead" lub "alive"
}

void Cell::NewState()
{
	state = newState;
}

std::string Cell::GetTypeState() { return 0; }

bool Cell::IsRestricted()
{
	return false;
}

void Cell::SetState(cellState state)
{
	this->state = state;
}

cellState Cell::GetState()
{
	return state;
}

void Cell::Evolve(int aliveCells) {}


Cell::~Cell() {}
