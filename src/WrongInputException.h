#pragma once

#include <exception>
using namespace std;

class WrongInputException : public exception
{
public:
	virtual const char* what() const
	{
		return "ERROR: Input is invalid!";
	}
}WrongInput;