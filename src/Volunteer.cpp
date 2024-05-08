#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <string>
#include <vector>

Volunteer::Volunteer(int id, const string &name) : completedOrderId(NO_ORDER), activeOrderId(NO_ORDER), id(id), name(name)
{
}

Volunteer::Volunteer(const Volunteer &other) : completedOrderId(NO_ORDER), activeOrderId(NO_ORDER), id(other.id), name(other.name) {}

int Volunteer::getId() const
{
    return id;
}

const string &Volunteer::getName() const { return name; }

int Volunteer::getActiveOrderId() const { return activeOrderId; }

int Volunteer::getCompletedOrderId() const { return completedOrderId; }

void Volunteer::finishCompletedOrder() { completedOrderId = NO_ORDER; }

bool Volunteer::isBusy() const
{
    if (activeOrderId != NO_ORDER)
        return true;
    return false;
}

string Volunteer::toString() const
{
    string s = "VoluteerId:" + std::to_string(id);
    if (isBusy())
        s = s + "\nisBusy: True" + "\nOrderId: " + std::to_string(activeOrderId);
    else
        s = s + "\nisBusy: False" + "\nOrderId: None";
    return s;
}

Volunteer::~Volunteer() {}
