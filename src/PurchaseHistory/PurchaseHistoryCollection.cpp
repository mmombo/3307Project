/** \file PurchaseHistoryCollection.h
 * \brief Functionality for purchase history database. 
 * \details Class for reading/writing the purchase history database file, including updating and removing entries.
 * \author Michael Schmittat
 */

#include "PurchaseHistoryCollection.h"
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

/** Reads database file into the application. Constructor that opens the collection database file. Reads
 * orders, and creates a purchase history for orders associated with a particular member.
 * @return None.
 */
PurchaseHistoryCollection::PurchaseHistoryCollection() {
	std::ifstream input;
	input.open("history.csv");
	
	std::string line, key;
	// Skip first three csv lines
	getline(input, line);
	getline(input, line);
	getline(input, line);
	
	while(getline(input, line)) {
		std::list<Order> ordList;
		
		std::istringstream iss(line);
		// Skip identifier
		getline(iss, key, ',');
		getline(iss, key, ',');
		int memberID = std::stoi(key);
		getline(iss, key, ',');
		double rawtime = std::stod(key);
		getline(iss, key, ',');
		int orders = std::stoi(key);	
		
		for(int c = 0; c < orders; c++) {
			// New line
			getline(input, line);
			std::istringstream nestIss(line);
			// Get constructor components for Order
			getline(nestIss, key, ',');
			getline(nestIss, key, ',');
			int oQty = std::stoi(key);
			getline(nestIss, key, ',');
			//float tCost = std::stof(key);
			getline(nestIss, key, ',');
			
			// New line
			getline(input, line);
			std::istringstream nestIss2(line);
			// Create Product
			Product product;
			getline(nestIss2, key, ',');
			getline(nestIss2, key, ',');
			product.setID(key);
			getline(nestIss2, key, ',');
			product.setName(key);
			getline(nestIss2, key, ',');
	        product.setCategory(key);
	        getline(nestIss2, key, ',');
	        product.setPrice(std::stof(key));
	        getline(nestIss2, key, ',');
			product.setQuantity(std::stoi(key));
			getline(nestIss2, key, ',');
			float disc = std::stof(key);
			if(disc != 0) {
				Discount d = Discount(product.getID(), disc, 1, 1, 100);
				product.setDiscount(&d);
			}
			// Create and push Order
			Order order = Order(product, 0, oQty);
			ordList.push_back(order);
		}
		
		// Add the completed PurchaseHistory to the map
		PurchaseHistory ph = PurchaseHistory(ordList, memberID, rawtime);
		//std::cout << ph.printHistory() << '\n';
		addPurchaseHistory(ph);
	}
	
	input.close();
}

/** Class destructor.
 * @return None.
 */
PurchaseHistoryCollection::~PurchaseHistoryCollection() {}

/** Gets a single PurchaseHistory for a particular member.
 * @param memberID Unique member ID of the member.
 * @param date Timestamp of the purchase history
 * @return A PurchaseHistory for the specified member.
 */
PurchaseHistory PurchaseHistoryCollection::getPurchaseHistory(int memberID, time_t date) {
	if(historyCollection.find(memberID) != historyCollection.end()) {
		std::vector<PurchaseHistory> histories = historyCollection.at(memberID);
		
		for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
			if(i->getRawTime() == date)
				return *i;
		}	
	}
	
	return PurchaseHistory();
}

/** @brief Gets purchase history for a member.
 * @details Gets purchase history for a member using their unique member ID.
 * @param memberID The unique member ID of the member to grab purchase history for
 * @return A vector of purchase histories associated with the member.
 */
std::vector<PurchaseHistory> PurchaseHistoryCollection::getHistoriesByID(int memberID) {
	if(historyCollection.find(memberID) != historyCollection.end())
		return historyCollection.at(memberID);
	
	return std::vector<PurchaseHistory>();
}

/** @brief Gets purchase history before a particuular date.
 * @details Given a unique member ID and a date, get the purchase history of this particular member
 * before the specified date.
 * @param memberID Unique member ID of member to search through purchase histories.
 * @param date Reference date to check purchase histories before.
 * @return A vector of purchase histories associated with the member before the specified date.
 */
