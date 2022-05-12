#include "logicManager.h"

#include <iostream>

LogicManager::LogicManager() {
    srand(time(NULL));
    BarberShop bs;
    bs.turn();
}

LogicManager::~LogicManager() {
    std::cout << "Simulation has terminated" << std::endl;
}