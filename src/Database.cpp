#include "Database.h"

Database::Database()
{
	accounts = NULL;
	db_size = 0;
}

bool Database::load(string file_name)
{
	fstream db_file;
	db_file.open(file_name, ios::in);
	if (!(db_file.is_open()))
	{
		return false; // Unnable to open file!
	}
	string line, element;
	int acc_num_;
	string name_;
	double balance_;
	while (getline(db_file, line))
	{
		stringstream str(line);
		getline(str, element, ',');
		acc_num_ = stoi(element);
		getline(str, element, ',');
		name_ = element;
		getline(str, element, ',');
		balance_ = stod(element);

		Account account_;
		account_.set_account_number(acc_num_);
		account_.set_name(name_);
		account_.set_balance(balance_);
		push(account_);
	}
	db_file.close();
	return true;
}

Database::~Database()
{
	delete[] accounts;
}

bool Database::add_new_account(string name)
{
	// The new acc_num will be the next integer of the last account on the database.
	unsigned int acc_num;
	if (db_size == 0)
	{
		acc_num = 1;
	}
	else
	{
		acc_num = accounts[db_size - 1].get_account_number() + 1;
	}
	Account acc;
	acc.set_account_number(acc_num);
	acc.set_name(name);
	push(acc);
	return true;
}

bool Database::save_to_file(string file_name)
{
	fstream db_file;
	db_file.open(file_name, ios::out);
	if (!(db_file.is_open()))
	{
		return false; // Unnable to open file!
	}
	for (unsigned int i = 0; i < db_size; i++)
	{
		db_file << accounts[i].get_account_number() << ",";
		db_file << accounts[i].get_name() << ",";
		db_file << accounts[i].get_balance() << endl;
	}
	db_file.close();
	return true;
}

bool Database::push(Account acc)
{
	if (db_size == 0)
	{
		accounts = new Account[1];
		accounts[0] = acc;
		db_size++;
		return true;
	}
	else if (db_size > 0)
	{
		Account* accsTemp = new Account[db_size + 1];
		for (unsigned int i = 0; i < db_size; i++)
		{
			accsTemp[i] = accounts[i];
		}
		accsTemp[db_size] = acc;
		delete[] accounts;
		accounts = accsTemp;
		db_size++;
		// TODO stack overflow exception
		return true;
	}
	return false;
}

bool Database::delete_account(int acc_num)
{
	/*for (int i = 0; i < db_size; i++)
	{
		if (accounts[i].get_account_number() == account_number)
		{
			accounts.erase(accounts.begin() + i);
			return true;
		}
	}
	return false;*/

	if (!account_exists(acc_num))
	{
		return false;
	}
	int pos;
	for (unsigned int i = 0; i < db_size; i++)
	{
		if (accounts[i].get_account_number() == acc_num)
		{
			pos = i;
		}
	}
	Account* accsTemp = new Account[db_size - 1];
	for (unsigned int i = 0, j = 0; i < db_size; i++)
	{
		if (accounts[i].get_account_number() != acc_num)
		{
			accsTemp[j] = accounts[i];
			j++;
		}
	}
	delete[] accounts;
	accounts = accsTemp;
	db_size--;
	return true;
}

int Database::size()
{
	return db_size;
}

bool Database::account_exists(int account_number) const
{
	for (unsigned int i = 0; i < db_size; i++)
	{
		if (account_number == accounts[i].get_account_number())
		{
			return true;
		}
	}
	return false;
}

int Database::get_position_with_account_number(int account_number) const
{
	for (unsigned int i = 0; i < db_size; i++)
	{
		if (accounts[i].get_account_number() == account_number)
		{
			return i;
		}
	}
	return -1;
}

bool Database::deposit(int account_number, double ammount)
{
	if (!account_exists(account_number))
	{
		return false;
	}
	int position = get_position_with_account_number(account_number);
	double new_balance = accounts[position].get_balance() + ammount;
	accounts[position].set_balance(new_balance);
	return true;
}

bool Database::withdraw(int account_number, double ammount)
{
	if (!account_exists(account_number))
	{
		return false;
	}
	int position = get_position_with_account_number(account_number);
	double new_balance = accounts[position].get_balance() - ammount;
	if (new_balance < 0)
	{
		return false;
	}
	accounts[position].set_balance(new_balance);
	return true;
}

// acc_n1 is the provider and acc_n2 is the receiver.
bool Database::transfer(int acc_n1, int acc_n2, double ammount)
{
	if (!account_exists(acc_n1) or !account_exists(acc_n2))
	{
		return false;
	}
	int pos1 = get_position_with_account_number(acc_n1);
	int pos2 = get_position_with_account_number(acc_n2);
	double new_balance1 = accounts[pos1].get_balance() - ammount;
	double new_balance2 = accounts[pos2].get_balance() + ammount;
	if (new_balance1 < 0)
	{
		return false;
	}
	accounts[pos1].set_balance(new_balance1);
	accounts[pos2].set_balance(new_balance2);
	return true;
}

void Database::print_all_accounts()
{
	for (unsigned int i = 0; i < db_size; i++)
	{
		accounts[i].print_account_details();
		cout << endl;
	}

}

void Database::print_account(int account_number)
{
	if (!account_exists(account_number))
	{
		cout << "Account "<<account_number<<" does not exist in the Database!"<<endl;
		return;
	}
	int position = get_position_with_account_number(account_number);
	cout << "Account number: " << accounts[position].get_account_number() << endl
		<< "Name: " << accounts[position].get_name() << endl
		<< "Balance: " << accounts[position].get_balance() << endl;
}

