#include "logicManager.h"

#include <iostream>
#include <random>

LogicManager::LogicManager() {
    srand(time(NULL));
    system("cls");
    BarberShop bs;
    customerEntered = 0;
    managingBarberShop(bs);
}

LogicManager::~LogicManager() {
    std::cout << "Simulation has terminated" << std::endl;
}

void LogicManager::managingBarberShop(BarberShop& bs) {
    std::thread barberThread(&BarberShop::barberAction, &bs);
    for (int i = 0; i < totalCustomers; i++) {
        // std::thread customerThread(&BarberShop::customerActon, &bs, customerEntered);
        customerThreads[i] = std::thread(&BarberShop::customerActon, &bs, i);
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 3));
    }

    barberThread.join();
    for (int i = 0; i < totalCustomers; i++) {
        customerThreads[i].join();
    }
}