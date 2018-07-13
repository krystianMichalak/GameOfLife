#pragma once
#include <vector>
#include <fstream>
#include <string>

#include "Cell.h"
#include "FileReadWriteException.h"

using namespace std;

class CellGroup
{
private:
	vector< vector<Cell *> > cellGroup;

	void ConvertStrToVect(string line);	//ZMIANA WIERSZA Z CHAR'AMI REPREZENTUJACYMI TYPY KOMOREK NA OBIEKT TYPU WEKTOR
	int GetAliveNeighbor(Cell * current, int i, int j);	//WYZNACZENIE ZYWYCH KOMOREK SASIADUJACYCH
public:
	CellGroup();

	void LoadFromFile(string path);	//ODCZYT DANYCH Z PLIKU TXT DO TABLICY KOMOREK

	void CalculateNewStates();	//WYZNACZENIE NOWYCH STANOW KOMOREK

	void SetNewStates();	//USTAWIENIE NOWYCH STANOW KOMOREK

	void Display();	//WYSWIETL ZAWARTOSC TABLICY KOMOREK

	void SaveToFile(string pathName);	//ZAPIS DANYCH DO PLIKU TXT Z TABLICY KOMOREK

	~CellGroup();
};

