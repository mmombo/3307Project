/*! @file LoginInterface.h
 * @brief Class that provides an interface to login to the vending machine system
 * @details Class provides an interface for the user to create an account and log into the system
 * @author Justin Woo
 */

#include <iostream>
#include <sstream>
#include "LoginInterface.h"
#include "../Login/Member.h"
#include "../Login/CreditCardCompany.h"

using namespace std;

/**
 * Default constructor to declare a new login interface
 * @return None.
 */
LoginInterface::LoginInterface()
{
}

/**
 * Constructor that sets the login system for the login interface
 * @return None
 */
LoginInterface::LoginInterface(Login *login)
{
    this->login = login;
}

/**
 * Class destructor.
 */
LoginInterface::~LoginInterface() {

}

/**
 * Provides an interface for the user to create an account in the system. Sets the username, password, first name and last name. Checks if password is secure enough. Additionally, prompts the user 
 * if they would like to create an admin account, if yes, then prompts for the login information for an admin account.
 * @param
 * @return void 
 */
void LoginInterface::createAccountPrompt()
{
    int result = -1;
    while (result < 0)
    {
        string username, password, fname, lname;

        cout << "Username: " << endl;
        getline(cin, username);

        cout << "Password (must be longer than 8 characters and contain uppercase, lowercase, a number and a special symbol): " << endl;
        getline(cin, password);

        cout << "First name: " << endl;
        getline(cin, fname);

        cout << "Last name: " << endl;
        getline(cin, lname);

        string input = "";
        while (input != "y" && input != "n")
        {
            cout << "Create an admin account? (Y/N)" << endl;
            getline(cin, input);
            input = tolower(input[0]);

            if (input.length() != 1 || (input != "y" && input != "n"))
            {
                cout << "Invalid input" << endl;
                continue;
            }
        }

        bool admin = false;
        if (input == "y")
        {
            // Prompt for admin login
            Member *result = NULL;
            string username, password;
            bool repeat = true;
            while (repeat)
            {
                cout << "----------Admin Login----------" << endl;
                cout << "Username: " << endl;
                getline(cin, username);

                cout << "Password: " << endl;
                getline(cin, password);

                result = login->checkLogin(username, password);
                if (result == NULL)
                {
                    cout << "Username does not exist or password does not match." << endl;
                }
                else
                {
                    if (result->getisadmin())
                    {
                        admin = true;
                        repeat = false;
                    }
                    else
                    {
                        cout << "This user is not an admin" << endl;
                    }
                }
                if (repeat)
                {
                    string redoInput;
                    int redo;
                    cout << "Input 0 to try again or 1 to exit." << endl;
                    while (getline(cin, redoInput))
                    {
                        stringstream stream(redoInput);
                        if (stream >> redo)
                        {
                            if (stream.eof() && (redo == 0 || redo == 1))
                            {
                                if (redo == 0)
                                {
                                    repeat = true;
                                }
                                else // redo == 1
                                {
                                    repeat = 0;
                                }
                                break;
                            }
                        }
                        cout << "Invalid input" << endl;
                    }
                }
            }
        }

        result = login->createAccount(username, password, fname, lname, admin, "temp");
        if (result == -1)
        {
            cout << "Username already exists." << endl;
        }
        else if (result == -2)
        {
            cout << "Password is not secure enough." << endl;
        }
        else if (result == -3)
        {
            cout << "Empty fields." << endl;
        }
        else if (result == -4)
        {
            cout << "Name contained non-alpha characters." << endl;
        }
        else
        {
            cout << "Account created." << endl;
        }

        if (result < 0)
        {
            string redoInput;
            int redo;
            cout << "Input 0 to try again or 1 to exit." << endl;
            while (getline(cin, redoInput))
            {
                stringstream stream(redoInput);
                if (stream >> redo)
                {
                    if (stream.eof() && (redo == 0 || redo == 1))
                    {
                        if (redo == 0)
                        {
                            result = -1;
                        }
                        else // redo == 1
                        {
                            result = 0;
                        }
                        break;
                    }
                }
                cout << "Invalid input" << endl;
            }
        }
    }
}

/**
 * Provides an interface for the user to login to the system. Takes in the user's username and password and checks the login system to see if they are correct.
 * @param
 * @return A pointer to the member that has been logged into or a NULL pointer if login is cancelled by the user 
 */
Member *LoginInterface::loginPrompt()
{
    bool done = false;
    Member *result = NULL;
    string username, password;
    while (!done)
    {
        cout << "Username: " << endl;
        getline(cin, username);

        cout << "Password: " << endl;
        getline(cin, password);

        result = login->checkLogin(username, password);
        if (result == NULL)
        {
            cout << "Username does not exist or password does not match, please try again." << endl;

            // prompt user if they want to try again
            string redoInput;
            int redo;
            cout << "Input 0 to try again or 1 to exit." << endl;
            while (getline(cin, redoInput))
            {
                stringstream stream(redoInput);
                if (stream >> redo)
                {
                    if (stream.eof() && (redo == 0 || redo == 1))
                    {
                        if (redo == 0)
                        {
                            done = false;
                        }
                        else // redo == 1
                        {
                            done = true;
                        }
                        break;
                    }
                }
                cout << "Invalid input" << endl;
            }
        }
        else
        {
            done = true;
            cout << "Logging in..." << endl;
        }
    }

    // Temp debugging print for member information
    if (result != NULL)
    {
        cout << "Now logged in as" << endl;
        cout << "ID: " << result->getID() << endl;
        cout << "Name: " << result->getName().first << " " << result->getName().second << endl;
        cout << "Currency: " << result->getCurrency() << endl;
    }

    // return the currently logged in member
    return result;
}
