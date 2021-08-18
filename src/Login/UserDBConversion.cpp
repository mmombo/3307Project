/*! \file UserDBConversion.h
 * \brief Class to convert the userDB file to the login collection and to save from the login collection to the UserDB file
 * \details Class to convert the userDB file to the login collection and to save from the login collection to the UserDB file, ecrypts file upon saving
 * \authors Matthew Mombourquette
*/


#include "UserDBConversion.h"
#include <string>
#include <fstream>
#include <sstream>
#include "Member.h"
#include "LoginCollection.h"
#include <iostream>

UserDBConversion::UserDBConversion()
{
	highestID = -1;
};

UserDBConversion::~UserDBConversion()
{
}

/** Writes the LoginCollection to Output File
* @param map of type : std::unordered_map<std::string, std::pair<std::string, Member>>
* @return None.
*/
void UserDBConversion::LoginCollectionToFile(std::unordered_map<std::string, std::pair<std::string, Member>> &map)
{

	//open output file
	std::ofstream userFile;
	userFile.open("userDB.txt");
	std::ostringstream oss;
	std::string temp;
	//std::hash<std::string> hashed;

	//create iterator for unordered_map
	//std::unordered_map<std::string, std::pair<std::string, Member>>::iterator it = map.begin();

	//iterate through unordered_map and output everything
	for (std::unordered_map<std::string, std::pair<std::string, Member>>::iterator it = map.begin(); it != map.end(); ++it)
	{
		oss << it->second.second.getfname() << "," << it->second.second.getlname() << "," << it->second.second.getisadmin() << "," << it->second.second.getID() << ","
			<< it->second.second.getMembershipType() << "," << it->second.second.getCurrency() << "," << it->first << "," << it->second.first << " " << std::endl;
		temp = oss.str();
		temp = encryptDecrypt(temp);
		userFile << temp;
	}
};

/** Fills LoginCollection from input file.
* @return Map of login collections.
*/
std::unordered_map<std::string, std::pair<std::string, Member>> UserDBConversion::FileToLoginCollection()
{

	std::string tPass, tUserName = "0";
	std::string line;
	std::ifstream file("UserDB.txt");
	std::unordered_map<std::string, std::pair<std::string, Member>> map;

	std::stringstream ss;
	std::string temp;
	if (file.is_open())
	{
		// Decrypt the file
		while (getline(file, line))
		{
			temp = encryptDecrypt(line);
			ss << temp;
		}

		while (getline(ss, line))
		{

			std::string tFName, tLName, tMembershipType, tUser, tPass;
			bool tIsAdmin = 0;
			int tmemberID = 0;
			float tcurrency = 0;
			int counter = 1;
			//convert line to c string to process
			const char *start = line.c_str();
			bool inString = false;
			//cstring allows for this for loop because cstring terminated with null char
			for (const char *p = start; *p; p++)
			{

				//left this in from assignment one where we needed to parse strings within quotes that contained commas as well. might remodel this later because we dont need this functionality
				if (*p == '"')
				{
					inString = !inString;
				}
				// if ',' is reached and we are not instring, save the token up until that point
				//sliding window algorithm. "start" stays at start of word and p iterates forward until it finds a "," token saved as chars between start and p, then start will be updated to p+1 and process continues
				else if (*p == ',' && !inString)
				{
					std::string token = std::string(start, p - start);
					std::stringstream conversion(token);

					//switch is used to save the correct data as the line is parsed, counter used to know where we are in the line (know the positions of data we want from the .csv )
					switch (counter)
					{
					case (1):
						tFName = token;
						break;

					case (2):
						tLName = token;
						break;

					case (3):
						conversion >> tIsAdmin;
						break;

					case (4):
						conversion >> tmemberID;
						if (tmemberID > highestID)
						{
							highestID = tmemberID;
						}
						break;

					case (5):
						tMembershipType = token;
						break;

					case (6):
						conversion >> tcurrency;
						break;

					case (7):
						tUser = token;
						break;

					default:
						break;
					}
					//start pointer is only updated to p+1 when a word is found
					start = p + 1;
					counter++;
				}
			}
			//save final token since the for loop will end before saving the last token
			// have to remove the last char of the string because it is terminated by a null char which will affect comparisons
			//for whatever reason last line of the file doesnt have terminator so there MUST be a newline in the file after the last line
			std::string t = std::string(start);
			tPass = t.substr(0, t.size() - 1);
			//std::cout << "in userdbconversion: " << tPass << std::endl;

			//input all information from line into map and update the highest member id

			map[tUser].first = tPass;
			map[tUser].second = Member(tFName, tLName, tIsAdmin, tmemberID, tMembershipType, tcurrency);
		}
	}

	return map;
};

/** Returns integer value of highest unique member ID.
 * @return Integer value of highest unique member ID.
 */
int UserDBConversion::getHighestID()
{
	return highestID;
}

/** Encrypts specified string for security reasons.
 * @param text String of text to be encrypted.
 * @return None.
 */
std::string UserDBConversion::encryptDecrypt(std::string text)
{
	char key = 'L';
	std::string result = text;

	for (unsigned i = 0; i < text.size(); i++)
	{
		result[i] = text[i] ^ key;
	}
	return result;
}