std::vector<PurchaseHistory> PurchaseHistoryCollection::getMemberHistoriesBefore(int memberID, time_t date) {
	if(historyCollection.find(memberID) == historyCollection.end())
		return std::vector<PurchaseHistory>();
		
	std::vector<PurchaseHistory> histories = historyCollection.at(memberID);
	std::vector<PurchaseHistory> histList;
	
	for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
		if(difftime(i->getRawTime(), date) < 0)
			histList.push_back(*i);	
	}
	
	return histList;
}

/** @brief Gets purchase history after a particular date.
 * @details Given a unique member ID and a date, get the purchase history of this particular member
 * after the specified date.
 * @param memberID Unique member ID of member to search through purchase histories.
 * @param date Reference date to check purchase histories after.
 * @return A vector of purchase histories associated with the member after the specified date.
 */
std::vector<PurchaseHistory> PurchaseHistoryCollection::getMemberHistoriesAfter(int memberID, time_t date) {
	if(historyCollection.find(memberID) == historyCollection.end())
		return std::vector<PurchaseHistory>();
		
	std::vector<PurchaseHistory> histories = historyCollection.at(memberID);
	std::vector<PurchaseHistory> histList;
	
	for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
		if(difftime(i->getRawTime(), date) > 0)
			histList.push_back(*i);	
	}
	
	return histList;
}

/** @brief Gets purchase history within a 24-hour span.
 * @details Given a unique member ID and a date, get the purchase history of this particular member over the past 24 hours.
 * @param memberID Unique member ID of member to search through purchase histories.
 * @param date Reference date to check purchase histories before.
 * @return A vector of purchase histories associated with the member within the past 24 hours.
 */
std::vector<PurchaseHistory> PurchaseHistoryCollection::getMemberHistoriesWithinDay(int memberID, time_t date) {
	if(historyCollection.find(memberID) == historyCollection.end())
		return std::vector<PurchaseHistory>();
		
	std::vector<PurchaseHistory> histories = historyCollection.at(memberID);
	std::vector<PurchaseHistory> histList;
	
	for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
		// Check the difference in seconds, push anything within 86,400 seconds (24 hours)
		if(std::abs(difftime(i->getRawTime(), date)) <= 86400)
			histList.push_back(*i);	
	}
	
	return histList;
}

/** @brief Gets all purchase histories before a particular date.
 * @details Given a date, get the purchase histories of all members before said date.
 * @param date Reference date to check purchase histories before.
 * @return A vector of purchase histories from the database created before given date.
 */
std::vector<PurchaseHistory> PurchaseHistoryCollection::getAllHistoriesBefore(time_t date) {
	std::vector<PurchaseHistory> histList;
	for(std::unordered_map<int, std::vector<PurchaseHistory>>::iterator it = historyCollection.begin(); it != historyCollection.end(); it++) {
	
		std::vector<PurchaseHistory> histories = it->second;
	
		for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
			if(difftime(i->getRawTime(), date) < 0)
				histList.push_back(*i);
		}	
	}
	
	return histList;
}

/**
* Gets all PurchaseHistory objects in the collection that occur after the provided time.
* @param date time_t raw time in seconds.
* @return vector<PurchaseHistory> All PurchaseHistory objects that occur after date.
*/
std::vector<PurchaseHistory> PurchaseHistoryCollection::getAllHistoriesAfter(time_t date) {
	std::vector<PurchaseHistory> histList;
	for(std::unordered_map<int, std::vector<PurchaseHistory>>::iterator it = historyCollection.begin(); it != historyCollection.end(); it++) {
	
		std::vector<PurchaseHistory> histories = it->second;
	
		for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
			if(difftime(i->getRawTime(), date) > 0)
				histList.push_back(*i);
		}	
	}
	
	return histList;
}

