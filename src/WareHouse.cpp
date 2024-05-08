
#include "../include/WareHouse.h"
#include "../include/Customer.h"
#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <typeinfo>

using namespace std;

extern WareHouse *backup;

WareHouse::WareHouse(const string &configFilePath) : isOpen(false), actionsLog(), volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), customers(), customerCounter(0), volunteerCounter(0), orderCounter(0)
{
    ParseConFile(configFilePath); // at the bottom of the file
}

WareHouse::WareHouse(const WareHouse &other) : isOpen(other.isOpen), actionsLog(), volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), customers(), customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter), orderCounter(other.orderCounter)
{
    for (std::vector<Customer *>::size_type i = 0; i < other.customers.size(); i++)
    {
        customers.push_back(other.customers[i]->clone());
    }
    for (std::vector<Volunteer *>::size_type i = 0; i < other.volunteers.size(); i++)
    {
        volunteers.push_back(other.volunteers[i]->clone());
    }
    for (std::vector<Order *>::size_type i = 0; i < other.pendingOrders.size(); i++)
    {
        pendingOrders.push_back(other.pendingOrders[i]->clone());
    }
    for (std::vector<Order *>::size_type i = 0; i < other.inProcessOrders.size(); i++)
    {
        inProcessOrders.push_back(other.inProcessOrders[i]->clone());
    }
    for (std::vector<Order *>::size_type i = 0; i < other.completedOrders.size(); i++)
    {
        completedOrders.push_back(other.completedOrders[i]->clone());
    }
    for (std::vector<BaseAction *>::size_type i = 0; i < other.actionsLog.size(); i++)
    {
        actionsLog.push_back(other.actionsLog[i]->clone());
    }
}

WareHouse::WareHouse(WareHouse &&other) : isOpen(other.isOpen), actionsLog(), volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), customers(), customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter), orderCounter(other.orderCounter)
{
    for (std::vector<Customer *>::size_type i = 0; i < other.customers.size(); i++)
    {
        customers.push_back(other.customers[i]);
        other.customers[i] = nullptr;
    }
    for (std::vector<Volunteer *>::size_type i = 0; i < other.volunteers.size(); i++)
    {
        volunteers.push_back(other.volunteers[i]);
        other.volunteers[i] = nullptr;
    }
    for (std::vector<Order *>::size_type i = 0; i < other.pendingOrders.size(); i++)
    {
        pendingOrders.push_back(other.pendingOrders[i]);
        pendingOrders[i] = nullptr;
    }
    for (std::vector<Order *>::size_type i = 0; i < other.inProcessOrders.size(); i++)
    {
        inProcessOrders.push_back(other.inProcessOrders[i]);
        inProcessOrders[i] = nullptr;
    }
    for (std::vector<Order *>::size_type i = 0; i < other.completedOrders.size(); i++)
    {
        completedOrders.push_back(other.completedOrders[i]);
        other.completedOrders[i] = nullptr;
    }
    for (std::vector<BaseAction *>::size_type i = 0; i < other.actionsLog.size(); i++)
    {
        actionsLog.push_back(other.actionsLog[i]);
        other.actionsLog[i] = nullptr;
    }
}

WareHouse &WareHouse::operator=(const WareHouse &other)
{
    if (&other != this)
    {
        deleteVectors(); // at the bottom of the file (deep delete to all vectors)
        this->isOpen = other.isOpen;
        this->customerCounter = other.customerCounter;
        this->volunteerCounter = other.volunteerCounter;
        this->orderCounter = other.orderCounter;
        for (std::vector<Customer *>::size_type i = 0; i < other.customers.size(); i++)
        {
            customers.push_back((*other.customers[i]).clone());
        }
        for (std::vector<Volunteer *>::size_type i = 0; i < other.volunteers.size(); i++)
        {
            volunteers.push_back((*other.volunteers[i]).clone());
        }
        for (std::vector<Order *>::size_type i = 0; i < other.pendingOrders.size(); i++)
        {
            pendingOrders.push_back((*other.pendingOrders[i]).clone());
        }
        for (std::vector<Order *>::size_type i = 0; i < other.inProcessOrders.size(); i++)
        {
            inProcessOrders.push_back((*other.inProcessOrders[i]).clone());
        }
        for (std::vector<Order *>::size_type i = 0; i < other.completedOrders.size(); i++)
        {

            completedOrders.push_back((*other.completedOrders[i]).clone());
        }
        for (std::vector<Action *>::size_type i = 0; i < other.actionsLog.size(); i++)
        {
            actionsLog.push_back((*other.actionsLog[i]).clone());
        }
    }
    return *this;
}

