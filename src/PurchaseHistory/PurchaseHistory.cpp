/** \file PurchaseHistory.h
 * \brief Functionality for purchase histories.
 * \details Creates a purchase history for a particular member. Also provides functionality for purchase history to be displayed in the application.
 * \author Michael Schmittat
 */

#include <sstream>
#include "PurchaseHistory.h"

/** Class constructor. Constructor that sets the member ID to 0 and gets default time of purchase.
 * @return None.
 */
PurchaseHistory::PurchaseHistory() {
	memberID = 0;
	time(&rawDate);
}

/** Class constructor. Constructor that sets the member ID to 0 and gets default time of purchase.
 * @return None.
 */
PurchaseHistory::PurchaseHistory(std::list<Order> orders, Member member) {
	memberID = member.getID();
	history = orders;
	time(&rawDate);
} 

/** Class constructor with parameters. Constructor that sets the member's purchase history and their orders.
 * @param orders Vector list of orders the member has made.
 * @param memberid Unique member ID to attach a purchase history to.
 * @return None.
 */
PurchaseHistory::PurchaseHistory(std::list<Order> orders, int memberid) {
	memberID = memberid;
	history = orders;
	time(&rawDate);
}

/** Class constructor with parameters. Constructor that sets the member's purchase history and their orders, including time of the order.
 * @param orders Vector list of orders the member has made.
 * @param member Member object to attach a purchase history to.
 * @param date Date of the purchase history
 * @return None.
 */
PurchaseHistory::PurchaseHistory(std::list<Order> orders, Member member, time_t date) {
	memberID = member.getID();
	rawDate = date;
	history = orders;
} 

/** Class constructor with parameters. Constructor that sets the member's purchase history and their orders, including time of the order.
 * @param orders Vector list of orders the member has made.
 * @param member Member object to attach a purchase history to.
 * @param date Date of the purchase history
 * @return None.
 */
PurchaseHistory::PurchaseHistory(std::list<Order> orders, int memberid, time_t date) {
	memberID = memberid;
	rawDate = date;
	history = orders;
}

/** Class destructor.
 * @return None.
 */
PurchaseHistory::~PurchaseHistory() {}

/** Gets unique member ID associated with this purchase history.
 * @return An integer value of the unique member ID associated with this purchase history.
 */
int PurchaseHistory::getMemberID() {
	return memberID;
}

/** Gets the date associated with this purchase history.
 * @return A timestamp of the date associated with this purchase history.
 */
time_t PurchaseHistory::getRawTime() {
	return rawDate;
}

/** Gets the time associated with this purchase history.
 * @return A timestamp in string format associated with this purchase history.
 */
std::string PurchaseHistory::getTime() {
	struct tm* timeInfo;
	timeInfo = localtime(&rawDate);
	// Converts cstring to std::string
	return std::string(asctime(timeInfo));
}

/** Adds an order to this purchase history.
 * @param order Order to be added to this purchase history.
 * @return None.
 */
void PurchaseHistory::addOrder(Order order) {
	for(std::list<Order>::iterator i = history.begin(); i != history.end(); ++i) {
		if(order.getProduct() == i->getProduct()) {
			i->setQuantity(i->getQuantity() + order.getQuantity());
			i->changeTotalCost(i->getTotalCost() + order.getTotalCost());
			return;
		}
	}
	history.push_back(order);
}

/** Removes an order to this purchase history.
 * @param order Order to be removed from this purchase history.
 * @return None.
 */
void PurchaseHistory::removeOrder(Order order) {
	history.remove(order);
}

/** Provides a transcription of the contained Orders.
* @return string representation of the Orders inside the PurchaseHistory list.
*/
std::string PurchaseHistory::printHistory() {
	std::ostringstream output;
	for(std::list<Order>::iterator i = history.begin(); i != history.end(); ++i) {
		output << "Product: " << i->getProduct().getName() << ", Amount: " << (i->getQuantity()) << ", Total Cost: $" << (i->getTotalCost()) << "\n";
	}
	
	return output.str();
}

/** Gets the amount of orders in this purchase history.
 * @return An integer amount of orders in this purchase history.
 */
int PurchaseHistory::length() {
	return history.size();
}

/** Checks if this purchase history is empty
 * @return True if this purchase history is empty. False if this purchase history has at least one entry.
 */
bool PurchaseHistory::isEmpty() {
	return history.empty();
}

/**
* Returns an iterator that can be used to traverse the PurchaseHistory. Iterator starts and the begining of the list.
* @return list<Order>::iterator to the start of the PurchaseHistory list.
*/
std::list<Order>::iterator PurchaseHistory::begin() {
	return history.begin();
}

/**
* Returns an iterator that can be used to traverse the PurchaseHistory. Iterator starts and the end of the list.
* @return list<Order>::iterator to the end of the PurchaseHistory list.
*/
std::list<Order>::iterator PurchaseHistory::end() {
	return history.end();
}
