#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <string>
#include <vector>

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, const string &name, int coolDown, int maxOrders) : CollectorVolunteer(id, name, coolDown), maxOrders(maxOrders), ordersLeft(maxOrders) {}

LimitedCollectorVolunteer::LimitedCollectorVolunteer(const LimitedCollectorVolunteer &other) : CollectorVolunteer(other), maxOrders(other.maxOrders), ordersLeft(other.ordersLeft) {}

LimitedCollectorVolunteer *LimitedCollectorVolunteer::clone() const
{
    return new LimitedCollectorVolunteer(*this);
}

bool LimitedCollectorVolunteer::hasOrdersLeft() const { return (ordersLeft > 0); }
bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const { return !isBusy() && hasOrdersLeft(); }
void LimitedCollectorVolunteer::acceptOrder(const Order &order)
{
    if (canTakeOrder(order))
    {
        this->CollectorVolunteer::acceptOrder(order);
        ordersLeft--;
    }
}

int LimitedCollectorVolunteer::getMaxOrders() const { return maxOrders; }
int LimitedCollectorVolunteer::getNumOrdersLeft() const { return ordersLeft; }

string LimitedCollectorVolunteer::toString() const
{
    string s = Volunteer::toString();
    if (isBusy())
        s = s + "\nTimeLeft: " + std::to_string(this->getTimeLeft());
    else
        s = s + "\nTimeLeft: None";
    s = s + "\nOrdersLeft: " + std::to_string(ordersLeft);
    return s;
}
