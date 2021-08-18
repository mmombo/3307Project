/*! \file Product.h
 * \brief Class containing a product object. 
 * \details Class containing a product object including its unique information. Also includes getter and setter methods for changing product details and data retrieval. 
 * \authors Alex Broekhuyse, Shahryar Iqbal
*/
#include <string>
#include "Product.h"
#include <iostream>

using namespace std;

/**
* Default constructor to declare a new product. Sets all string values as blank, and float values of 0
* @return None.
*/
Product::Product() {
    this->id = "";
    this->productName = "";
    this->category = "";
    this->price = 0.00;
	this->discount = NULL;
    this->bulkModifier = 0.00;
    this->quantity = 0;
}
/**
* Constructor with specific parameters.
* @param id Unique product tag.
* @param productName Name of the product.
* @param category Specific product category.
* @param price Price of the product.
* @param discount Product discount.
* @param quantity On-hand quantity of the product.
* @param bulkModifier
* @return None.
*/
Product::Product(std::string productName, std::string category, std::string id, float price, int quantity, float bulkModifier) {
	this->productName = productName;
	this->category = category;
	this->id = id;
	this->price = price;
	this->quantity = quantity;
	this->discount = NULL;
	this->bulkModifier = bulkModifier;
}

/**
* Constructor with bulkModifier set to 0.
* @param id Unique product tag.
* @param productName Name of the product.
* @param category Specific product category.
* @param price Price of the product.
* @param discount Product discount.
* @param quantity On-hand quantity of the product.
* @return None.
*/
Product::Product(std::string productName, std::string category, std::string id, float price, int quantity) {
	this->productName = productName;
	this->category = category;
	this->id = id;
	this->price = price;
	this->quantity = quantity;
	this->discount = NULL;
	this->bulkModifier = 0;
}

/**
* Destructor of the Product class.
* @return None.
*/
Product::~Product() {
}
/**
* Sets the unique product ID.
* @param new_id Unique ID for the product.
* @return None.
*/
void Product::setID(string new_id) {
    id = new_id;
}
/**
* Sets a product name.
* @param new_name Name for the product.
* @return None.
*/
void Product::setName(string new_name) { 
    productName = new_name; 
}
/**
* Sets the category of the product.
* @param new_category Category for the product.
* @return None.
*/
void Product::setCategory(string new_category) {
    category = new_category;
}
/*void Product::setDiscount(float new_discount) {
    discount = new_discount;
}*/
/**
* Sets the price of the product.
* @param new_price Price of the product.
* @return None.
*/
void Product::setPrice(float new_price) { 
    price = new_price; 
}
/**
* Sets the on-hand quantity of the product.
* @param new_quantity Quantity of the product.
* @return None.
*/
void Product::setQuantity(int new_quantity) { 
    quantity = new_quantity; 
}
/**
* Sets the product discount.
* @param *new_discount Product discount.
* @return None.
*/
void Product::setDiscount(Discount *new_discount){
	discount = new_discount;
}
/**
* Gets the unique product ID.
* @return A string with the unique product ID.
*/
string Product::getID() const{
    return id;
}
/**
* Gets the product name.
* @return A string with the product name.
*/
string Product::getName() { 
    return productName; 
}
/**
* Gets the product category.
* @return A string with the product category.
*/
string Product::getCategory() {
    return category;
}
/**
* Gets the product's discount.
* @return A discount object for the product.
*/
Discount* Product::getDiscount() {
    return discount;
}
/**
* Gets the price of the product.
* @return A float with the product price.
*/
float Product::getPrice() { 
    return price; 
}
/**
* Gets the on-hand quantity of the product.
* @return An integer representing the product's quantity.
*/
int Product::getQuantity() { 
    return quantity; 
}
/**
* Adds to the product's on-hand quantity.
* @param quantity Integer quantity to be added to current on-hand quantity.
* @return None.
*/
void Product::addQuantity(int quantity) {
	this->quantity += quantity;
}
/**
* Compares two unique product IDs to see if they are the same.
* @param other Product object to check against
* @return True if both product IDs are the same, false if not.
*/
bool Product::operator == (const Product& other) {
	return this->getID() == other.getID();
}

ostream& operator<<(ostream& os, const Product& prod) {
	os << prod.productName << "    " << prod.category << "    " << prod.id << "    " << prod.price << "    " << prod.quantity << "    " << prod.bulkModifier << endl;
	return os;
}
