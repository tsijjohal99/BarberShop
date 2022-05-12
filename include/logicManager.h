#pragma once

#include "barberShop.h"

class LogicManager {
   private:
    bool simulation = false;

   public:
    LogicManager();
    ~LogicManager();

    void managingBarberShop(BarberShop& bs);
};