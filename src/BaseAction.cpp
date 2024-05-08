#include "../include/Action.h"
#include "../include/WareHouse.h"
#include "../include/Customer.h"
#include "../include/Volunteer.h"
#include "../include/Order.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

BaseAction::BaseAction() : errorMsg(""), status(ActionStatus::COMPLETED) {} // the defult for status is COMPLETED only for intialize

BaseAction::BaseAction(const BaseAction &other) : errorMsg(other.errorMsg), status(other.status) {}

ActionStatus BaseAction::getStatus() const { return status; }

void BaseAction::complete() { status = ActionStatus::COMPLETED; }
void BaseAction::error(string errorMsg)
{
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg;
    std::cout << "Error: " + this->errorMsg << std::endl;
}
string BaseAction::getErrorMsg() const { return errorMsg; }

string BaseAction::statusToString() const
{
    if (BaseAction::getStatus() == ActionStatus::ERROR)
        return "ERROR";
    else
        return "COMPLETED";
}

BaseAction::~BaseAction() {}
