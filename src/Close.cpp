#include "../include/Action.h"
#include "../include/WareHouse.h"
#include <iostream>

Close::Close() : BaseAction() {}
Close::Close(const Close &other) : BaseAction(other) {}
void Close::act(WareHouse &wareHouse)
{
    this->BaseAction::complete();
    wareHouse.addAction(this);
    wareHouse.close();
}

Close *Close::clone() const
{
    return new Close(*this);
}
string Close::toString() const
{
    string s = "Close " + this->BaseAction::statusToString();
    return s;
}
