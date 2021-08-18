/*!
 * \file SetupInterface.h
 * \brief Class containing the interface for the first time setup
 * \details Class containing the interface for the first time setup. Prompts for relevant user inputs and then creates an admin account based on the input information.
 * \author Shahryar Iqbal
*/

#include "../Login/Member.h"
#include "SetupInterface.h"
#include <iostream>
#include <sstream>

using namespace std;


/**
* Default constructor to declare a SetupInterface. Does not initialze the login attribute. 
* @return None.
*/
SetupInterface::SetupInterface()
{
}

/**
* constructor to declare a SetupInterface and initialize the login attribute. 
* @param login The Login object that holds all login information
* @return None.
*/
SetupInterface::SetupInterface(Login *login)
{
	this->login = login;
}

/**
* Default destuctor for SetupInterface. Just a null destructor.
* @return None.
*/
SetupInterface::~SetupInterface() {

}

/**
* Method that does all the relevant prompts to complete the setup. User's are prompted for their first name, last name, username, and password. Creates an admin account with the user inputs. Checks for incorrect inputs and prompts the user to redo the setup.
* @return None.
*/
void SetupInterface::SetupPrompt()
{
	int result = -1;
	string firstName, lastName, username, password;
	cout << "WELCOME TO YOUR BRAND NEW VIRTUAL VENDING MACHINE\n"
		 << endl;
	cout << "Please Follow The Upcoming Instructions To Setup Your First Account" << endl;

	// loops until the user has successfully created an account
	while (result < 0)
	{
		cout << "Please Enter Your First Name: " << endl;
		getline(cin, firstName);

		cout << "Please Enter Your Last Name: " << endl;
		getline(cin, lastName);

		cout << "Please Enter A Username: " << endl;
		getline(cin, username);

		cout << "Please Enter A Password (Must be longer than 8 characters and contain an uppercase, lowercase, a number and a special symbol): " << endl;
		getline(cin, password);

		cout << "As the first member, your account will be designated as an admin account" << endl;


		result = login->createAccount(username, password, firstName, lastName, true, "temp");	// creates an account using the given information. See Login.cpp for description of createAccount

		// if the username is already being used
		if (result == -1)
		{
			cout << "Username already exists. Please try again" << endl;
		}

		// if the password does not fullfill all requirements
		else if (result == -2)
		{
			cout << "Password is not secure enough. Please try again" << endl;
		}

		// if there are empty fields
		else if (result == -3)
		{
			cout << "Empty fields." << endl;
		}

		// if the user input non-alpha characters for their name
		else if (result == -4)
		{
			cout << "Name contained non-alpha characters." << endl;
		}

		// if the account was successfully created.
		else
		{
			cout << "Your setup is complete!" << endl;
		}
		cout << endl;
	}
}
