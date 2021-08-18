#ifndef PURCHASEHISTORY_H
#define PURCHASEHISTORY_H
#include "../Product/Product.h"
#include "../Login/Member.h"
#include "../ShoppingCart/Order.h"
#include <list>
#include <string>
#include <ctime>

class PurchaseHistory {
	private:
		int memberID;
		time_t rawDate;
		std::list<Order> history;
		
	public:
		PurchaseHistory();
		PurchaseHistory(std::list<Order> orders, Member member);
		PurchaseHistory(std::list<Order> orders, int memberid);
		PurchaseHistory(std::list<Order> orders, Member member, time_t date);
		PurchaseHistory(std::list<Order> orders, int memberid, time_t date);
		~PurchaseHistory();
		
		int getMemberID();
		time_t getRawTime();
		std::string getTime();
		void addOrder(Order order);
		void removeOrder(Order order);
		std::string printHistory();
		
		int length();
		bool isEmpty();
		std::list<Order>::iterator begin();
		std::list<Order>::iterator end();
};

#endif
