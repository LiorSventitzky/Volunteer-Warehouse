#pragma once
#include <string>
#include <vector>
#include <sstream>

#include "Order.h"
#include "Customer.h"
#include "Volunteer.h"
#include "Action.h"

#ifndef WareHouse_H_
#define WareHouse_H_

class Action;
class Volunteer;

using namespace std;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.

class WareHouse
{

public:
    WareHouse(const string &configFilePath);
    WareHouse(const WareHouse &other);
    WareHouse(WareHouse &&other);
    WareHouse &operator=(const WareHouse &other);
    WareHouse &operator=(WareHouse &&other);
    ~WareHouse();
    void start();
    void addOrder(Order *order);
    void addAction(BaseAction *action);
    Customer &getCustomer(int customerId) const;
    Volunteer &getVolunteer(int volunteerId) const;
    Order &getOrder(int orderId) const;
    const vector<BaseAction *> &getActions() const;
    void close();
    void open();
    void SimulateStepInWarehouse();
    int getOrderCounter();
    int getCustomerCounter();
    void printOrderStatus(int orderId);
    void printCustomerStatus(int customerId);
    int doesVolunteerExist(int volunteerId);
    void printVolunteerStatus(int index);
    void addCustomer(Customer *customer);
    void createBackUp();
    void restoreWarehouse();
    void deleteVectors();

private:
    bool isOpen;
    vector<BaseAction *> actionsLog;
    vector<Volunteer *> volunteers;
    vector<Order *> pendingOrders;
    vector<Order *> inProcessOrders;
    vector<Order *> completedOrders;
    vector<Customer *> customers;
    int customerCounter;  // For assigning unique customer IDs
    int volunteerCounter; // For assigning unique volunteer IDs
    int orderCounter;     // For assigning unique order IDs
    void ParseConFile(const string &configFilePath);
    void addCustomer(stringstream *temp);
    void addVolunteer(stringstream *temp);
    bool findAvailableCollector(Order &order, int index);
    bool findAvailableDriver(Order &order, int index);
};

#endif
