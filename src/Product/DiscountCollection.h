#ifndef DISCOUNT_COLLECTION_H
#define DISCOUNT_COLLECTION_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Discount.h"
#include "ProductCollection.h"

class DiscountCollection
{
private:
    std::unordered_map<std::string, Discount> discountCollection;

public:
    DiscountCollection();
    DiscountCollection(ProductCollection *pCollection);
    ~DiscountCollection();
    void addDiscount(Product *product, float discountAmount, int day, int month, int year);
    void removeDiscount(Product *product);
    void saveToDatabase();
};

#endif