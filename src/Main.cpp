/// Driver code and menu functionality.
/** Driver class that provides the interface for the main menu, login, shopping car and account creation.
 *  Also provides access to admin menu functionality.
 * \authors Alexander Broekhuyse , Shahryar Iqbal , Matthew Mombourquette , Michael Schmittat , Justin Woo 
*/

#include <iostream>
#include <sstream>
#include "Interfaces/AccountInterface.h"
#include "Interfaces/LoginInterface.h"
#include "Login/UserDBConversion.h"
#include "Interfaces/SetupInterface.h"
#include "Interfaces/VendingInterface.h"
#include "ShoppingCart/Order.h"
#include "ShoppingCart/ShoppingCart.h"
#include "Interfaces/AdminInterface.h"
#include "PurchaseHistory/PurchaseHistoryCollection.h"
#include <climits>

// temp
#include "Product/DiscountCollection.h"

using namespace std;



enum Menu
{
	mainMenu, /*!< Initial menu interface. */ 
	loginMenu, /*!< Login interface. */ 
	accountMenu, /*!< Account menu interface. */ 
	productMenu, /*!< Product display interface. */ 
	cartMenu, /*!< Shopping cart interface. */ 
	setupMenu, /*!< Initial menu interface. */ 
	adminMenu /*!< Interface for admin users. */ 
};

