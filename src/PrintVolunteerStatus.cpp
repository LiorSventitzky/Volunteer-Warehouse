#include <string>
#include <vector>
#include "../include/Action.h"
#include "../include/WareHouse.h"

PrintVolunteerStatus::PrintVolunteerStatus(int id) : BaseAction(), volunteerId(id) {}
PrintVolunteerStatus::PrintVolunteerStatus(const PrintVolunteerStatus &other) : BaseAction(other), volunteerId(other.volunteerId) {}
void PrintVolunteerStatus::act(WareHouse &wareHouse)
{
    int index = wareHouse.doesVolunteerExist(volunteerId);
    if (index != -1)
    {
        wareHouse.printVolunteerStatus(index);
        this->BaseAction::complete();
    }
    else
    {
        this->BaseAction::error("volunteer doesn't exist");
    }
    wareHouse.addAction(this);
}
PrintVolunteerStatus *PrintVolunteerStatus::clone() const { return new PrintVolunteerStatus(*this); }
string PrintVolunteerStatus::toString() const
{
    return "PrintVolunteerStatus " + std::to_string(volunteerId) + " " + this->BaseAction::statusToString();
}
