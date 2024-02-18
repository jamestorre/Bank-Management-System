#include "Account.h"

using namespace std;

Account::Account()
{
	account_number = 0;
	name = "";
	balance = 0;
}



void Account::set_account_number(const int an)
{
	account_number = an;
}

void Account::set_balance(const double b)
{
	balance = b;
}


void Account::print_account_details()
{
	cout << "Account number: " << account_number << endl;
	cout << "Name: " << name << endl;
	cout << "Balance: " << balance << endl;
}


