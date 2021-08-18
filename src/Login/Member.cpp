/** \file Member.h
 * \brief Class that contains the data for a member in the vending machine system.
 * \details Contains the name, member status, ID, member type and currency of the member.
 * \author Justin Woo
 */
//#include <iostream> // TEMP FOR DEBUGGING
#include <ctime>
#include <math.h>
#include "Member.h"

using namespace std;

/** Default constructor.
 * @return None.
 */
Member::Member()
{
}

/** Default destructor.
 * @return None.
 */
Member::~Member() {

}

/**
* Constructor for Member class to initialize new member
* @param name Name of the new member
* @param isAdmin Admin status of the member
* @param memberID ID of the member
* @param membershipType membership type of the new member
* @return none
*/
Member::Member(std::string fname, std::string lname, bool isAdmin, int memberID, std::string membershipType)
{
    this->fname = fname;
    this->lname = lname;
    this->isAdmin = isAdmin;
    this->memberID = memberID;
    this->membershipType = membershipType;
    currency = 0;
}

/**
* Constructor for Member class to add user from DB to collection
* @param fname First name of the new member
* @param lname Surname of the new member
* @param isAdmin Admin status of the member
* @param memberID ID of the member
* @param membershipType membership type of the new member
* @param currency amount of currency on member account
* @return none
*/
Member::Member(std::string fname, std::string lname, bool isAdmin, int memberID, std::string membershipType, float currency)
{
    this->fname = fname;
    this->lname = lname;
    this->isAdmin = isAdmin;
    this->memberID = memberID;
    this->membershipType = membershipType;
    this->currency = currency;
}

/**
* Takes credit card information and amount of currency to add as parameters and checks if the card is valid, if valid then adds to the member's currency
* @param quantity amount of currency to be added
* @param number credit card number as a string
* @param month expiry month as an int
* @param year expiry year as an int
* @param name name of the card holder
* @param securityCode security code for credit card as a string
* @param company the providing credit card company as an enum of CreditCardCompany
* @return 0 if currency added, -1 if not added
*/
int Member::addCurrency(float quantity, std::string number, int month, int year, std::string name, std::string securityCode, CreditCardCompany company)
{
    // check if quantity in valid format
    if (currency < 0)
    {
        return -1;
    }

    // add currency rounded to two decimal places to account if credit card is valid
    if (validateCreditCard(number, month, year, name, securityCode, company))
    {
        currency += roundf(quantity * 100) / 100;
        return 0;
    }
    else
    {
        return -1;
    }
}

/**
* Adds the specified quantity to the current amount of currency while bypassing the card validation process, rounds to the nearest two decimal places
* @param quantity amount of currency to be added
* @return none
*/
void Member::modifyBalance(float quantity)
{
    currency += roundf(quantity * 100) / 100;
}

/**
* Takes credit card information as parameters and checks if the card is valid
* @param number credit card number as a string
* @param month expiry month as an int
* @param year expiry year as an int
* @param name name of the card holder
* @param securityCode security code for credit card as a string
* @param company the providing credit card company as an enum of CreditCardCompany
* @return true if the card is valid, false if the card is invalid
*/
bool Member::validateCreditCard(std::string number, int month, int year, std::string name, std::string securityCode, CreditCardCompany company)
{
    // check the credit card number and security code to the providing company
    switch (company)
    {
    case visa: // start with 4 and 16 digits and 3 digit security code
        if (number[0] != '4' || number.length() != 16 || securityCode.length() != 3)
        {
            //cerr << "Type error." << endl;
            return false;
        }
        break;
    case americanExpress: // start with 37 and 15 digits and 4 digit security code
        if (number[0] != '3' || number[1] != '7' || number.length() != 15 || securityCode.length() != 4)
        {
            //cerr << "Type error." << endl;
            return false;
        }
        break;
    case masterCard: // start with 5 and 16 digits and 3 digit security code
        if (number[0] != '5' || number.length() != 16 || securityCode.length() != 3)
        {
            //cerr << "Type error." << endl;
            return false;
        }
        break;
    }

    // check to see if name is valid
    for (unsigned i = 0; i < name.length(); i++)
    {
        if (!isalpha(name[i]))
        {
            return false;
        }
    }

    // check the credit card number using Luhn algorithm

    // double every second digit and sum the individual digits
    int sum = 0;
    for (int i = number.length() - 2; i >= 0; i -= 2)
    {
        int temp = (number[i] - '0') * 2; // convert to int and then multiply by 2

        // if double digit then convert take sum of digits
        if (temp > 9)
        {
            temp = 1 + temp % 10;
        }
        sum += temp;
    }
    // sum odd digits from right to left
    for (int i = number.length() - 1; i >= 0; i -= 2)
    {
        sum += number[i] - '0';
    }

    if (sum % 10 != 0)
    {
        //cerr << "Number Error" << endl;
        return false;
    }

    // COULD MOVE INTO ITS OWN CLASS FOR USE IN EXPIRATION DATES FOR PRODUCTS, ETC
    // check the expiry date to the current date
    time_t currSec = time(NULL);        // get number of seconds since epoch
    tm *currTime = localtime(&currSec); // convert to days/months/years

    // month in range of 1-12
    if (month > 12 || month < 1)
        return false;

    // check if card is expired
    if ((currTime->tm_year - 100) > year || ((currTime->tm_year - 100) == year && (currTime->tm_mon + 1) > month))
    {
        //cerr << "Expired Card" << endl;
        //cerr << currTime->tm_year-100<< " " << currTime->tm_mon +1 << endl;
        return false;
    }

    // otherwise card is valid
    return true;
}

/** Gets name of member. Returns first name and last name of the member.
 * @return A pair of strings containing the first name and surname of the member.
 */
std::pair<std::string, std::string> Member::getName() const
{
    return std::pair<std::string, std::string>(fname, lname);
}

/** Gets the unique ID of the member.
 * @return Unique member ID of this member.
 */
int Member::getID() const
{
    return memberID;
}

/** Gets the amount of currency this member has in the application.
 * @return Float value of the amount of currency this member has in their account.
 */
float Member::getCurrency() const
{
    return currency;
}
/** Gets the first name of this member.
 * @return A string containing first name of this member.
 */
std::string Member::getfname() const
{
    return fname;
}
/** Gets the surname of this member.
 * @returns A string containg this member's surname.
 */
std::string Member::getlname() const
{
    return lname;
}
/** Gets the isAdmin boolean of this member. Determines if this member is an admin by returning the isAdmin attribute of this member.
 * @return A boolean that is true if the member is an admin, false if not.
 */
bool Member::getisadmin() const
{
    return isAdmin;
}
/** Gets the membership type of this member.
 * @return A string describing the membership type of this member.
 */
std::string Member::getMembershipType() const
{
    return membershipType;
}
/** Sets the membership type of this member.
 * @param membershipType The membership type to assign to this member.
 * @return None.
 */
void Member::setMembershipType(std::string membershipType)
{
    this->membershipType = membershipType;
}