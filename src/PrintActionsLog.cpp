#include "../include/Action.h"
#include "../include/WareHouse.h"
#include <iostream>

PrintActionsLog::PrintActionsLog() : BaseAction() {}
PrintActionsLog::PrintActionsLog(const PrintActionsLog &other) : BaseAction(other) {}

void PrintActionsLog::act(WareHouse &wareHouse)
{
    BaseAction::complete(); // This action never results in an error
    wareHouse.addAction(this);
    vector<BaseAction *> log = wareHouse.getActions();
    for (std::vector<BaseAction *>::size_type i = 0; i < log.size(); i++)
        std::cout << log[i]->toString() << std::endl;
}

PrintActionsLog *PrintActionsLog::clone() const
{
    return new PrintActionsLog(*this);
}

string PrintActionsLog::toString() const
{
    string s = "log " + this->BaseAction::statusToString();
    return s;
}
