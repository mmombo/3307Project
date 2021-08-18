/*!
 * \file AdminInterface.h
 * \brief Class containing the user interface for he admin menu
 * \details Class containing admin menu interface actions. Takes in user inputs and does the according actions. Can do add product, remove product, restock product, change price of product in adminProductPrompt(). Can do add discount and remove discount in the AdminDiscountPrompt().
 * \authors Justin Woo, Shahryar Iqbal
*/

#include "AdminInterface.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

constexpr auto TITLE = "|                                               ~   Products   ~                                               |";
constexpr auto SHOPTOP = "----------------------------------------------------------------------------------------------------------------";
constexpr auto SHOPLEFT = "| ";
constexpr auto SHOPRIGHT = "   |";
constexpr auto PRICEDIV = "    Price: ";

/**
* Default Constructor for this AdminInterface class. Takes in the product collection and discount collection databases as parameters and sets the attributes accordingly.
* @param productCollection product collection database.
* @param discountCollection dicount collection database.
*/
AdminInterface::AdminInterface(ProductCollection &productCollection, DiscountCollection &discountCollection)
{

	this->pCollection = &productCollection;
	this->dCollection = &discountCollection;
};

/**
* @brief Default destructor for AdminInterface. Just a null destructor
* @return None.
*/
AdminInterface::~AdminInterface()
{
}

/**
* @brief Method that displays the products currently in the product collection database. Prints out to the console each product along with their attributes. It displays the product's name, id, quantity, cost, and category.
* @return None.
*/
void AdminInterface::ProductDisplay()
{

	// print out products and prices, each with an assigned code.
	std::cout << SHOPTOP << std::endl
			  << TITLE << std::endl
			  << SHOPTOP << std::endl;

	if (pCollection->size() == 0)
	{
		std::cout << std::endl
				  << "Sorry No Products Available" << std::endl
				  << std::endl;
	}

	for (int i = 0; i < pCollection->size(); i++)
	{

		std::cout << SHOPLEFT << std::left << std::setw(4) << i + 1 << ".  "
				  << "ID: " << std::left << std::setw(10) << pCollection->getProductList().at(i).getID() << std::left << std::setw(20) << pCollection->getProductList().at(i).getName() << PRICEDIV << "$" << std::left << std::setw(10) << pCollection->getProductList().at(i).getPrice()
				  << "QTY: " << std::left << std::setw(10) << pCollection->getProductList().at(i).getQuantity() << std::left << std::setw(15) << pCollection->getProductList().at(i).getCategory();
		if (pCollection->getProductList().at(i).getDiscount() != NULL)
		{
			std::cout << "Discount: " << std::left << std::setw(2) << pCollection->getProduct(i)->getDiscount()->getAmount() * 100 << "%" << SHOPRIGHT << std::endl;
		}
		else
		{
			std::cout << "Discount: " << std::left << std::setw(2) << "N/A" << SHOPRIGHT << std::endl;
		}
	}

	cout << SHOPTOP << endl;
}

