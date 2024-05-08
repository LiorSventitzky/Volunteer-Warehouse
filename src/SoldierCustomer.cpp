#include "../include/Customer.h"
#include <string>
#include <vector>

SoldierCustomer::SoldierCustomer(int id, const string &name, int locationDistance, int maxOrders) : Customer(id, name, locationDistance, maxOrders) {}

SoldierCustomer::SoldierCustomer(const SoldierCustomer &other) : Customer(other) {}

SoldierCustomer *SoldierCustomer::clone() const
{
    return new SoldierCustomer(*this);
}

string SoldierCustomer:: toString() const{
    string s= Customer::toString() + " type:solider";
    return s; 
}
