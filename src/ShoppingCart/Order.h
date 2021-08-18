#ifndef ORDER_H
#define ORDER_H

#include "../Product/Product.h"

class Order {
	private:
		Product product;
		int dateOfPurchase;	
		int quantity;
		float totalCost;
		
	public:
		Order();
		~Order();
		Order(Product prod, int pDate, int quant);
		
		bool operator == (const Order& other);
		bool operator != (const Order& other);
		
		int getDate() const;
		int getQuantity() const;
		Product getProduct() const;
		float getTotalCost();
		
		void updateCost();
		void setDate(int newDate);
		void setQuantity(int amount);
		void changeTotalCost(float cost);
		
		
};

#endif
