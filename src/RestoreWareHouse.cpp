#include "../include/Action.h"
#include "../include/WareHouse.h"

extern WareHouse *backup;

RestoreWareHouse::RestoreWareHouse()
{
}

void RestoreWareHouse::act(WareHouse &wareHouse)
{
    if (backup != nullptr)
    {
        wareHouse.restoreWarehouse();
        BaseAction::complete();
    }
    else
        BaseAction::error("No backup available");
    wareHouse.addAction(this);
}

RestoreWareHouse *RestoreWareHouse::clone() const
{
    return new RestoreWareHouse(*this);
}

string RestoreWareHouse::toString() const
{
    string s = "RestorWareHouse: " + this->BaseAction::statusToString();
    return s;
}
