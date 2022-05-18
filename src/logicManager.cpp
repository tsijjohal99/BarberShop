#include "logicManager.h"

#include <iostream>
#include <random>

LogicManager::LogicManager() {
    srand(time(NULL));
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    fflush(stdout);
    // system("cls");
    BarberShop bs;
    customerEntered = 0;
    managingBarberShop(bs);
}

LogicManager::~LogicManager() {
    std::cout << "Simulation has terminated" << std::endl;
}

void LogicManager::managingBarberShop(BarberShop& bs) {
    for (int i = 0; i < noOfBarbers; i++)
        barberThreads[i] = std::thread(&BarberShop::barberAction, &bs, i);

    for (int j = 0; j < totalCustomers; j++) {
        customerThreads[j] = std::thread(&BarberShop::customerActon, &bs, j);
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 4000));
    }

    for (auto& barbThread : barberThreads)
        barbThread.join();

    for (auto& cusThread : customerThreads)
        cusThread.join();
}