WareHouse &WareHouse::operator=(WareHouse &&other)
{
    if (&other != this)
    {
        deleteVectors();
        this->isOpen = other.isOpen;
        this->customerCounter = other.customerCounter;
        this->volunteerCounter = other.volunteerCounter;
        this->orderCounter = other.orderCounter;
        for (std::vector<Customer *>::size_type i = 0; i < other.customers.size(); i++)
        {
            customers.push_back(other.customers[i]);
            other.customers[i] = nullptr;
        }
        for (std::vector<Volunteer *>::size_type i = 0; i < other.volunteers.size(); i++)
        {
            volunteers.push_back(other.volunteers[i]);
            other.volunteers[i] = nullptr;
        }
        for (std::vector<Order *>::size_type i = 0; i < other.pendingOrders.size(); i++)
        {
            pendingOrders.push_back(other.pendingOrders[i]);
            other.pendingOrders[i] = nullptr;
        }
        for (std::vector<Order *>::size_type i = 0; i < other.inProcessOrders.size(); i++)
        {
            inProcessOrders.push_back(other.inProcessOrders[i]);
            other.inProcessOrders[i] = nullptr;
        }
        for (std::vector<Order *>::size_type i = 0; i < other.completedOrders.size(); i++)
        {
            completedOrders.push_back(other.completedOrders[i]);
            other.completedOrders[i] = nullptr;
        }
        for (std::vector<Action *>::size_type i = 0; i < other.actionsLog.size(); i++)
        {
            actionsLog.push_back(other.actionsLog[i]);
            other.actionsLog[i] = nullptr;
        }
    }
    return *this;
}

WareHouse::~WareHouse()
{
    deleteVectors();
}

void WareHouse::addCustomer(Customer *customer)
{
    customers.push_back(customer);
    customerCounter++;
}

void WareHouse::addOrder(Order *order)
{
    pendingOrders.push_back(order);
    orderCounter++;
}

Customer &WareHouse::getCustomer(int customerId) const
{
    for (std::vector<Customer *>::size_type i = 0; i < customers.size(); i++)
    {
        if (customers[i]->getId() == customerId)
            return *customers[i];
    }
    Customer *c = new SoldierCustomer(-1, "NULL", -1, -1);
    return *c;
}

Volunteer &WareHouse::getVolunteer(int volunteerId) const
{
    for (std::vector<Volunteer *>::size_type i = 0; i < volunteers.size(); i++)
    {
        if (volunteers[i]->getId() == volunteerId)
            return *volunteers[i];
    }
    Volunteer *v = new CollectorVolunteer(-1, "NULL", -1);
    return *v;
}

Order &WareHouse::getOrder(int orderId) const
{
    for (std::vector<Order *>::size_type i = 0; i < pendingOrders.size(); i++)
    {
        if (pendingOrders[i]->getId() == orderId)
            return *pendingOrders[i];
    }
    for (std::vector<Order *>::size_type i = 0; i < inProcessOrders.size(); i++)
    {
        if (inProcessOrders[i]->getId() == orderId)
            return *inProcessOrders[i];
    }
    for (std::vector<Order *>::size_type i = 0; i < completedOrders.size(); i++)
    {
        if (completedOrders[i]->getId() == orderId)
            return *completedOrders[i];
    }
    Order *o = new Order(-1, -1, -1);
    return *o;
}

