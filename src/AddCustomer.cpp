#include "../include/Action.h"
#include "../include/Volunteer.h"
#include "../include/Order.h"
#include "../include/WareHouse.h"
#include "../include/Customer.h"
#include <string>
#include <vector>

AddCustomer::AddCustomer(const string &customerName, const string &customerType, int distance, int maxOrders) : BaseAction(), customerName(customerName), customerType((customerType == "soldier") ? CustomerType::Soldier : CustomerType::Civilian), distance(distance), maxOrders(maxOrders)
{
}

AddCustomer::AddCustomer(const AddCustomer &other) : BaseAction(other), customerName(other.customerName), customerType(other.customerType), distance(other.distance), maxOrders(other.maxOrders) {}

void AddCustomer::act(WareHouse &wareHouse)
{
    if (customerType == CustomerType::Soldier)
        wareHouse.addCustomer(new SoldierCustomer(wareHouse.getCustomerCounter(), customerName, distance, maxOrders));
    else
        wareHouse.addCustomer(new CivilianCustomer(wareHouse.getCustomerCounter(), customerName, distance, maxOrders));
    BaseAction::complete();
    wareHouse.addAction(this);
}

AddCustomer *AddCustomer::clone() const { return new AddCustomer(*this); }

string AddCustomer::typeToString() const
{
    if (customerType == CustomerType::Soldier)
        return "solider";
    else
        return "civilian";
}

string AddCustomer::toString() const
{
    string s = "customer " + customerName + " " + this->typeToString() + " " + std::to_string(distance) + " " + std::to_string(maxOrders) + " " + this->BaseAction::statusToString();
    return s;
}
