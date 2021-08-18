/** \file Discount.h
 */
#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <string>
#include <iostream>
#include <ctime>

class Discount
{
private:
    float amount;
    std::string productID;
    tm endDate;

public:
    Discount();
    Discount(std::string product, float amount, int day, int month, int year);
    ~Discount();
    std::string getProductID();
    float getAmount();
    bool checkDate();
};

#endif