void WareHouse::SimulateStepInWarehouse()
{
    // phase 1 of the scheme
    for (std::vector<Order *>::size_type i = 0; i < pendingOrders.size(); i++)
    {
        if ((*pendingOrders[i]).getStatus() == OrderStatus::PENDING)
        {
            if (findAvailableCollector(*pendingOrders[i], i)) // findAvailableCollector under this function
                i--;
        }
        else
        {
            if (findAvailableDriver(*pendingOrders[i], i)) // findAvailableDriver under this function
                i--;
        }
    }

    // phase 2+3+4 of the scheme
    for (std::vector<Order *>::size_type i = 0; i < volunteers.size(); i++)
    {
        // 2
        if (volunteers[i]->isBusy())
        {
            volunteers[i]->step();
        }
        // 3
        if (volunteers[i]->getCompletedOrderId() != NO_ORDER)
        {
            for (std::vector<Order *>::size_type j = 0; j < inProcessOrders.size(); j++)
            {
                if (inProcessOrders[j]->getId() == volunteers[i]->getCompletedOrderId()) // search the completed order
                {
                    if (inProcessOrders[j]->getStatus() == OrderStatus::COLLECTING)
                    {
                        pendingOrders.push_back(inProcessOrders[j]);
                        inProcessOrders.erase(inProcessOrders.begin() + j);
                    }
                    else
                    {
                        inProcessOrders[j]->setStatus(OrderStatus::COMPLETED);
                        completedOrders.push_back(inProcessOrders[j]);
                        inProcessOrders.erase(inProcessOrders.begin() + j);
                    }
                    j = inProcessOrders.size();
                }
            }
            volunteers[i]->finishCompletedOrder();
        }

        // 4
        if ((!volunteers[i]->isBusy()) && !volunteers[i]->hasOrdersLeft())
        {
            delete volunteers[i];
            volunteers.erase(volunteers.begin() + i);
            i--;
        }
    }
}

bool WareHouse::findAvailableCollector(Order &order, int index)
{
    int size = volunteers.size();
    for (auto i = 0; i < size; i++)
    {
        if (typeid(*volunteers[i]) == typeid(CollectorVolunteer) || typeid(*volunteers[i]) == typeid(LimitedCollectorVolunteer))
        {
            if ((*volunteers[i]).canTakeOrder(order))
            {
                (*volunteers[i]).acceptOrder(order);
                order.setCollectorId((*volunteers[i]).getId());
                order.setStatus(OrderStatus::COLLECTING);
                inProcessOrders.push_back(&order);
                pendingOrders.erase(pendingOrders.begin() + index);
                return true;
            }
        }
    }
    return false;
}

bool WareHouse::findAvailableDriver(Order &order, int index)
{
    for (std::vector<Volunteer *>::size_type i = 0; i < volunteers.size(); i++)
    {
        if (typeid(*volunteers[i]) == typeid(DriverVolunteer) || typeid(*volunteers[i]) == typeid(LimitedDriverVolunteer))
        {
            if ((*volunteers[i]).canTakeOrder(order))
            {
                (*volunteers[i]).acceptOrder(order);
                order.setDriverId((*volunteers[i]).getId());
                order.setStatus(OrderStatus::DELIVERING);
                inProcessOrders.push_back(&order);
                pendingOrders.erase(pendingOrders.begin() + index);
                return true;
            }
        }
    }
    return false;
}

void WareHouse::addAction(BaseAction *action) { actionsLog.push_back(action); }

const vector<BaseAction *> &WareHouse::getActions() const { return actionsLog; }

int WareHouse::getOrderCounter() { return orderCounter; }

int WareHouse::getCustomerCounter() { return customerCounter; }

void WareHouse::printOrderStatus(int orderId)
{
    bool found = false;
    for (std::vector<Order *>::size_type i = 0; i < pendingOrders.size() && !found; i++)
    {
        if (pendingOrders[i]->getId() == orderId)
        {
            cout << pendingOrders[i]->toString() + "\n";
            found = true;
        }
    }
    for (std::vector<Order *>::size_type i = 0; i < inProcessOrders.size() && !found; i++)
    {
        if (inProcessOrders[i]->getId() == orderId)
        {
            cout << inProcessOrders[i]->toString() + "\n";
            found = true;
        }
    }
    for (std::vector<Order *>::size_type i = 0; i < completedOrders.size() && !found; i++)
    {
        if (completedOrders[i]->getId() == orderId)
        {
            cout << completedOrders[i]->toString() + "\n";
            found = true;
        }
    }
}

