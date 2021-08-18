/** \file Discount.h
 * \brief Class containing the discount object.
 * \details The discount object, containing information for which product the disount is for, 
 * the value of the discount, and the discount's expiry date.
 * \author Justin Woo
 */

#include "Discount.h"
using namespace std;

/**
* Default constructor, creates a discount object.
* @return None.
*/
Discount::Discount()
{
}

/** 
 * Contructor with parameters for creating a discount object.
* @param product Product to associate the discount with.
* @param amount Value of the discount.
* @param day Day the discount expires.
* @param month Month the discount expires.
* @param year Year the discount expires.
* @return None.
*/
Discount::Discount(string product, float amount, int day, int month, int year){
    this->productID = product;
    this->amount = amount;
    this->endDate = tm();
    endDate.tm_mday = day;
    endDate.tm_mon = month;
    endDate.tm_year = year;
}

/**
 * Class destructor.
 * @return None.
 */
Discount::~Discount()
{
}

/**
* Gets the unique product ID associated with a discount.
* @return String of unique product ID.
*/
string Discount::getProductID(){
    return productID;
}

/**
* Gets the value of the discount
* @return Float of discount's value.
*/
float Discount::getAmount(){
    return amount;
}

/**
* Checks by date if a discount has expired.
* @return True if the discount is valid, false if it is expired.
*/
bool Discount::checkDate(){
    return false;
}