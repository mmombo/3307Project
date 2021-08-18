#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include "LoginCollection.h"

class Login
{
private:
    LoginCollection loginCollection;

public:
    Login();
    ~Login();
    Login(LoginCollection loginCollection);
    int createAccount(std::string username, std::string password, std::string fname, std::string lname, bool isAdmin, std::string membershipType);
    Member *checkLogin(std::string username, std::string password);

    void setLoginCollection(LoginCollection *collection);
	LoginCollection getLoginCollection();
};

#endif
