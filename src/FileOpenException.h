#pragma once

#include <exception>
using namespace std;

class FileOpenException : public exception
{
public:
	virtual const char* what() const
	{
		return "ERROR: Unnable to open file!";
	}
}FileOpen;