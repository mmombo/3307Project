/** \file DiscountCollection.h
 * \brief Functionality for maintaining the discount database.
 * \details Class that handles the processing of the discount database.
 * \author Justin Woo
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "DiscountCollection.h"

using namespace std;

/**
* Constructor to build empty discount collection
* @return None.
*/
DiscountCollection::DiscountCollection()
{
    std::unordered_map<std::string, Discount> temp;
    this->discountCollection = temp;
}
/**
* Constructor reads from product collection to check for discounts.
* @param pCollection Reference to product collection.
* @return None.
*/
DiscountCollection::DiscountCollection(ProductCollection *pCollection)
{
    std::unordered_map<std::string, Discount> temp;
    this->discountCollection = temp;

    ifstream input;
    string fileName;
    input.open("discounts.csv");

    string line, key;
    getline(input, line); // Skip first line of CSV file (headings)

    while (getline(input, line))
    { // Read lines of CSV file into a 'Discount' object
        istringstream iss(line);
        getline(iss, key, ',');
        string prodID = key;
        getline(iss, key, ',');
        string amount = key;

        Discount discount = Discount(prodID, stof(amount), 0, 0, 0);
        discountCollection[prodID] = discount; // Add discount to discount dictionary
        pCollection->getProduct(pCollection->findProduct(prodID))->setDiscount(&discountCollection[prodID]); // Update the product collection to hold the discount
    }
    input.close();
}

/**
* Destructor for discount collection.
* @return None.
*/
DiscountCollection::~DiscountCollection()
{
}

/**
* Attaches a discount and expiry date to a product.
* @param product Product to add the discount to.
* @param discountAmount Discount value for the product.
* @param day Day of discount expiry.
* @param month Month of discount expiry.
* @param year Year of discount expiry.
* @return None.
*/
void DiscountCollection::addDiscount(Product *product, float discountAmount, int day, int month, int year)
{
    if (discountAmount > 1)
    {
        cout << "A product may only have a discount of less than 100%" << endl;
        return;
    }

    // Product already has a global discount
    if (discountCollection.find(product->getID()) != discountCollection.end())
    {
        cout << "A product may only have one global discount. Please remove the current discount before adding another" << endl;
        return;
    }
    else
    {
        Discount discount = Discount(product->getID(), discountAmount, day, month, year);
        discountCollection[product->getID()] = discount;
        product->setDiscount(&discountCollection[product->getID()]);

        cout << "Discount was added successfully" << endl;
    }
}

/**
* Removes a discount association with a product.
* @param product Product to remove the discount from.
* @return None.
*/
void DiscountCollection::removeDiscount(Product *product)
{
    if (discountCollection.find(product->getID()) != discountCollection.end())
    {
        product->setDiscount(NULL);
        discountCollection.erase(product->getID());
        cout << "Discount was removed successfully" << endl;
        return;
    }
    else
    {
        cout << "This product does not have a discount" << endl;
        return;
    }
}

/**
* Saves discount information to discount database file.
* @return None.
*/
void DiscountCollection::saveToDatabase()
{
    // clears the csv file
    ofstream ofs;
    ofs.open("discounts.csv", ofstream::out | ofstream::trunc);
    ofs.close();

    // write the productsList vector into the empty csv file
    ofstream file;
    file.open("discounts.csv");
    file << "Product,Amount\n"; // create the column titles

    // create a discount entry for each discount in the list
    for (auto it : discountCollection)
    {
        file << it.first << "," << it.second.getAmount() << '\n';
    }

    file.close();
}