#include "../include/Customer.h"
#include <string>
#include <vector>
#include <iostream>

Customer::Customer(int id, const string &name, int locationDistance, int maxOrders) : id(id), name(name), locationDistance(locationDistance), maxOrders(maxOrders), ordersId()
{
}

Customer::Customer(const Customer &other) : id(other.id), name(other.name), locationDistance(other.locationDistance), maxOrders(other.maxOrders), ordersId(other.ordersId)
{
}

const string &Customer::getName() const { return name; }
int Customer::getId() const { return id; }
int Customer::getCustomerDistance() const { return locationDistance; }
int Customer::getMaxOrders() const { return maxOrders; }
int Customer::getNumOrders() const { return ordersId.size(); }
bool Customer::canMakeOrder() const
{
    if (ordersId.size() == static_cast<std::vector<int>::size_type>(maxOrders))
        return false;
    return true;
}
const vector<int> &Customer::getOrdersIds() const { return ordersId; }
int Customer::addOrder(int orderId) // return OrderId if order was added successfully, -1 otherwise
{
    if (this->canMakeOrder())
    {
        ordersId.push_back(orderId);
        return orderId;
    }
    return -1;
}

string Customer::toString() const
{
    string s = " id:" + std::to_string(id) + " name:" + name + " distance:" + std::to_string(locationDistance) + " max orders:" + std::to_string(maxOrders);
    return s;
}

Customer::~Customer()
{
}
