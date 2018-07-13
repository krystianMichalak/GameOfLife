#include "FileReadWriteException.h"

FileReadWriteException::FileReadWriteException(int type) : type(type)
{
	switch (type)
	{
	case 0:
		exeptionType = "Invalid Characters Type in file! Only Allowed : \"0\", \"1\", \"N\", \"O\", \"H\" !";
		break;
	case 1:
		exeptionType = "Invalid Characters Sequence in file!\nAfter: character there should be a space and then \"0\" or \"1\" !";
		break;
	case 2:
		exeptionType = "Could not open the file to read!";
		break;
	case 3:
		exeptionType = "Could not open the file to write!";
		break;
	}
}

const char * FileReadWriteException::what() const throw()
{
	return exeptionType;
}


FileReadWriteException::~FileReadWriteException() {}
