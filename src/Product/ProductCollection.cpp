/*! \file ProductCollection.h
 * \brief Functions for maintaining product database. 
 * \details Reads and writes from/to the product database, including adding products and monitoring stock. 
 * \authors Alex Broekhuyse, Shahryar Iqbal, Matthew Mombourquette
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <iomanip>
#include "../ShoppingCart/Order.h"
#include "ProductCollection.h"
using namespace std;

/**
* Constructor reads from database file and puts product objects into a vector.
* @param temp Tempory vector of product objects, use for loading products into application.
* @param input File stream for reading/writing product database file.
* @param fileName Specifies database file name.
* @param line Holds a product record read from database file.
* @param key Placeholder for specific product attribute (ID, price, etc).
* @param product Placeholder for product object to be inserted in vector.
* @return None.
*/
ProductCollection::ProductCollection()
{
    std::vector<Product> temp;
    this->productList = temp;

    ifstream input;
    string fileName;
    input.open("products.csv");

    string line, key;
    getline(input, line); // Skip first line of CSV file (headings)

    while (getline(input, line))
    { // Read lines of CSV file into a 'Product' object
        Product product;

        istringstream iss(line);
        getline(iss, key, ',');
        product.setID(key);
        getline(iss, key, ',');
        product.setName(key);
        getline(iss, key, ',');
        product.setCategory(key);
        getline(iss, key, ',');
        product.setPrice(std::stof(key));
        getline(iss, key, ',');
        // product.setDiscount(std::stof(key));
        getline(iss, key, ',');
        product.setQuantity(std::stoi(key));

        productList.push_back(product); // Add product to product list, rinse & repeat
    }
    input.close();
}
/**
 * Class destructor.
 * @return None.
 */
ProductCollection::~ProductCollection()
{
}
/**
* Adds a product. Adds a product to the productList, and writes product to database file.
* @param newProduct Product object of new product for database.
* @return None.
*/
// No need to take in quantity (like in UML diagram) because quantity is specified when creating Product object
void ProductCollection::addProduct(Product newProduct)
{
    bool inCollection = false; //! Checks if this product is already in the collection */
    for (unsigned i = 0; i < productList.size(); i++)
    {
        if (productList[i].getID() == newProduct.getID())
        {
            inCollection = true;
        }
    }

    if (inCollection)
    {
        cout << "This product shares the same ID as another product in the collection" << endl;
    }

    else
    {
        productList.push_back(newProduct);

        // Writes product to file in CSV format
        ofstream output;
        output.open("products.csv", std::ios_base::app);
        output << newProduct.getID() << "," << newProduct.getName() << "," << newProduct.getCategory() << "," << newProduct.getPrice() << "," << newProduct.getQuantity() << '\n'; // Outputs to .CSV
        output.close();

        cout << "Product was added successfully" << endl;
    }
}
/**
* Changes a product's on-hand quantity
* @param product Product to receive inventory change.
* @param quantity On-hand quantity to set product as having.
* @return None.
*/
void ProductCollection::changeInventory(Product product, int quantity)
{
    // Changes product quantity
    for (unsigned i = 0; i < productList.size(); i++)
    {
        if (productList[i].getID() == product.getID())
        {
            productList[i].setQuantity(quantity);
            saveToDatabase();
            return;
        }
    }
    cout << "Could not find the given product in the product collection" << endl;
}
/**
* Removes a product from the product collection.
* @param id Product's unique ID.
* @return None.
*/
void ProductCollection::removeProduct(string id)
{
    // Removes product and updates product list
    bool found = false; /*!< Checks if this product is in the collection */
    for (unsigned i = 0; i < productList.size(); i++)
    {
        if (productList[i].getID() == id)
        {
            found = true;
            productList.erase(productList.begin() + i);
            cout << "Product was removed from the product collection successfully" << endl;
            saveToDatabase();
        }
    }
    if (!found)
    {
        cout << "Product was not found in the product collection" << endl;
    }
}

