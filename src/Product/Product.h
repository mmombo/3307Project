/* COMPSCI-3307 Group Assignment | Alex Broekhuyse | abroekhu@uwo.ca | 250978523 */
/** @author Alex Broekhuyse
 */
#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <iostream>
#include "Discount.h"

class Product
{
private:
    std::string id;
    std::string productName;
    std::string category;
    float price;
    int quantity;

    float bulkModifier;
    Discount *discount;

public:
    Product();

    Product(std::string productName, std::string category, std::string id, float price, int quantity, float bulkModifier);
    Product(std::string productName, std::string category, std::string id, float price, int quantity);

    ~Product();

    std::string getID() const;
    std::string getName();
    std::string getCategory();
    Discount *getDiscount();
    float getPrice();
    int getQuantity();
    void setID(std::string id);
    void setName(std::string productName);
    void setCategory(std::string category);
    void setPrice(float price);
    void setQuantity(int quantity);
    void setDiscount(Discount *new_discount);

    void addQuantity(int quantity);
    bool operator==(const Product &other);
    friend std::ostream &operator<<(std::ostream &os, const Product &prod);
};

#endif
