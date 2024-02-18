#pragma once

#include <exception>
using namespace std;

class FileSaveException : public exception
{
public:
	virtual const char* what() const
	{
		return "ERROR: Unnable to save file!";
	}
}FileSave;