/**
* Finds the index of the product contained in the product vector.
* @param id Product's unique ID.
* @return Int of the product's index in the product vector. Returns -1 if not found.
*/
int ProductCollection::findProduct(string id)
{
    for (unsigned i = 0; i < productList.size(); i++)
    {
        if (productList[i].getID() == id)
        {
            return i;
        }
    }
    return -1;
}
/**
* Changes a product's on-hand quantity
* @param product Product to receive inventory change.
* @param quantity On-hand quantity to set product as having.
* @return None.
*/
void ProductCollection::restockInventory(Product product, int quantity)
{
    bool found = false;
    for (unsigned i = 0; i < productList.size(); i++)
    {
        if (productList.at(i) == product)
        {
            found = true;
            cout << "Previous Quantity for " << productList.at(i).getName() << " was " << productList.at(i).getQuantity() << endl;
            productList.at(i).addQuantity(quantity);
            saveToDatabase();
            cout << "New Quantity for " << productList.at(i).getName() << " is " << productList.at(i).getQuantity() << endl;
            break;
        }
    }
    if (!found)
    {
        cout << "Product was not found in the collection." << endl;
    }
}
/**
* Sorts the product list according to price.
* @param order Either in increasing or decreasing price.
* @return None.
*/
void ProductCollection::sortByPrice(string order)
{
    if (order == "increasing")
    {
        sort(productList.begin(), productList.end(), [](Product &lhs, Product &rhs) {
            return lhs.getPrice() < rhs.getPrice();
        });
    }
    else if (order == "decreasing")
    {
        sort(productList.begin(), productList.end(), [](Product &lhs, Product &rhs) {
            return lhs.getPrice() > rhs.getPrice();
        });
    }
}
/**
* Sorts the product list according to category, alphabetically.
* @param order Either in increasing or decreasing order.
* @return None.
*/
void ProductCollection::sortByCategory(string order)
{
    if (order == "increasing")
    {
        sort(productList.begin(), productList.end(), [](Product &lhs, Product &rhs) {
            return lhs.getCategory() < rhs.getCategory();
        });
    }
    else if (order == "decreasing")
    {
        sort(productList.begin(), productList.end(), [](Product &lhs, Product &rhs) {
            return lhs.getCategory() > rhs.getCategory();
        });
    }
}
/**
* Changes the price of a product.
* @param product Product to receive price change.
* @param newPrice Updated price of product.
* @return None.
*/
void ProductCollection::changePrice(Product product, float newPrice)
{
    bool found = false;
    for (unsigned i = 0; i < productList.size(); i++)
    {
        if (productList.at(i) == product)
        {
            found = true;
            cout << "Previous Price for " << productList.at(i).getName() << " was " << productList.at(i).getPrice() << endl;
            productList.at(i).setPrice(newPrice);
            saveToDatabase();
            cout << "New Price for " << productList.at(i).getName() << " is " << productList.at(i).getPrice() << endl;
            break;
        }
    }
    if (!found)
    {
        cout << "Product was not found in the collection" << endl;
    }
}

/**
* Returns the amount of products in the collection.
* @return Integer amount of products.
*/
int ProductCollection::size()
{
    return productList.size();
}
/**
* Returns the product at specified index in product vector.
* @param index Index to search in product vector.
* @return Integer index of product in product vector.
*/
Product ProductCollection::at(int index)
{
    return productList[index];
}
/**
* Returns product found at specified index in product vector.
* @param index Index to search in product vector.
* @return Reference to product found at index
*/
Product *ProductCollection::getProduct(int index)
{
    return &productList[index];
}
/**
* Returns product collection vector.
* @return Vector of product objects
*/
std::vector<Product> ProductCollection::getProductList()
{
    return productList;
}
/**
* Saves any changes made to product collection to database file.
* @return None.
*/
void ProductCollection::saveToDatabase()
{
    // clears the csv file
    ofstream ofs;
    ofs.open("products.csv", ofstream::out | ofstream::trunc);
    ofs.close();

    // write the productsList vector into the empty csv file
    ofstream file;
    file.open("products.csv");
    file << "ID,Name,Category,Price,GlobalDiscount,Quantity,\n"; // create the column titles

    // create a product entry for each product in the list
    for (unsigned i = 0; i < productList.size(); i++)
    {
        file << productList.at(i).getID() << "," << productList.at(i).getName() << "," << productList.at(i).getCategory() << "," << productList.at(i).getPrice() << "," << productList.at(i).getQuantity() << "\n";
    }

    file.close();
}
/**
* Displays admin alerts for product collection based on inventory.
* @return None.
*/
void ProductCollection::alertInterface()
{

	cout << "------------------Current Inventory Alerts------------------" << endl << endl;

	for (unsigned i = 0; i < productList.size(); i++)
	{
		if (productList[i].getQuantity() < 5) 
		{
			cout << "Product: " << left << setw(20) << productList[i].getName() << " LOW STOCK - Current Stock: " << productList[i].getQuantity() << endl;
		}
		else if (productList[i].getQuantity() == 0) {
			cout << "Product: " << productList[i].getName() << " OUT OF STOCK - Current Stock: " << productList[i].getQuantity() << endl;
		}
		
	}
	
	cout <<endl<< "Press Enter to Continue";
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
}