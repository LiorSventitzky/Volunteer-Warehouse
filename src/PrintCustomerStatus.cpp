#include <string>
#include <vector>
#include "../include/Action.h"
#include "../include/WareHouse.h"

PrintCustomerStatus::PrintCustomerStatus(int customerId) : BaseAction(), customerId(customerId) {}
PrintCustomerStatus::PrintCustomerStatus(const PrintCustomerStatus &other) : BaseAction(other), customerId(other.customerId) {}
void PrintCustomerStatus::act(WareHouse &wareHouse)
{
    if (wareHouse.getCustomerCounter() > customerId)
    {
        wareHouse.printCustomerStatus(customerId);
        this->BaseAction::complete();
    }
    else
    {
        this->BaseAction::error("Customer doesn't exist");
    }
    wareHouse.addAction(this);
}

PrintCustomerStatus *PrintCustomerStatus::clone() const { return new PrintCustomerStatus(*this); }
string PrintCustomerStatus::toString() const
{
    return "PrintCustomerStatus " + std::to_string(customerId) + " " + this->BaseAction::statusToString();
}
