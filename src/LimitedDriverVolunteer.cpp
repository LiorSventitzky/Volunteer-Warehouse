#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <string>
#include <vector>

LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep, int maxOrders) : DriverVolunteer(id, name, maxDistance, distancePerStep), maxOrders(maxOrders), ordersLeft(maxOrders){};

LimitedDriverVolunteer::LimitedDriverVolunteer(const LimitedDriverVolunteer &other) : DriverVolunteer(other), maxOrders(other.maxOrders), ordersLeft(other.ordersLeft){};

LimitedDriverVolunteer *LimitedDriverVolunteer::clone() const
{
    return new LimitedDriverVolunteer(*this);
}
int LimitedDriverVolunteer::getMaxOrders() const { return maxOrders; }
int LimitedDriverVolunteer::getNumOrdersLeft() const { return ordersLeft; }
bool LimitedDriverVolunteer::hasOrdersLeft() const { return (ordersLeft > 0); }
bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const
{
    return DriverVolunteer::canTakeOrder(order) && hasOrdersLeft();
}

void LimitedDriverVolunteer::acceptOrder(const Order &order) // Assign distanceLeft to order's distance and decrease ordersLeft
{
    if (canTakeOrder(order))
    {
        this->DriverVolunteer::acceptOrder(order);
        ordersLeft--;
    }
}
string LimitedDriverVolunteer::toString() const
{
    string s = Volunteer::toString();
    if (isBusy())
        s = s + "\nDistanceLeft: " + std::to_string(this->getDistanceLeft());
    else
        s = s + "\nDistanceLeft: None";
    s = s + "\nOrdersLeft: " + std::to_string(ordersLeft);
    return s;
}
