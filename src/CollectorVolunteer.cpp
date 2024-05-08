#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

CollectorVolunteer::CollectorVolunteer(int id, const string &name, int coolDown) : Volunteer(id, name), coolDown(coolDown), timeLeft(NO_ORDER)
{
}

CollectorVolunteer::CollectorVolunteer(const CollectorVolunteer &other) : Volunteer(other), coolDown(other.coolDown), timeLeft(other.timeLeft) {}

CollectorVolunteer *CollectorVolunteer::clone() const { return new CollectorVolunteer(*this); }

void CollectorVolunteer::step() // Simulate volunteer step,if the volunteer finished the order, transfer activeOrderId to completedOrderId
{
    if (decreaseCoolDown())
    {
        timeLeft = NO_ORDER;
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;
    }
}

int CollectorVolunteer::getCoolDown() const { return coolDown; }

int CollectorVolunteer::getTimeLeft() const { return timeLeft; }

bool CollectorVolunteer::decreaseCoolDown() // Decrease timeLeft by 1,return true if timeLeft=0,false otherwise
{
    timeLeft--;
    return (timeLeft == 0);
}

bool CollectorVolunteer::hasOrdersLeft() const { return true; }
bool CollectorVolunteer::canTakeOrder(const Order &order) const { return !isBusy(); }

void CollectorVolunteer::acceptOrder(const Order &order)
{
    if (canTakeOrder(order))
    {
        activeOrderId = order.getId();
        timeLeft = coolDown;
    }
}

string CollectorVolunteer::toString() const
{
    string s = Volunteer::toString();
    if (isBusy())
        s = s + "\nTimeLeft: " + std::to_string(timeLeft);
    else
        s = s + "\nTimeLeft: None";
    s = s + "\nOrdersLeft: No Limit";
    return s;
}
