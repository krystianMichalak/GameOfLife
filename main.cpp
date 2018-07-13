#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#include <string>
#include <ctime>
#include <conio.h>

#include "FileReadWriteException.h"
#include "UserInputException.h"
#include "CellGroup.h"
#include "CommandLine.h"

int main(int argc, char * argv[])
{
	//POBRANIE DANYCH Z LINI POLECEN
	CommandLine * cmd = new CommandLine();
	try
	{
		cmd->SetData(argv, argc);
	}
	catch(UserInputException &e)
	{
		cout << e.what();
		delete cmd;
		_getch();
		return -1;
	}
	//USTAWIENIE PUNKTU STARTOWEGO DLA MECHANIZMU GENEROWANIA LICZB CALKOWITYCH POTRZEBNEGO DLA KOMOREK HIBERNUJACYCH
	srand(time_t(NULL));

	//SCIEZKA DO PLIKOW ODCZYTU I ZAPISU POBRANA Z LINI POLECEN
	std::string fileNameRead = cmd->GetSourcePath();
	std::string fileNameWrite = cmd->GetResultPath();

	//LICZBA ITERACJI Z LINI POLECEN
	const int iterations = cmd->GetIterations();

	//STWORZ TABLICE KOMOREK
	CellGroup * colony = new CellGroup();
	try
	{
		colony->LoadFromFile(fileNameRead);	//POBRANIE DANYCH Z PLIKU
	}
	catch (FileReadWriteException &e)
	{
		cout << e.what();
		delete colony;
		delete cmd;
		_getch();
		return -1;
	}

	//WYSWIETL TABLICE
	colony->Display();

	//EWOLUCJA TABLICY KOMOREK
	for (int i = 0; i < iterations; i++)
	{
		colony->CalculateNewStates();	//WYZNACZ NOWE STANT
		colony->SetNewStates();			//USTAW NOWE STANY
	}
	//WYSWIETL TABLICE
	std::cout << endl;
	colony->Display();
	try
	{
		colony->SaveToFile(fileNameWrite);
	}
	catch (FileReadWriteException &e)
	{
		cout << e.what();
		delete colony;
		delete cmd;
		_getch();
		return -1;
	}
	//USUN TABLICE
	delete colony;
	delete cmd;

	_getch();
	return 0;
	_CrtDumpMemoryLeaks();
}