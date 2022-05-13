#pragma once

#include <list>
#include <thread>

#include "barberShop.h"

class LogicManager {
   private:
    int customerEntered;
    const static int totalCustomers = 100;
    const static int noOfBarbers = 3;
    std::thread customerThreads[totalCustomers];
    std::thread barberThreads[noOfBarbers];

   public:
    LogicManager();
    ~LogicManager();

    void managingBarberShop(BarberShop& bs);
};