#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Account.h"
#include "Database.h"
#include "WrongInputException.h"
#include "FileSaveException.h"

using namespace std;

// Returns true if string s contain characters A-Z a-z and spaces only
bool verify_client_name(string s)
{
	int space_counter = 0;
	// If string contain spaces only
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == 32) space_counter++;
	}
	if (space_counter == s.size()) return false;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] < 32 || (s[i] > 32 && s[i] < 65) ||
			(s[i] > 90 && s[i] < 97) || s[i]>122) return false;
	}
	return true;
}

void menu_reg_new_acc(Database& db)
{
	string name;
	char choice;
	cout << "---REGISTER NEW ACCOUNT---" << endl;
	cout << "Provide the person name: ";
	cin >> name; // Must contain characters A-Z, a-z or spaces.
	try
	{
		if (!verify_client_name(name)) throw WrongInput;
	}
	catch (exception& e)
	{
		cerr << e.what() << endl << endl;
		cerr << "Name must not contain numbers or special characters!" << endl<<endl;
		system("pause");
		return;
	}
	cout << endl << endl;
	cout << "--- CONFIRMATION ---" << endl;
	cout << "An account will be created with the following client name: " << name << endl;
	cout << "Enter 'y' to confirm operation, any other key to cancel: "<<endl;
	cin >> choice;
	if (choice != 'y')
	{
		cout << endl << "Operation canceled!" << endl;
		system("pause");
		return;
	}
	if (!db.add_new_account(name))
	{
		cout << "Error adding account into database!" << endl;
		system("pause");
		return;
	}
	cout << "Account created succesfully!"<<endl;
	system("pause");
	return;
}

// Returns true if string ends with ".csv"
bool verify_db_file_name(string s)
{
	string aux = ".csv";
	for (int i = s.size() - 4, j = 0; i < s.size(); i++, j++)
	{
		if (s[i] != aux[j])
		{
			return false;
		}
	}
	return true;
}

void menu_save(Database& db, string& current_file_name)
{
	char choice;
	cout << "---SAVE DATABASE TO FILE---" << endl;
	cout << "Save current Database to "<<current_file_name<< " ?" << endl
		<< "Enter 'y' to confirm, any other key to save to other file: ";
	cin >> choice;
	if (choice == 'y')
	{
		db.save_to_file(current_file_name);
		cout << endl << "File saved at " << current_file_name << " !" << endl;
		system("pause");
		return;
	}
	cout << "Please enter the file name with .csv extension: ";
	string file_name;
	cin >> file_name;
	if (!verify_db_file_name(file_name))
	{
		cout << endl << "File name must end with .csv extension! ";
		system("pause");
		return;
	}
	try
	{
		if (!db.save_to_file(file_name)) throw FileSave;
	}
	catch (exception& e)
	{
		cerr << e.what() << endl << endl;
		system("pause");
		return;
	}
	current_file_name = file_name;
	cout << "Database saved sucessfully to " << file_name << " !" << endl;
	system("pause");
	return;
}

void menu_print_all(Database& db)
{
	cout << "---DISPLAY ALL ACCOUNTS IN DATABASE---" << endl;
	db.print_all_accounts();
	system("pause");
	return;
}

void menu_del_acc(Database& db)
{
	cout << "---DELETE ACCOUNT---" << endl;
	int acc_num;
	cout << "Please provide the account number to be deleted: ";
	cin >> acc_num;
	if (!db.account_exists(acc_num))
	{
		cout<< endl<<"Error! Account not found!"<<endl;
		system("pause");
		return;
	}
	cout << endl << "The following account will be deleted: " << endl;
	db.print_account(acc_num);
	cout << endl<< "Enter 'y' to confirm, any other key to cancel: ";
	char choice;
	cin >> choice;
	if (choice != 'y')
	{
		cout << endl<<"Operation canceled!"<<endl;
		system("pause");
		return;
	}
	db.delete_account(acc_num);
	cout << endl << "Account number " << acc_num << "successfully deleted!"<<endl;
	system("pause");
	return;
}

void menu_show_acc_data(Database& db)
{
	cout << "---DISPLAY ACCOUNT DETAILS---" << endl;
	cout << "Please enter the account number to be shown: ";
	int acc_num;
	cin >> acc_num;
	db.print_account(acc_num);
	system("pause");
	return;
}

void menu_perform_deposit(Database& db)
{
	int acc_num;
	double amount;
	char choice;
	cout << "---DEPOSIT---" << endl;
	cout << "Please enter the account number to be deposited: ";
	cin >> acc_num;
	if (!db.account_exists(acc_num))
	{
		cout << endl << "Error! Account not found in Database!" << endl;
		system("pause");
		return;
	}
	db.print_account(acc_num);
	cout << endl << "Please enter the amount to be deposited: ";
	cin >> amount;
	cout << endl << "A deposit of " <<amount<< " will be performed on the following account : " <<endl<< endl;
	db.print_account(acc_num);
	cout << endl << "Enter 'y' to confirm operation. Enter any other key to cancel the operation: ";
	cin >> choice;
	if (choice == 'y')
	{
		db.deposit(acc_num, amount);
		cout << endl << "Deposit successful!" << endl << endl << "New account details: " << endl;
		db.print_account(acc_num); system("pause");
		return;
	}
	cout << endl << "Deposit canceled!"<<endl;
	system("pause");
	return;
}

