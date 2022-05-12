#pragma once

#include <list>
#include <thread>

#include "barberShop.h"

class LogicManager {
   private:
    int customerEntered;
    const static int totalCustomers = 20;
    std::thread customerThreads[totalCustomers];

   public:
    LogicManager();
    ~LogicManager();

    void managingBarberShop(BarberShop& bs);
};