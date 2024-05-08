#include "../include/Action.h"
#include "../include/WareHouse.h"

BackupWareHouse::BackupWareHouse() : BaseAction() {}
BackupWareHouse::BackupWareHouse(const BackupWareHouse &other) : BaseAction(other) {}
void BackupWareHouse::act(WareHouse &wareHouse)
{
    wareHouse.addAction(this);
    wareHouse.createBackUp();
    BaseAction::complete();
}
BackupWareHouse *BackupWareHouse::clone() const
{
    return new BackupWareHouse(*this);
}
string BackupWareHouse::toString() const
{
    string s = "BackupWarehouse: " + this->BaseAction::statusToString();
    return s;
}
