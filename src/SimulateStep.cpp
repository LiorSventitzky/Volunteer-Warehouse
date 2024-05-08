#include "../include/Action.h"
#include "../include/WareHouse.h"
#include <string>
#include <vector>

SimulateStep::SimulateStep(int numOfSteps) : BaseAction(), numOfSteps(numOfSteps) {}

SimulateStep::SimulateStep(const SimulateStep &other) : BaseAction(other), numOfSteps(other.numOfSteps) {}

void SimulateStep::act(WareHouse &wareHouse)
{
    for (int i = 0; i < numOfSteps; i++)
        wareHouse.SimulateStepInWarehouse();
    this->BaseAction::complete();
    wareHouse.addAction(this);
}

std::string SimulateStep::toString() const
{
    string s = "SimulateStep " + std::to_string(numOfSteps) + " " + this->BaseAction::statusToString();
    return s;
}

SimulateStep *SimulateStep::clone() const { return new SimulateStep(*this); }
