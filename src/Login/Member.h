#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include "CreditCardCompany.h"

class Member
{
private:
    float currency;
    std::string membershipType; // Probably need to change this to something other than string
    std::string fname;
    std::string lname;
    bool isAdmin;
    int memberID;

    bool validateCreditCard(std::string number, int month, int year, std::string name, std::string securityCode, CreditCardCompany company);
    //purchasehistory
    //lastlogin

public:
    Member();
    ~Member();
    Member(std::string fname, std::string lname, bool isAdmin, int memberID, std::string membershipType);
	Member(std::string fname, std::string lname, bool isAdmin, int memberID, std::string membershipType, float currency);
    int addCurrency(float quantity, std::string number, int month, int year, std::string name, std::string securityCode, CreditCardCompany company);
    void modifyBalance(float quantity);
    void setMembershipType(std::string membershipType);
    float getCurrency() const;
    std::pair<std::string, std::string> getName() const;
    int getID() const;
	std::string getfname() const; 
	std::string getlname() const;
	bool getisadmin() const;
	std::string getMembershipType() const;
};

#endif
