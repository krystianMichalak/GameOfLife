#pragma once
#include <iostream>

#include "FileReadWriteException.h"
#include "EnumTypes.h"

class Cell
{
protected:
	cellState state;	//STAN BIEZACY KOMORKI
	cellState newState;	//NOWY STAN KOMORKI
public:
	Cell();
	
	Cell(char state);	//KONSTRUKTOR PRZYJMUJACY JAKO ARGUMENT STAN '0' - martwa komorka LUB '1' - zywa komorka

	void NewState();	//USTAW NOWY STAN

	virtual std::string GetTypeState();	//ZWROC TYP KOMORKI JAKO CHAR np. 'N', 'H' itp ORAZ STAN JAKO 1 lub 0

	virtual bool IsRestricted();	//SPRAWDZENIE CZY KOMORKA JEST OGRANICZONA

	void SetState(cellState state);	//USTAWIENIE STANU KOMORKI

	cellState GetState();	//POBRANIE BIEZACEGO STANU KOMORKI

	virtual void Evolve(int aliveCells);	//WYZNACZENIE NOWEGO STANU KOMORKI NA PODSTAWIE ILOSCI SASIADUJACYCH ZYWYCH KOMOREK

	~Cell();
};