/*!< Driver function for switching between menus inside the application. */
int main()
{
	LoginCollection collection;		// collection containing login information
	UserDBConversion converter;		// encrpyts saves the member information into the csv database.
	Menu menu;						// enum variable that holds the current menu being used

	//load collections from file
	auto map = converter.FileToLoginCollection();
	collection.setCollection(map, converter.getHighestID());
	ProductCollection Products;
	Products = ProductCollection();

	DiscountCollection discounts = DiscountCollection(&Products);

	//initalize classes
	Login login(collection);
	LoginInterface loginInterface(&login);
	SetupInterface SetupInterface(&login);
	AdminInterface adminInterface(Products, discounts);
	Member *currentUser;
	AccountInterface accInterface;
	ShoppingCart cart;
	PurchaseHistoryCollection history = PurchaseHistoryCollection();

	int input = 0;
	int amount, index;
	Menu baseMenu;

	// if the login collection is empty run a first time setup for the first admin account
	if (collection.getMap().size() == 0)
	{
		menu = setupMenu;
	}

	// otherwise go straight to the login meny
	else
	{
		menu = loginMenu;
	}

	// forever loop that keeps going until the user exits 
	while (true)
	{
		// if in the setup menu, then call the prompts from SetupInterface. After the setup is complete, changes menu to loginMenu
		while (menu == setupMenu)
		{
			SetupInterface.SetupPrompt();
			menu = loginMenu;
			break;
		}

		// if in the login menu, then prompts for user action. Can do login, createAccount, or exit
		while (menu == loginMenu)
		{

			string inputStr;
			cout << endl
				 << "----------------- Main Menu -----------------" << endl;
			cout << "1. Login" << endl;
			cout << "2. CreateAccount" << endl;
			cout << "3. Exit" << endl;
			while (getline(cin, inputStr))
			{
				stringstream stream(inputStr);
				if (stream >> input)
				{
					if (stream.eof())
					{
						break;
					}
				}
				cout << "Invalid input" << endl;
			}

			// if user inputs for Login, then display the login menu and call the relevant prompts from loginInterface
			if (input == 1)
			{

				cout << "----------------- Login -----------------" << endl;
				currentUser = NULL;
				currentUser = loginInterface.loginPrompt();
				if (currentUser != NULL)
				{
					// add other setters here for the current user in the system
					// OR could change login interface to a singleton and have a static member for the current user----------------------
					accInterface.setCurrentMember(currentUser);
					string adminCheck = "";
					// if the user is an admin, then prompted to view the vending machine as an admin.
					if (currentUser->getisadmin())
					{
						while (adminCheck != "y" && adminCheck != "n")
						{
							cout << "Login as an admin? (Y/N)" << endl;
							getline(cin, adminCheck);
							adminCheck = tolower(adminCheck[0]);

							if (adminCheck.length() != 1 || (adminCheck != "y" && adminCheck != "n"))
							{
								cout << "Invalid input" << endl;
								continue;
							}
						}
					}
					// if user is not an admin, then they are sent to the main menu
					else
					{
						menu = baseMenu = mainMenu;
						break;
					}

					if (adminCheck == "y")
					{
						Products.alertInterface();
						menu = baseMenu = adminMenu;
						break;
					}
					else
					{
						menu = baseMenu = mainMenu;
						break;
					}
				}
			}
			// if the user inputs to create an account, then go to the account creation menu and call relevant prompts from loginInterface.
			else if (input == 2)
			{
				std::cin.clear();
				cout << "----------------- Account Creation -----------------" << endl;
				loginInterface.createAccountPrompt();
			}

			// if the user inputs to exit, then save all relevant data to the databases and terminate the program. 
			else if (input == 3)
			{
				auto test = login.getLoginCollection().getMap();
				converter.LoginCollectionToFile(test);
				Products.saveToDatabase();
				discounts.saveToDatabase();
				return 0;
			}
		}

		// the product menu. Displays relevant prompts from VendingInterface.
		while (menu == productMenu)
		{

			while (true)
			{
				VendingInterface SaleInterface(Products);
				pair<int, int> result = SaleInterface.VendingDisplay();

				amount = result.second;
				index = result.first;

				if (index != -1)
				{

					Product Product = *Products.getProduct(index);
					Order newOrder(Product, 0, amount);
					cart.addOrder(newOrder);

					cout << cart.printCart() << endl;
				}
				else
				{
					break;
				}
			}

			menu = baseMenu;
		}

		// The main menu. This is the first menu shown after logging in. Prompts user for action, either to view the product catalogue and purchase products, go to checkout, go to account menu, or logout.
		while (menu == mainMenu)
		{

			string inputStr;
			int input;
			cout << endl
				 << "--------------------- Main Menu ---------------------" << endl;
			cout << "1. Product Catalogue" << endl;
			cout << "2. Shopping Cart and Checkout" << endl;
			cout << "3. Account Menu" << endl;
			cout << "4. Logout" << endl;

			while (getline(cin, inputStr))
			{
				stringstream stream(inputStr);
				if (stream >> input)
				{
					if (stream.eof())
					{
						break;
					}
				}
				cout << "Invalid input" << endl;
			}

			// checks user input and sets the menu accordingly
			if (input == 1)
			{
				menu = productMenu;
				break;
			}
			else if (input == 2)
			{
				menu = cartMenu;
				break;
			}
			else if (input == 3)
			{
				menu = accountMenu;
				break;
			}
			else if (input == 4)
			{
				cart.clearOrders();
				menu = loginMenu;
				break;
			}
		}

		// Account menu. Displays prompts for user action. Can either display account information, add currency, or go back to the main menu
		while (menu == accountMenu)
		{
			string inputStr;
			int input;
			cout << "----------------- Account Menu -----------------" << endl;
			cout << "1. Display Account Information" << endl;
			cout << "2. Add currency" << endl;
			cout << "3. Return to Main Menu" << endl;
			while (getline(cin, inputStr))
			{
				stringstream stream(inputStr);
				if (stream >> input)
				{
					if (stream.eof())
					{
						break;
					}
				}
				cout << "Invalid input" << endl;
			}

			// checks user input and calls the correct functions from AccountInterface or sets the menu to the Main Menu.
			if (input == 1)
			{
				cout << "----------------- Account Information -----------------" << endl;
				accInterface.printAccountInfo();
			}
			else if (input == 2)
			{
				cout << "----------------- Add Currency -----------------" << endl;
				accInterface.addCurrencyPrompt();
			}
			else if (input == 3)
			{
				menu = baseMenu;
				break;
			}
		}

		// Menu for the shopping cart. Prompts user for various actions. 
		while (menu == cartMenu)
		{
			string inputStr;
			int input;
			cout << endl
				 << "----------------- Shopping Cart Menu -----------------" << endl;
			cout << "1. View Shopping Cart" << endl;
			cout << "2. Checkout" << endl;
			cout << "3. Remove Items from Shopping Cart" << endl;
			cout << "4. Return to Main Menu" << endl;
			while (getline(cin, inputStr))
			{
				stringstream stream(inputStr);
				if (stream >> input)
				{
					if (stream.eof())
					{
						break;
					}
				}
				cout << "Invalid input" << endl;
			}

			// checks user input and does the appropriate function call from ShoppingCart. 
			if (input == 1)
			{
				cout << cart.printCart() << endl;
				cout << "Press Enter to Continue";
				cin.ignore();
			}
			else if (input == 2)
			{

				int check = cart.processCart(currentUser, Products, history);

				//check if process cart failed or succeeded here.

				if (check == 0)
				{
					break;
				}
				else
				{
					cout << cart.createInvoice() << endl;
					cart.clearOrders();
					history.saveToDatabase();
					cout << endl
						 << "Press Enter to Continue";
					cin.ignore();
				}
			}
			else if (input == 3)
			{
				cart.removeOrderInterface();
				break;
			}
			else if (input == 4)
			{

				menu = baseMenu;
				break;
			}
		}
		
		// Admin Menu. Prompts user for different actions related to the admin. 
		while (menu == adminMenu)
		{

			string inputStr;
			int input;
			cout << endl
				 << "--------------------- Admin Menu ---------------------" << endl;
			cout << "1. Product Catalogue" << endl;
			cout << "2. Shopping Cart and Checkout" << endl;
			cout << "3. Account Menu" << endl;
			cout << "4. Add/Remove/Restock/Change Price" << endl;
			cout << "5. Add/Remove Discount" << endl;
			cout << "6. View Inventory Alerts" << endl;
			cout << "7. Logout" << endl;

			while (getline(cin, inputStr))
			{
				stringstream stream(inputStr);
				if (stream >> input)
				{
					if (stream.eof())
					{
						break;
					}
				}
				cout << "Invalid input" << endl;
			}

			// checks user input and either sets the menu appropriately, or calls a function related to the action. 
			if (input == 1)
			{
				menu = productMenu;
				break;
			}
			else if (input == 2)
			{
				menu = cartMenu;
				break;
			}
			else if (input == 3)
			{
				menu = accountMenu;
				break;
			}
			else if (input == 4)
			{
				adminInterface.AdminProductPrompt();
				break;
			}
			else if (input == 5)
			{
				adminInterface.AdminDiscountPrompt();
				break;
			}
			else if (input == 6)
			{
				Products.alertInterface();
				break;
			}
			else if (input == 7)
			{
				menu = loginMenu;
				break;
			}
		}
	}
}

// for (int i = 0; i < 1; i++)
// {
// 	cout << "----------------- Account Creation -----------------" << endl;
// 	loginInterface.createAccountPrompt();
// }

// cout << "----------------- Login -----------------" << endl;
// currentUser = loginInterface.loginPrompt();

// if (currentUser != NULL)
// {
// 	accInterface.setCurrentMember(currentUser);
// 	accInterface.addCurrencyPrompt();
// }

//save collection to file
// auto test = login.getLoginCollection().getMap();
// converter.LoginCollectionToFile(test);

// return 0;
