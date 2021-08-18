/*! \file Order.h
 *  \brief Keeps details about a particular member order.
 *  \details Class containing order information and metadata for a particular order from a member.
 *  \author Michael Schmittat
 */
#include "Order.h"

/**
 * Default constructor. Sets all values to zero initially.
 * @return None.
 */
Order::Order()
{
	this->dateOfPurchase = 0;
	this->quantity = 0;
	this->totalCost = 0;
}

/**
 * Default destructor.
 * @return None.
 */
Order::~Order()
{
}

/**
 * Constructor with arguments.
 * @param prod Product bought in the order.
 * @param pDate Date of purchase.
 * @param quant Quantity of product bought.
 * @return None.
 */
Order::Order(Product prod, int pDate, int quant)
{
	this->product = prod;
	this->dateOfPurchase = pDate;
	this->quantity = quant;

	updateCost();
}

/** Overrides == to compare product, quantity, and date
 * @return true iff product bought, quantity bought and date of purchase match, false if not.
 */
bool Order::operator==(const Order &other)
{
	return (product == (other.getProduct()) && this->quantity == other.getQuantity() && this->dateOfPurchase == other.getDate());
}

/** Overrides != to compare product, quantity, and date
 * @param other Other order to compare to.
 * @return true iff product bought, quantity bought and date of purchase do not match, false if not.
 */
bool Order::operator!=(const Order &other)
{
	return (!(product == (other.getProduct())) || !(this->quantity == other.getQuantity()) || !(this->dateOfPurchase == other.getDate()));
}

/** Overrides == to compare product, quantity, and date
 * @return true iff ANY of the above does not match with the other
 */
void Order::updateCost()
{
	float cost = this->product.getPrice();
	// If there is any discount stuff, calculate it here
	if (product.getDiscount() != NULL)
	{
		//std::cout << product->getDiscount()->getAmount() << "% Discount applied!" << std::endl;
		this->totalCost = cost * (1 - product.getDiscount()->getAmount()) * this->quantity;
	}
	else
		this->totalCost = cost * this->quantity;
}

/** Gets date of purchase of this order.
 *  @return This order's date of purchase.
 */
int Order::getDate() const
{
	return this->dateOfPurchase;
}

/** Gets quantity of product purchased from this order.
 *  @return An integer of this order's quantity purchases.
 */
int Order::getQuantity() const
{
	return this->quantity;
}

/** Gets this order's purchased product.
 *  @return Product from this order.
 */
Product Order::getProduct() const
{
	return product;
}

/** Gets total cost of this order.
 *  @return Float value of this order's cost.
 */
float Order::getTotalCost()
{
	return this->totalCost;
}

/** Sets an order's date of purchase.
 * @param newDate This order's date of purchase.
 * @return None.
 */
void Order::setDate(int newDate)
{
	this->dateOfPurchase = newDate;
}

/** Sets an order's product quantity.
 * @param amount Integer amount of product purchased.
 * @return None.
 */
void Order::setQuantity(int amount)
{
	this->quantity = amount;
}

/** Sets an order's total cost.
 * @param cost Float value of total cost of this order.
 * @return None.
 */
void Order::changeTotalCost(float cost)
{
	this->totalCost = cost;
}
