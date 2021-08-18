#ifndef ADMININTERFACE_H
#define ADMININTERFACE_H

#include "../Product/Product.h"
#include "../Product/ProductCollection.h"
#include "../Product/DiscountCollection.h"

class AdminInterface
{
private:
	ProductCollection* pCollection;
	DiscountCollection* dCollection;

public:

	AdminInterface(ProductCollection& productCollection, DiscountCollection& discountCollection);
	~AdminInterface();
	void ProductDisplay();
	void AdminProductPrompt();
	void AdminDiscountPrompt();

};
#endif