void menu_perform_withdraw(Database& db)
{
	int acc_num;
	double amount;
	char choice;
	cout << "---WITHDRAW---" << endl;
	cout << "Please enter the account number to withdraw: ";
	cin >> acc_num;
	db.print_account(acc_num);
	cout << endl << "Please enter the amount to be withdraw: ";
	cin >> amount;
	cout << endl << "A withdraw of " << amount << " will be performed on the following account: " << endl << endl;
	db.print_account(acc_num);
	cout << endl << "Enter 'y' to confirm operation. Enter any other key to cancel the operation: ";
	cin >> choice;
	if (choice == 'y')
	{
		if (!db.withdraw(acc_num, amount))
		{
			cout <<endl<< "Balance not enough for withdraw!" << endl;
			system("pause");
			return;
		}
		cout << endl << "Withdraw successful!"<<endl<<endl<<"New account details: "<<endl;
		db.print_account(acc_num);
		system("pause");
		return;
	}
	cout << endl << "Deposit canceled!" << endl;
	system("pause");
	return;
}

void menu_perform_transfer(Database& db)
{
	int a1, a2;
	double amount;
	cout << "---TRANSFER---" << endl;
	cout << "Enter the provider account number: ";
	cin >> a1;
	db.print_account(a1);
	cout << endl << "Enter the destiny account number: ";
	cin >> a2;
	db.print_account(a2);
	cout << endl << "Enter the amount to be transfered: ";
	cin >> amount;
	cout << endl;
	cout <<endl<< "Transfering " << amount << " from account " << a1 << " to account " << a2 <<"."<< endl << endl;
	cout << "Enter 'y' to confirm, any other key to cancel: ";
	char choice;
	cin >> choice;
	if (choice == 'y')
	{
		if (db.transfer(a1, a2, amount))
		{
			cout << "Operation successfull! New account state: " << endl<<endl;
			db.print_account(a1);
			db.print_account(a2);
			system("pause");
			return;
		}
		else
		{
			cout << "Error in operation! Insuficient funds from the provider account! " << endl<<endl;
			system("pause");
			return;
		}
	}
	cout << "Operation canceled!" << endl;
	system("pause");
	return;
}

void menu_load(Database& db, string& current_file_name)
{
	cout << "---LOAD DATABASE FROM FILE---" << endl;
	cout << "Enter the file name: ";
	string file_name;
	cin >> file_name;
	cout << endl << endl << "Load database from " << file_name << " ?";
	cout << endl << "Enter 'y' to confirm, any other key to cancel: ";
	char choice;
	cin >> choice;
	if (choice == 'y')
	{
		if (db.load(file_name))
		{
			cout << endl << "File " << file_name << " succesfuly loaded! " << endl;
			current_file_name = file_name;
			system("pause");
			return;
		}
		else
		{
			cout << endl << "Error loading file!" << endl;
			system("pause");
			return;
		}
	}
}

int main()
{
	// Main Menu
	string loaded_db_file = "Database.csv";
	Database db;
	db.load(loaded_db_file);

	while (true)
	{
		system("CLS");
		cout << "--- BANK MANAGMENT SYSTEM ---" << endl << "Author: James Machado De La Torre" << endl
			<< "Neptun code: CZQAEM" << endl<<endl<<endl;
		cout << "Current Loaded Database: " << loaded_db_file << endl << endl;

		cout << endl << "--- MAIN MENU ---" << endl;
		cout << "(1) Register a new account...\n"
			<< "(2) Delete account...\n"
			<< "(3) Show account data...\n"
			<< "(4) Perform deposit...\n";
		cout << "(5) Perform withdrawal...\n"
			<< "(6) Perform transfer...\n"
			<< "(7) Print all database contents...\n"
			<< "(8) Save the current Database to file...\n"
			<< "(9) Load Database from file...\n"
			<< endl
			<< "(0) Exit...\n\n";
		cout << "Please enter an option: ";

		char option;
		cin >> option;

		switch (option)
		{
		case '1':
			system("CLS");
			menu_reg_new_acc(db);
			break;

		case '2':
			system("CLS");
			menu_del_acc(db);
			break;

		case '3':
			system("CLS");
			menu_show_acc_data(db);
			break;

		case '4':
			system("CLS");
			menu_perform_deposit(db);
			break;

		case '5':
			system("CLS");
			menu_perform_withdraw(db);
			break;

		case '6':
			system("CLS");
			menu_perform_transfer(db);
			break;

		case '7':
			system("CLS");
			menu_print_all(db);
			break;

		case '8':
			system("CLS");
			menu_save(db, loaded_db_file);
			break;

		case '9':
			system("CLS");
			menu_load(db, loaded_db_file);
			break;

		case '0':
			system("CLS");
			return 0;

		default:
			cout << "Invalid option!" << endl;
			system("pause");
		}
	}
	
	
	return 0;
}