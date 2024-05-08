#include <string>
#include <vector>
#include "../include/Action.h"
#include "../include/WareHouse.h"

PrintOrderStatus::PrintOrderStatus(int id) : BaseAction(), orderId(id) {}

PrintOrderStatus::PrintOrderStatus(const PrintOrderStatus &other) : BaseAction(other), orderId(other.orderId) {}

void PrintOrderStatus::act(WareHouse &wareHouse)
{
    if (orderId < wareHouse.getOrderCounter())
    {
        wareHouse.printOrderStatus(orderId);
        this->BaseAction::complete();
    }
    else
        this->BaseAction::error("Order does not exist");
    wareHouse.addAction(this);
};

PrintOrderStatus *PrintOrderStatus::clone() const { return new PrintOrderStatus(*this); };

string PrintOrderStatus::toString() const
{
    string s = "PrintOrderStatus " + std::to_string(orderId) + " " + this->BaseAction::statusToString();
    return s;
}
