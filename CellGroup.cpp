#include "CellGroup.h"
#include "NormalCell.h"
#include "HibernatedCell.h"
#include "RestrictedCell.h"
#include "HardToReviveCell.h"

CellGroup::CellGroup() {}

//ZMIANA WIERSZA Z CHAR'AMI REPREZENTUJACYMI TYPY KOMOREK NA OBIEKT TYPU WEKTOR ZAWIERAJACY OBIEKTY POCHODNE KLASY "CELL"
void CellGroup::ConvertStrToVect(string line)
{
	vector<Cell *> row;
	if (line.length() == 0)
		return;
	for (unsigned int i = 0; i < line.length(); i++)
	{	//SPRAWDZENIE POPRAWNOSCI DANYCH ZNAJDUJACYCH SIE W PLIKU
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'O' && line[i] != 'H' && line[i] != 'T' && line[i] != ' ')
		{
			FileReadWriteException ex(0);
			throw ex;
		}
		switch (line[i])
		{
		case 'N':	//KOMORKI "NORMALNE"
			row.push_back(new NormalCell(line[i + 2]));	//line[i + 2] PRZYJMUJE WARTOSCI '0' - kom. martwa LUB '1' - kom. zywa
			break;
		case 'H':	//KOMORKI "HIBERNUJACE"
			row.push_back(new HibernatedCell(line[i + 2]));	//line[i + 2] PRZYJMUJE WARTOSCI '0' - kom. martwa LUB '1' - kom. zywa
			break;
		case 'O':	//KOMORKI "OGRANICZONE"
			row.push_back(new  RestrictedCell(line[i + 2])); //line[i + 2] PRZYJMUJE WARTOSCI '0' - kom. martwa LUB '1' - kom. zywa
			break;
		case 'T':	//KOMORKI "TRUDNOODRADZALNE"
			row.push_back(new HardToReviveCell(line[i + 2])); //line[i + 2] PRZYJMUJE WARTOSCI '0' - kom. martwa LUB '1' - kom. zywa
			break;
		}
	}
	this->cellGroup.push_back(row);
}

//WYZNACZENIE ZYWYCH KOMOREK SASIADUJACYCH
int CellGroup::GetAliveNeighbor(Cell * current, int i, int j)
{
	int aliveCells = 0;

	for (int k = i - 1; k <= i + 1; k++)
	{
		for (int l = j - 1; l <= j + 1; l++)
		{
			if ((k == i && l == j) || l < 0 || k < 0 || k >= (int)cellGroup.size() || l >= (int)cellGroup[k].size())	//SPRAWDZENIE NIE POZWALAJACE WYJSC POZA ZAKRES TABLICY
				continue;
			if (current->IsRestricted() == true)	//DLA KOMOREK OGRANICZONYCH SPRAWDZAMY TYLKO CONAJWYZEJ 4 KOMORKI O TAKIM SAMYM INDEKSIE i lub j
			{
				if((k == i || l == j) && cellGroup[k][l]->GetState() == alive)
					aliveCells++;
			}
			else if (cellGroup[k][l]->GetState() == alive)
				aliveCells++;
		}
	}
	return aliveCells;
}

//ODCZYT DANYCH Z PLIKU TXT DO TABLICY KOMOREK
void CellGroup::LoadFromFile(string pathName)
{
	ifstream file;
	file.open(pathName);
	if (file.is_open())
	{
		string line = "";
		while (file)
		{
			getline(file, line);	//	ODCZYT WIERSZAMI
			if (line != "endFile")
				ConvertStrToVect(line);	//	PRZEKONWERTOWANIE WIERSZA BEDACEGO STRINGIEM NA OBIEKT TYPU VEKTOR
			line = "endFile";
		}
		file.close();
	}
	else
	{
		FileReadWriteException ex(2);
		throw ex;
	}
}

//ZAPIS DANYCH DO PLIKU TXT Z TABLICY KOMOREK
void CellGroup::SaveToFile(string pathName)
{
	ofstream file;
	file.open(pathName);
	if (file.is_open())
	{
		for (vector< vector<Cell *> > ::iterator it1 = cellGroup.begin(); it1 != cellGroup.end(); it1++)
		{
			for (vector<Cell *> ::iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
			{
				file << (*it2)->GetTypeState();
				file << " ";
			}
			file << '\n';
		}
		file.close();
	}
	else
	{
		FileReadWriteException ex(3);
		throw ex;
	}
}

//WYZNACZENIE NOWYCH STANOW KOMOREK
void CellGroup::CalculateNewStates()
{
	int i = 0;
	for (vector< vector<Cell *> > ::iterator it1 = cellGroup.begin(); it1 != cellGroup.end(); it1++)
	{
		int j = 0;
		for (vector<Cell *> ::iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
		{
			int numberOfAliveCells = GetAliveNeighbor(*it2, i, j);	//WYZNACZENIE ILOSCI ZYWYCH KOMOREK SASIEDNICH
			(*it2)->Evolve(numberOfAliveCells);	//WYZNACZENIE NOWEGO STANU KOMORKI NA PODSTAWIE ILOSCI ZYWYCH KOMOREK SASIADUJACYCH
			j++;
		}
		i++;
	}
}

//USTAWIENIE NOWYCH STANOW KOMOREK
void CellGroup::SetNewStates()
{
	for (vector< vector<Cell *> > ::iterator it1 = cellGroup.begin(); it1 != cellGroup.end(); it1++)
	{
		for (vector<Cell *> ::iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
		{
			(*it2)->NewState();	//USTAWIENIE NOWYCH STANOW DLA KOMOREK
		}
	}
}

//WYSWIETL ZAWARTOSC TABLICY KOMOREK
void CellGroup::Display()
{
	for (vector< vector<Cell *> > ::iterator it1 = cellGroup.begin(); it1 != cellGroup.end(); it1++)
	{
		for (vector<Cell *> ::iterator it2 = (*it1).begin(); it2 != (*it1).end();  it2++)
		{				
			cout << (*it2)->GetTypeState() << " ";
		}
		cout << endl;
	}
}

//ZWOLNIENIE PAMIECI
CellGroup::~CellGroup()
{
	for (vector< vector<Cell *> > ::iterator it1 = cellGroup.begin(); it1 != cellGroup.end(); it1++)
	{
		for (vector<Cell *> ::iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
		{
			delete (*it2);
		}
	}
}
