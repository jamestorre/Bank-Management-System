#pragma once
#include "Account.h"
#include <string>
//#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Database
{
private:
	//vector<Account> accounts;
	Account* accounts;
	unsigned int db_size;
	
public:
	Database();
	~Database();

	bool push(Account acc);
	int size();

	bool load(string file_name);
	bool add_new_account(string name);
	bool save_to_file(string file_name);
	bool delete_account(int account_number);
	bool account_exists(int account_number) const;
	int get_position_with_account_number(int account_number) const;
	bool deposit(int account_number, double ammount);
	bool withdraw(int account_number, double ammount);
	bool transfer(int acc_n1, int acc_n2, double ammount);
	void print_all_accounts();
	void print_account(int account_number);

	

};