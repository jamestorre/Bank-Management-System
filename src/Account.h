#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Account
{
	unsigned int account_number;
	string name;
	double balance;

public:
	Account();
	

	void set_account_number(const int an);
	void set_name(string n) { name = n; }
	void set_balance(const double b);
	
	int get_account_number() const { return account_number; }
	string get_name() const { return name; }
	double get_balance() const { return balance; }
	
	
	void print_account_details();
};