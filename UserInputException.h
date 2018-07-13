#pragma once
#include <exception>

class UserInputException : public std::exception
{
public:
	UserInputException();

	const char* what() const throw();

	~UserInputException();
};

