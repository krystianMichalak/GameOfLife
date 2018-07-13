#include "UserInputException.h"

UserInputException::UserInputException() {}

const char * UserInputException::what() const throw()
{
	return "Bad command line arguments!";
}


UserInputException::~UserInputException() {}