/**
*	Method that displays relevant prompts to the console and checks for user input. Depending on the input, performs product specific tasks and keeps looping until the exit input is placed.
*	@return None.
*/
void AdminInterface::AdminProductPrompt()
{
	// represents what action the user wants to do. Possible actions are shown below
	int action;

	while (true)
	{
		action = -1;
		// possible actions
		cout << "Please select one of the following options: " << endl;
		cout << "1: Add Product" << endl;
		cout << "2: Remove Product" << endl;
		cout << "3: Restock Product" << endl;
		cout << "4: Change Price of Product" << endl;
		cout << "0: Exit the admin menu" << endl;
		cin >> action;

		//if incorrect input, then prompt again
		while (cin.fail() || (action != 1 && action != 2 && action != 3 && action != 4 && action != 0))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error: You must pick one of the valid options" << endl;
			cout << "Please select one of the following options: " << endl;
			cout << "1: Add Product" << endl;
			cout << "2: Remove Product" << endl;
			cout << "3: Restock Product" << endl;
			cout << "4: Change Price of Product" << endl;
			cout << "0: Exit the admin menu" << endl;
			cin >> action;
		}

		// exit the admin menu
		if (action == 0)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			break;
		}

		// prompts for adding a product
		while (action == 1)
		{
			string id, productName, category;
			float price;
			int quantity;
			ProductDisplay();
			cout << "Please enter a unique product id\n"
				 << endl;
			cin >> id;

			if (cin.fail())
			{
				cout << "Invalid id input\n"
					 << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}

			cout << "Please enter the product name\n"
				 << endl;
			cin >> productName;

			if (cin.fail())
			{
				cout << "Invalid product name input\n"
					 << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}

			cout << "Please enter the product's category\n"
				 << endl;
			cin >> category;

			if (cin.fail())
			{
				cout << "Invalid category input\n"
					 << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}

			cout << "Please enter the price for the new product\n"
				 << endl;
			cin >> price;

			if (cin.fail() || price < 0)
			{
				cout << "Invalid price input. Must be a positive numeric value\n"
					 << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}

			cout << "Please enter the quantity for the new product\n"
				 << endl;
			cin >> quantity;

			if (cin.fail() || quantity < 0)
			{
				cout << "Invalid quantity input. Must be a positive integer value\n"
					 << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}

			Product newProduct = Product(productName, category, id, price, quantity, 0);
			this->pCollection->addProduct(newProduct);

			cin.clear();
			cin.ignore(1000, '\n');

			cout << "If you want to add product again, press 1\nTo go back to the main menu input 0" << endl;
			cin >> action;
			if (cin.fail() || (action != 1 && action != 0))
			{
				cout << "Invalid input. Returning to main menu" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				action = -1;
				break;
			}

			if (action == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
		}

		// prompts for removing a product
		while (action == 2)
		{
			ProductDisplay();
			string id;
			cout << "Please enter the product id of the product you want to remove" << endl;
			cin >> id;
			this->pCollection->removeProduct(id);

			cin.clear();
			cin.ignore(1000, '\n');

			cout << "If you want to remove product again, press 2\nTo go back to the main menu input 0" << endl;
			cin >> action;
			if (cin.fail() || (action != 2 && action != 0))
			{
				cout << "Invalid input. Returning to main menu" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				action = -1;
				break;
			}

			if (action == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
		}

		// prompts for restocking a product
		while (action == 3)
		{
			int choice, quantity;
			ProductDisplay();
			cout << "Enter number of product you wish to restock or enter 0 to exit " << endl
				 << "";
			cin >> choice;
			//if input is not an integer or is an integer that is negative, or greater than the size of the product list, then prompt again
			while (cin.fail() || choice > pCollection->size() || choice < 0)
			{

				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Error: You must enter number of displayed product" << endl;
				cout << "Please enter number of product you wish to restock or enter 0 to exit: " << endl;
				cin >> choice;
			}

			//if choice is 0 to exit
			if (choice == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
			//if input is integer and in the correct range
			else
			{
				int vectorIndex = choice - 1;

				Product selectedProduct = pCollection->getProductList().at(vectorIndex);

				cout << "Please enter the quantity you would like to add to the stock of the selected product" << endl;
				cin >> quantity;
				// if the quantity is 0 or less, then prompt again
				while (cin.fail() || quantity < 1)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Please enter a valid number" << endl;
					cin >> quantity;
				}
				this->pCollection->restockInventory(selectedProduct, quantity);
			}

			cin.clear();
			cin.ignore(1000, '\n');

			cout << "If you want to restock another product, press 3\nTo go back to the main menu input 0" << endl;
			cin >> action;
			if (cin.fail() || (action != 3 && action != 0))
			{
				cout << "Invalid input. Returning to main menu" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				action = -1;
				break;
			}

			if (action == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
		}

		// prompts for changing the price of a product
		while (action == 4)
		{
			int choice, price;
			ProductDisplay();
			cout << "Enter number of product you wish to change the price of or enter 0 to exit " << endl
				 << "";
			cin >> choice;
			//if input is not an integer, or is greater than the product collection size, or is negative, then prompt again
			while (cin.fail() || choice > pCollection->size() || choice < 0)
			{

				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Error: You must enter number of displayed product" << endl;
				cout << "Please enter number of product you wish to change the price of or enter 0 to exit: " << endl;
				cin >> choice;
			}

			//if choice is 0 to exit
			if (choice == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
			//if input is integer and in the correct range
			else
			{
				int vectorIndex = choice - 1;

				Product selectedProduct = pCollection->getProductList().at(vectorIndex);

				cout << "Please enter the new price of the selected product" << endl;
				cin >> price;
				while (cin.fail() || price < 0)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Please enter a valid number" << endl;
					cin >> price;
				}
				this->pCollection->changePrice(selectedProduct, price);
			}

			cin.clear();
			cin.ignore(1000, '\n');

			cout << "If you want to change price of another product, press 4\nTo go back to the main menu input 0" << endl;
			cin >> action;
			if (cin.fail() || (action != 4 && action != 0))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input. Returning to main menu" << endl;
				action = -1;
				break;
			}

			if (action == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
		}
	}
}

/**
*	Method that displays relevant prompts to the console and checks for user input. Depending on the input, performs specific task regarding discounts and keeps looping until the exit input is placed.
*	@return None.
*/
void AdminInterface::AdminDiscountPrompt()
{
	// represents what action the user wants to do. Possible actions are shown below
	int action;

	while (true)
	{

		// possible actions
		cout << "Please select one of the following options: " << endl;
		cout << "1: Add Discount" << endl;
		cout << "2: Remove Discount" << endl;
		cout << "0: Exit the admin menu" << endl;
		cin >> action;

		//if incorrect input, then prompt again
		while (cin.fail() || (action != 1 && action != 2 && action != 0))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error: You must pick one of the valid options" << endl;
			cout << "Please select one of the following options: " << endl;
			cout << "1: Add Discount" << endl;
			cout << "2: Remove Discount" << endl;
			cout << "0: Exit the admin menu" << endl;
			cin >> action;
		}

		if (action == 0)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			break;
		}
		while (action == 1)
		{
			ProductDisplay();
			int choice = -1;
			cout << "Enter number of product or enter 0 to exit " << endl;
			cin >> choice;
			//if input is not an integer enter this loop
			while (cin.fail() || choice > pCollection->size() || choice < 0)
			{

				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Error: You must enter number of displayed product" << endl;
				cout << "Please enter number of product or enter 0 to exit: " << endl;
				cin >> choice;
			}

			//if choice is 0 to exit
			if (choice == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
			//if input is integer and in the correct range
			else
			{
				int vectorIndex = choice - 1;

				float amount = 0;
				cout << "Enter the discount amount in percent: " << endl;
				cin >> amount;

				//if input is invalid
				while (cin.fail() || amount < 0 || amount > 100)
				{

					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Error: You must enter a valid percentage" << endl;
					cout << "Please enter the discount amount in percent: " << endl;
					cin >> amount;
				}
				// Prompts for adding expiration date if implemented
				// int day, month, year;

				// cout << "Enter the expiry day of the month: " << endl;
				// cin >> day;
				// while (cin.fail() || day < 0 || day > 31)
				// {
				// 	cin.clear();
				// 	cin.ignore(1000, '\n');
				// 	cout << "Error: You must enter a valid day" << endl;
				// 	cout << "Please enter the expiry day: " << endl;
				// 	cin >> day;
				// }

				// cout << "Enter the expiry month: " << endl;
				// cin >> month;
				// while (cin.fail() || month < 0 || month > 12)
				// {
				// 	cin.clear();
				// 	cin.ignore(1000, '\n');
				// 	cout << "Error: You must enter a valid month" << endl;
				// 	cout << "Please enter the expiry month: " << endl;
				// 	cin >> month;
				// }

				// cout << "Enter the expiry year: " << endl;
				// cin >> year;
				// while (cin.fail() || year < 0)
				// {
				// 	cin.clear();
				// 	cin.ignore(1000, '\n');
				// 	cout << "Error: You must enter a valid year" << endl;
				// 	cout << "Please enter the expiry year: " << endl;
				// 	cin >> year;
				// }

				dCollection->addDiscount(pCollection->getProduct(vectorIndex), amount / 100, 0, 0, 0);
			}
		}

		// prompts for removing a discount
		while (action == 2)
		{
			ProductDisplay();
			int choice;
			cout << "Enter number of product or enter 0 to exit" << endl;
			cin >> choice;
			while (cin.fail() || choice > pCollection->size() || choice < 0)
			{

				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Error: You must enter number of displayed product" << endl;
				cout << "Please enter number of product or enter 0 to exit: " << endl;
				cin >> choice;
			}
			//if choice is 0 to exit
			if (choice == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
			dCollection->removeDiscount(pCollection->getProduct(choice - 1));

			cout << "If you want to remove another discount, press 2\nTo go back to the main menu input 0" << endl;
			cin >> action;
			if (cin.fail() || (action != 2 && action != 0))
			{
				cout << "Invalid input. Returning to main menu" << endl;
				action = -1;
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}

			if (action == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
		}
	}
}