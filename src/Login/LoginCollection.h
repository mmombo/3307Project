/*! \file LoginCollection.h
    \brief Header file for LoginCollection.
*/
/*! \var std::unordered_map<std::string, std::pair<std::string, Member>> loginCollection
    \brief A LoginCollection object.
    
    An unordered map containing a string and string pair to store the login information of a vending machine user.
*/
/*! \var int currentHighestMemberID
    \brief Integer storing highest ID number of a member in the current session.
*/
/*! \fn LoginCollection()
    \brief Constructor for the LoginCollection() class.
*/
/*! \fn ~LoginCollection()
    \brief Destructor for the LoginCollection() class.
*/
/*! \fn int addMember(std::string username, std::string password, std::string fname, std::string lname, bool isAdmin, std::string membershipType)
    \brief Adds a member to the member database.
    \param username The username of the new member.
    \param password The password of the new member.
    \param fname The first name of the new member.
    \param lname The surname of the new member.
    \param isAdmin Boolean to determine if member is an admin.
    \param membershipType Membership type of the new member.
*/
/*! \fn Member *findMember(std::string username, std::string password)
    \brief Finds a member from the database.
    \param username The username of the member.
    \param password The password of the member.

*/
/*! \fn int deleteUser(std::string username, std::string password)
    \brief Deletes a user from the database.
    \param username The username of the member.
    \param password The password of the member.

*/
/*! \fn int changePassword(std::string username, std::string oldPassword, std::string newPassword)
    \brief Changes a particular member's password.
    \param username The username of the member.
    \param oldPassword The current password of the member.
    \param newPassword The password to assign to the member.

*/
/*! \fn std::unordered_map<std::string, std::pair<std::string, Member>> getMap()
    \brief Returns session information of this LoginCollection
*/
/*! \fn void setCollection(std::unordered_map<std::string, std::pair<std::string, Member>>,int highestID)
    \brief Updates session information
    \param highestID Current highestID in the member database.
*/
#ifndef LOGIN_COLLECTION_H
#define LOGIN_COLLECTION_H

#include <unordered_map>
#include <string>
#include "Member.h"

class LoginCollection
{
private:
    std::unordered_map<std::string, std::pair<std::string, Member>> loginCollection;
    int currentHighestMemberID;

public:
    LoginCollection();
    ~LoginCollection();
    int addMember(std::string username, std::string password, std::string fname, std::string lname, bool isAdmin, std::string membershipType);
    Member *findMember(std::string username, std::string password);

    int deleteUser(std::string username, std::string password);
    int changePassword(std::string username, std::string oldPassword, std::string newPassword);
	std::unordered_map<std::string, std::pair<std::string, Member>> getMap();
	void setCollection(std::unordered_map<std::string, std::pair<std::string, Member>>,int highestID);
};

#endif