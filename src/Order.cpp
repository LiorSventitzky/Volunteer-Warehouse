#include "../include/Customer.h"
#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <string>
#include <vector>

Order::Order(int id, int customerId, int distance) : id(id), customerId(customerId), distance(distance), status(OrderStatus::PENDING), collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER) {}
Order::Order(Order &other) : id(other.id), customerId(other.customerId), distance(other.distance), status(other.status), collectorId(other.collectorId), driverId(other.driverId) {}
int Order::getId() const { return id; }
int Order::getCustomerId() const { return customerId; }
int Order::getDistance() const { return distance; }
void Order::setStatus(OrderStatus status) { this->status = status; }
void Order::setCollectorId(int collectorId) { this->collectorId = collectorId; }
void Order::setDriverId(int driverId) { this->driverId = driverId; }
int Order::getCollectorId() const { return collectorId; }
int Order::getDriverId() const { return driverId; }
OrderStatus Order::getStatus() const { return status; }
const string Order::toString() const
{
    string stat = statusToString();
    string cId = std::to_string(collectorId);
    string dId = std::to_string(driverId);
    if (cId == "-1")
        cId = "None";
    if (dId == "-1")
        dId = "None";
    string s = "OrderId: " + std::to_string(id) + "\nOrderStatus: " + stat + "\nCustomerID: " + std::to_string(customerId) + "\nCollectorId: " + cId + "\nDriverId: " + dId;
    return s;
}
const string Order::shortenedToString() const
{
    string stat = statusToString();
    return "OrderId: " + std::to_string(id) + "\nOrderStatus: " + stat + "\n";
}

const string Order::toStringForClose() const
{
    string stat = statusToString();
    return "OrderId: " + std::to_string(id) + " CustomerId: " + std::to_string(customerId) + " OrderStatus: " + stat;
}

Order *Order::clone()
{
    return new Order(*this);
}

string Order::statusToString() const
{
    if (status == OrderStatus::PENDING)
        return "PENDING";
    else if (status == OrderStatus::COLLECTING)
        return "COLLECTING";
    else if (status == OrderStatus::DELIVERING)
        return "DELIVERING";
    else if (status == OrderStatus::COMPLETED)
        return "COMPLETED";
    else
        return "UNKNOWN";
}