/**
* Gets all PurchaseHistory objects in the collection within 24 hours of the provided time.
* @param date time_t raw time in seconds.
* @return vector<PurchaseHistory> All PurchaseHistory objects that occur within 24 hours of date.
*/
std::vector<PurchaseHistory> PurchaseHistoryCollection::getAllHistoriesWithinDay(time_t date) {
	std::vector<PurchaseHistory> histList;
	for(std::unordered_map<int, std::vector<PurchaseHistory>>::iterator it = historyCollection.begin(); it != historyCollection.end(); it++) {
	
		std::vector<PurchaseHistory> histories = it->second;
	
		for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
			// Check the difference in seconds, push anything within 86,400 seconds (24 hours)
			if(std::abs(difftime(i->getRawTime(), date)) <= 86400)
				histList.push_back(*i);
		}
	}
	
	return histList;
}

/**
* Adds a PurchaseHistory object to the collection.
* @param history PurchaseHistory object to be added.
* @return None.
*/
void PurchaseHistoryCollection::addPurchaseHistory(PurchaseHistory history) {
	int memberID = history.getMemberID();
	
	// If empty, initialize new vector and place inside collection
	if(historyCollection.find(memberID) == historyCollection.end()) {
		std::vector<PurchaseHistory> histList (1, history);
		//historyCollection.insert(std::make_pair<int, std::vector<PurchaseHistory>>(memberID, histList));
		historyCollection.emplace(memberID, histList);
	}
	else {
		// Just add history to existing list
		historyCollection.at(memberID).push_back(history);
	}
}

/**
* Removes a single PurchaseHistory object from the collection. 
* @param memberID int ID that specifies the member the PurchaseHistory belongs to.
* @param date time_t raw time in seconds that specifies when PurchaseHistory occured.
* @return 0 if deletion was succesful, -1 if PurchaseHistory could not be found.
*/
int PurchaseHistoryCollection::deletePurchaseHistory(int memberID, time_t date) {
	if(historyCollection.find(memberID) != historyCollection.end()) {
		std::vector<PurchaseHistory> histories = historyCollection.at(memberID);
		
		for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
			if(i->getRawTime() == date) {
				histories.erase(i, i);
				return 0;
			}
		}
	}
	
	return -1;
}

/**
* Removes all PurchaseHistory objects associaed with a Member from the collection. 
* @param memberID int ID that specifies the member the PurchaseHistory objects belong to.
* @return 0 if deletion was succesful, -1 if no PurchaseHistory could not be found.
*/
int PurchaseHistoryCollection::deleteAllHistoriesByMember(int memberID) {
	if(historyCollection.find(memberID) != historyCollection.end()) {
		historyCollection.erase(memberID);
		return 0;
	}	
	
	return -1;
}

/**
* Saves all PurchaseHistory objects in the collection to file in .csv format.
* @return None.
*/
void PurchaseHistoryCollection::saveToDatabase() {
	// Clears csv file
	std::ofstream ofs;
	ofs.open("history.csv", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	
	// Begin writing to csv
	std::ofstream file;
	file.open("history.csv");
	// Column line
	file << "History,mID,rawtime,length\n";
	file << "Order,quantity,totalcost,dateofpurchase\n";
	file << "Product,pID,name,category,price,quantity,Discount\n";
	
	// Start the looping - First iterate through the map - get every pair<int memberID, vector<PurchaseHistory>>
	for(auto colIt = historyCollection.begin(); colIt != historyCollection.end(); colIt++) {
		
		// Iterate through the vector<PurchaseHistory> for each PurchaseHistory
		for(auto vectIt = colIt->second.begin(); vectIt != colIt->second.end(); vectIt++) {
			file << "H," << colIt->first << "," << vectIt->getRawTime() << "," << vectIt->length() << "\n";
			
			// Iterate through the PurchaseHistory for each Order
			for(auto phIt = vectIt->begin(); phIt != vectIt->end(); phIt++) {
				// Order line
				file << "O," << phIt->getQuantity() << "," << phIt->getTotalCost() << ",0\n";
				// Product line
				Product temP = phIt->getProduct();
				float dAmt = 0.0;
				if(temP.getDiscount() != NULL)
					dAmt = temP.getDiscount()->getAmount();
				file << "P," << temP.getID() << "," << temP.getName() << "," << temP.getCategory() << "," << temP.getPrice() << "," << temP.getQuantity() << "," << dAmt << "\n";
			}
		}
	}
	
	file.close();
}

























