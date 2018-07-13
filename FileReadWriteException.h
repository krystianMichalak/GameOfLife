#pragma once
#include <exception>

class FileReadWriteException : public std::exception
{
private:
	int type;
	char * exeptionType;
public:
	FileReadWriteException(int type);

	const char* what() const throw();

	~FileReadWriteException();
};