void WareHouse::printCustomerStatus(int customerId)
{
    cout << "CustomerId: " + std::to_string(customerId) + "\n";
    Customer &c = getCustomer(customerId);
    vector<int> ordersId = c.getOrdersIds();
    for (std::vector<Order *>::size_type i = 0; i < ordersId.size(); i++)
    {
        Order &order = getOrder(ordersId[i]);
        cout << order.shortenedToString();
    }
    cout << "numOrdersLeft:" + std::to_string(c.getMaxOrders() - c.getNumOrders()) + "\n";
}

int WareHouse::doesVolunteerExist(int volunteerId)
{
    for (std::vector<Volunteer *>::size_type i = 0; i < volunteers.size(); i++)
    {
        if (volunteers[i]->getId() == volunteerId)
            return i;
    }
    return -1;
}

void WareHouse::printVolunteerStatus(int index)
{
    std::cout << volunteers[index]->toString() << std::endl;
}

void WareHouse::start()
{
    open();
    while (isOpen)
    {
        string action, word, num;
        std::getline(std::cin, action);
        stringstream temp(action);
        temp >> word;
        if (word == "step")
        {
            temp >> num;
            int numOfSteps = std::stoi(num);
            SimulateStep *s = new SimulateStep(numOfSteps);
            s->act(*this);
        }
        if (word == "order")
        {
            temp >> num;
            int customerId = std::stoi(num);
            AddOrder *a = new AddOrder(customerId);
            a->act(*this);
        }
        if (word == "customer")
        {
            string name, type, dis, max;
            temp >> name >> type >> dis >> max;
            int distance = std::stoi(dis);
            int maxOrders = std::stoi(max);
            AddCustomer *a = new AddCustomer(name, type, distance, maxOrders);
            a->act(*this);
        }
        if (word == "orderStatus")
        {
            temp >> num;
            int orderId = std::stoi(num);
            PrintOrderStatus *p = new PrintOrderStatus(orderId);
            p->act(*this);
        }
        if (word == "customerStatus")
        {
            temp >> num;
            int customerId = std::stoi(num);
            PrintCustomerStatus *p = new PrintCustomerStatus(customerId);
            p->act(*this);
        }
        if (word == "volunteerStatus")
        {
            temp >> num;
            int volunteerId = std::stoi(num);
            PrintVolunteerStatus *p = new PrintVolunteerStatus(volunteerId);
            p->act(*this);
        }
        if (word == "log")
        {
            PrintActionsLog *p = new PrintActionsLog();
            p->act(*this);
        }
        if (word == "close")
        {
            Close *c = new Close();
            c->act(*this);
        }
        if (word == "backup")
        {
            BackupWareHouse *b = new BackupWareHouse();
            b->act(*this);
        }
        if (word == "restore")
        {
            RestoreWareHouse *r = new RestoreWareHouse();
            r->act(*this);
        }
    }
}

void WareHouse::close()
{
    for (std::vector<Order *>::size_type i = 0; i < pendingOrders.size(); i++)
    {
        cout << pendingOrders[i]->toStringForClose() << endl;
    }
    for (std::vector<Order *>::size_type i = 0; i < inProcessOrders.size(); i++)
    {
        cout << inProcessOrders[i]->toStringForClose() << endl;
    }
    for (std::vector<Order *>::size_type i = 0; i < completedOrders.size(); i++)
    {
        cout << completedOrders[i]->toStringForClose() << endl;
    }
    isOpen = false;
}

void WareHouse::open()
{
    isOpen = true;
    std::cout << "Warehouse is open!" << std ::endl;
}

