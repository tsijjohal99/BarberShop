#include "barberShop.h"

#include <chrono>
#include <iostream>
#include <thread>

BarberShop::BarberShop() {
    barberInShop = std::make_shared<Barber>();
}

BarberShop::~BarberShop() {
    std::cout << "The Barber Shop has closed" << std::endl;
}

void BarberShop::turn() {
    std::thread barberThread(&BarberShop::barberMovements, this);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread customerThread(&BarberShop::customer, this);

    barberThread.join();
    customerThread.join();
}

void BarberShop::barberMovements() {
    while (barberChair == nullptr) {
        auto now = std::chrono::system_clock::now();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::unique_lock<std::mutex> lock(gLock);
        if (waitingRoom.empty()) {
            std::cout << "Barber sleeps" << std::endl;
            barberInShop->setSleep(true);
            gConditionVariable.wait(lock, !barberInShop->getSleep());
            std::cout << "Barber wakes" << std::endl;
        }
        gConditionVariable.wait(lock, !waitingRoom.empty());
        barberChair = waitingRoom.front();
        waitingRoom.pop();
        std::cout << "cuts hair" << std::endl;
        std::cout << "customer leaves" << std::endl;
        barberChair->setHaircutCompleted(true);
        gConditionVariable.notify_one();
    }
}

void BarberShop::customer() {
    while (true) {
        std::unique_lock<std::mutex> lock(gLock);
        std::shared_ptr<Customer> cs = std::make_shared<Customer>();
        std::cout << "Customer enters" << std::endl;
        while (barberInShop->getSleep()) {
            std::cout << "Customer wakes Barber" << std::endl;
            barberInShop->setSleep(false);
        }
        gConditionVariable.notify_one();
        if (waitingRoom.size() < 5) {
            waitingRoom.push(cs);
            std::cout << "Add customer to waiting room" << std::endl;
            gConditionVariable.notify_one();
            gConditionVariable.wait(lock, barberChair->getHaircutCompleted());
            barberChair = nullptr;
        } else {
            std::cout << "Not enough space" << std::endl;
            continue;
        }
        std::cout << "Customer Leaves" << std::endl;
    }
}