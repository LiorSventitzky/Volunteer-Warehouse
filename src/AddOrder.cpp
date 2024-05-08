#include "../include/Action.h"
#include "../include/Volunteer.h"
#include "../include/Order.h"
#include "../include/WareHouse.h"
#include "../include/Customer.h"
#include <string>
#include <vector>

AddOrder::AddOrder(int id) : BaseAction(), customerId(id) {}

AddOrder::AddOrder(const AddOrder &other) : BaseAction(other), customerId(other.customerId) {}

void AddOrder::act(WareHouse &wareHouse)
{
    if (wareHouse.getCustomerCounter() > customerId) // check if this customer exists
    {
        Customer &c = wareHouse.getCustomer(customerId);
        if (c.addOrder(wareHouse.getOrderCounter()) != -1) // if it returns -1 it means he can't take the order
        {
            Order *order = new Order(wareHouse.getOrderCounter(), c.getId(), c.getCustomerDistance());
            wareHouse.addOrder(order);
            BaseAction::complete();
        }
        else
        {
            this->BaseAction::error("Cannot place this order");
        }
    }
    else
    {
        this->BaseAction::error("Cannot place this order");
    }
    wareHouse.addAction(this);
}

string AddOrder::toString() const
{
    string s = "order " + std::to_string(customerId) + " " + this->BaseAction::statusToString();
    return s;
}

AddOrder *AddOrder::clone() const { return new AddOrder(*this); }
