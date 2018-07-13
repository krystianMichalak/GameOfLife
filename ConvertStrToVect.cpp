#include <string>
#include <vector>
using namespace std;

vector<char> ConvertStrToVect(string line)
{
	vector<char> row;

	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'O' && line[i] != 'H' && line[i] != ' ')
		{
			throw new exception("Inwalid Characters in file! Only Allowed: \"0\", \"1\", \"N\", \"O\", \"H\"");
		}

		if (line[i] != ' ')
		{
			row.push_back(line[i]);
		}
	}

	return row;
}