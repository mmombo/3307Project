/** \file Login.h
 * \brief A class to provide the login functions, dealing with the raw passwords
 * \details This class may be removed depending on how security for the passwords will be handled.
 * \author Justin Woo
 */
#include "Login.h"

/** Default constructor.
 * @return None.
 */
Login::Login()
{
}

/** Default destructor.
 * @return None.
 */
Login::~Login() {

}

/**
* Constructor for Login class to set the LoginCollection
* @param loginCollection The collection used to store the username and password data
* @return none
*/
Login::Login(LoginCollection loginCollection)
{
    this->loginCollection = loginCollection;
}

/**
* Adds a user to the collection of logins with their username and password
* @param username username of the new user
* @param password password of the new user 
* @return 0 on success, -1 on failure (username already exists)
*/
int Login::createAccount(std::string username, std::string password, std::string fname, std::string lname, bool isAdmin, std::string membershipType)
{
    // Directly add user to login collection (update to encrypt password)
    return loginCollection.addMember(username, password, fname, lname, isAdmin, membershipType);
}

/**
* Adds a user to the collection of logins with their username and password
* @param username username of the new user
* @param password password of the new user
* @return Pointer to the member
*/
Member *Login::checkLogin(std::string username, std::string password)
{
    // Directly add user to login collection (update to encrypt password)
    return loginCollection.findMember(username, password);
}
/**
 * Sets the login collction attached to the login system
 * @param collection the login collection
 * @return None.
 */
void Login::setLoginCollection(LoginCollection *collection)
{
    loginCollection = *collection;
}
/**
 * Returns the login collection attached to the login system
 * @return the login collection
 */
LoginCollection Login::getLoginCollection() {
	return loginCollection;
}