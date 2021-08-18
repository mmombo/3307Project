/** \file LoginCollection.h
 * Class that stores the login information of the members of the vending machine system.
 * \author Justin Woo
 */

#include "LoginCollection.h"
#include <iostream>
#include <string>

LoginCollection::LoginCollection()
{
    currentHighestMemberID = 0;
}

/** Default destructor.
 * @return None.
 */
LoginCollection::~LoginCollection() 
{
}

/**
* Adds a user to the collection of logins with their username and password. Only adds to the collection if the password is secure enough
* @param username username of the new user
* @param password password of the new user (encoded)
* @param fname first name of new user
* @param lname last name of new user
* @param isAdmin admin status of new user
* @param membershipType membership type of new user
* @return 0 on success, -1 on failure (username already exists), -2 if password is not secure enough, -3 if fields are empty, -4 if name contains non alpha characters
*/
int LoginCollection::addMember(std::string username, std::string password, std::string fname, std::string lname, bool isAdmin, std::string membershipType)
{
    if (loginCollection.find(username) != loginCollection.end())
    {
        // username already exists
        return -1;
    }

    // check if fields are empty
    if (username.length() < 1 || fname.length() < 1 || lname.length() < 1)
    {
        return -3;
    }

    // check if password is secure enough
    bool digit, upper, lower, special;
    digit = upper = lower = special = false;
    int length = password.length();
    if (length < 8)
    {
        return -2;
    }
    for (int i = 0; i < length; i++)
    {
        if (islower(password[i]))
        {
            lower = true;
        }
        else if (isupper(password[i]))
        {
            upper = true;
        }

        if (isdigit(password[i]))
        {
            digit = true;
        }
        if (!isalpha(password[i]) && !isdigit(password[i]))
        {
            special = true;
        }
    }
    if (!lower || !upper || !digit || !special)
    {
        return -2;
    }

    // check if name contains non alpha characters
    for (unsigned i = 0; i < fname.length(); i++)
    {
        if (!isalpha(fname[i]))
        {
            return -4;
        }
    }
    for (unsigned i = 0; i < lname.length(); i++)
    {
        if (!isalpha(lname[i]))
        {
            return -4;
        }
    }

    //alternate way to insert
    currentHighestMemberID += 1;
    auto test = std::make_pair(password, Member(fname, lname, isAdmin, currentHighestMemberID, membershipType, 0.0));
    auto insert = std::make_pair(username, test);
    this->loginCollection.insert(insert);

    return 0;

    // add user to the collection
    /*
   loginCollection[username].first = password;
   loginCollection[username].second = Member(fname, lname, isAdmin, currentHighestMemberID += 1, membershipType);
    return 0;
	*/
}

/**
* Adds a user to the collection of logins with their username and password
* @param username username of the user
* @param password password of the user 
* @return NULL if username doesnt exist or password does not match, Member* if the member exists
*/
Member *LoginCollection::findMember(std::string username, std::string password)
{
    std::unordered_map<std::string, std::pair<std::string, Member>>::iterator search = loginCollection.find(username);
    if (search == loginCollection.end() || search->second.first != password)
    {
        // username does not exist in the system or password does not match

        // debugging to see if password mismatch or usename not in collection
        // std::cout << "Found password: " << (search->second.first)  << " Input password: " << password << std::endl;
        // std::cout << (search == loginCollection.end()) << (search->second.first != password);
        return NULL;
    }
    else
    {
        // username and password match entry
        return &search->second.second;
    }
}

/**
* Delete a user from the database with a specific username and password
* @param username: username of the user to be deleted
* @param password: password of the user to be deleted
* @return 0 on success, -1 if username doesnt exist or password does not match
*/
int LoginCollection::deleteUser(std::string username, std::string password)
{
    const Member *membercheck = findMember(username, password);
    if (membercheck == NULL)
    {
        return -1;
    }
    else
    {
        // Member exists and password is correct
        loginCollection.erase(username);
        return 0;
    }
}

/**
* Description: Changes the password of an existing user in the database
* @param username username of the user
* @param oldPassword oldPassword of the user 
* @param newPassword newPassword of the user 
* @return 0 on success, -1 if username does not exist or if oldPassword is incorrect for username
*/
int LoginCollection::changePassword(std::string username, std::string oldPassword, std::string newPassword)
{
    const Member *membercheck = findMember(username, oldPassword);
    if (membercheck == NULL)
    {
        return -1;
    }
    else
    {
        // Member exists and password is correct
        loginCollection[username].first = newPassword;
        return 0;
    }
}

std::unordered_map<std::string, std::pair<std::string, Member>> LoginCollection::getMap()
{

    return this->loginCollection;
}
void LoginCollection::setCollection(std::unordered_map<std::string, std::pair<std::string, Member>> map, int highestID)
{
    loginCollection = map;
    currentHighestMemberID = highestID;
}