void WareHouse::createBackUp()
{
    if (backup == nullptr)
        backup = new WareHouse(*this); // calling the copy constractor
    else
        *backup = *this; // calling the = operator
}

void WareHouse::restoreWarehouse()
{
    *this = *backup; // using the "=" operator
}

void WareHouse::ParseConFile(const string &configFilePath)
{
    std::ifstream myfile;
    myfile.open(configFilePath);
    std::string myline;
    if (myfile.is_open())
    {
        while (myfile)
        {
            std::getline(myfile, myline);
            stringstream temp(myline);
            string word;
            temp >> word;
            if (word == "customer")
                this->addCustomer(&temp);
            if (word == "volunteer")
                this->addVolunteer(&temp);
        }
    }
}

// add a new customer to the customer list
void WareHouse::addCustomer(stringstream *temp)
{
    string name, type, dis, maxOrder;
    (*temp) >> name >> type >> dis >> maxOrder;
    if (type == "soldier")
    {
        customers.push_back(new SoldierCustomer(customerCounter, name, std::stoi(dis), std::stoi(maxOrder)));
    }
    else if (type == "civilian")
        customers.push_back(new CivilianCustomer(customerCounter, name, std::stoi(dis), std::stoi(maxOrder)));
    else
        customerCounter--; // problem in the type, so we don't do anything
    customerCounter++;
}

// add a new volunteer to the customer list
void WareHouse::addVolunteer(stringstream *temp)
{
    string name, type;
    (*temp) >> name >> type;
    if (type == "collector")
    {
        string cooldown;
        (*temp) >> cooldown;
        volunteers.push_back(new CollectorVolunteer(volunteerCounter, name, std::stoi(cooldown)));
    }
    else if (type == "limited_collector")
    {
        string cooldown, maxOrder;
        (*temp) >> cooldown >> maxOrder;
        volunteers.push_back(new LimitedCollectorVolunteer(volunteerCounter, name, std::stoi(cooldown), std::stoi(maxOrder)));
    }
    else if (type == "driver")
    {
        string maxdis, distancePerStep;
        (*temp) >> maxdis >> distancePerStep;
        volunteers.push_back(new DriverVolunteer(volunteerCounter, name, std::stoi(maxdis), std::stoi(distancePerStep)));
    }
    else if (type == "limited_driver")
    {
        string maxdis, distancePerStep, maxOrder;
        (*temp) >> maxdis >> distancePerStep >> maxOrder;
        volunteers.push_back(new LimitedDriverVolunteer(volunteerCounter, name, std::stoi(maxdis), std::stoi(distancePerStep), std::stoi(maxOrder)));
    }
    else
        volunteerCounter--; // problem in the type, so we don't do anything
    volunteerCounter++;
}

// do deep delete to all vectors
void WareHouse::deleteVectors()
{
    for (std::vector<Customer *>::size_type i = 0; i < customers.size(); i++)
    {
        if (customers[i] != nullptr)
            delete customers[i];
    }
    customers.clear();
    for (std::vector<Volunteer *>::size_type i = 0; i < volunteers.size(); i++)
    {
        if (volunteers[i] != nullptr)
            delete volunteers[i];
    }
    volunteers.clear();
    for (std::vector<Order *>::size_type i = 0; i < pendingOrders.size(); i++)
    {
        if (pendingOrders[i] != nullptr)
            delete pendingOrders[i];
    }
    pendingOrders.clear();
    for (std::vector<Order *>::size_type i = 0; i < inProcessOrders.size(); i++)
    {
        if (inProcessOrders[i] != nullptr)
            delete inProcessOrders[i];
    }
    inProcessOrders.clear();
    for (std::vector<Order *>::size_type i = 0; i < completedOrders.size(); i++)
    {
        if (completedOrders[i] != nullptr)
            delete completedOrders[i];
    }
    completedOrders.clear();
    for (std::vector<BaseAction *>::size_type i = 0; i < actionsLog.size(); i++)
    {
        if (actionsLog[i] != nullptr)
            delete actionsLog[i];
    }
    actionsLog.clear();
}
