#ifndef PURCHASE_HISTORY_COLLECTION_H
#define PURCHASE_HISTORY_COLLECTION_H

#include <vector>
#include <unordered_map>
#include <ctime>
#include "PurchaseHistory.h"

class PurchaseHistoryCollection
{
	private: 
		std::unordered_map<int, std::vector<PurchaseHistory>> historyCollection;
		
	public:
		PurchaseHistoryCollection();
		~PurchaseHistoryCollection();
		
		PurchaseHistory getPurchaseHistory(int memberID, time_t date);
		std::vector<PurchaseHistory> getHistoriesByID(int memberID);
		std::vector<PurchaseHistory> getMemberHistoriesBefore(int memberID, time_t date);
		std::vector<PurchaseHistory> getMemberHistoriesAfter(int memberID, time_t date);
		std::vector<PurchaseHistory> getMemberHistoriesWithinDay(int memberID, time_t date);
		std::vector<PurchaseHistory> getAllHistoriesBefore(time_t date);
		std::vector<PurchaseHistory> getAllHistoriesAfter(time_t date);
		std::vector<PurchaseHistory> getAllHistoriesWithinDay(time_t date);
		
		void addPurchaseHistory(PurchaseHistory history);
		int deletePurchaseHistory(int memberID, time_t date);
		int deleteAllHistoriesByMember(int memberID);
		
		void saveToDatabase();
};

#endif
