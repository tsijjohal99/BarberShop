#include "barberShop.h"

#include <chrono>
#include <iostream>
#include <thread>

BarberShop::BarberShop() {
    customersEntered = 0;
    std::cout << "The Barber Shop is now open" << std::endl;
    barberInShop = std::make_shared<Barber>();
}

BarberShop::~BarberShop() {
    std::cout << "The Barber Shop has closed" << std::endl;
}

void BarberShop::barberAction() {
    while (true) {
        if (barberChair == nullptr) {
            auto now = std::chrono::system_clock::now();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::unique_lock<std::mutex> lock(gLock);
            if (waitingRoom.empty()) {
                std::cout << "Barber sleeps." << std::endl;
                barberInShop->setSleep(true);
                gConditionVariable.wait(lock, [&] { return !barberInShop->getSleep(); });
                std::cout << "Barber wakes" << std::endl;
                gConditionVariable.wait(lock, [&] { return !waitingRoom.empty(); });
            }
            barberChair = waitingRoom.front();
            std::cout << "Barber get Customer " << barberChair->getId() << std::endl;
            waitingRoom.pop();
            std::cout << "Cuts Customer " << barberChair->getId() << " hair." << std::endl;
            barberChair->setHaircutCompleted(true);
            gConditionVariable.notify_one();
        }
    }
}

void BarberShop::customerActon(int customerID) {
    // while (true) {
    //  std::this_thread::sleep_for(std::chrono::seconds(rand() % 10));
    std::unique_lock<std::mutex> lock(gLock);
    std::shared_ptr<Customer> cs = std::make_shared<Customer>(customerID);
    customersEntered++;
    std::cout << "Customer " << cs->getId() << " enters" << std::endl;
    while (barberInShop->getSleep()) {
        std::cout << "Customer " << cs->getId() << " wakes Barber" << std::endl;
        barberInShop->setSleep(false);
    }
    gConditionVariable.notify_one();
    if (waitingRoom.size() < 5) {
        waitingRoom.push(cs);
        std::cout << "Add Customer " << cs->getId() << " to waiting room" << std::endl;
        gConditionVariable.notify_one();
        gConditionVariable.wait(lock, [&] {
                if (barberChair == nullptr) return false;
                else return barberChair->getHaircutCompleted(); });
        std::cout << "Customer " << barberChair->getId() << " haircut complete" << std::endl;
        std::cout << "Customer " << barberChair->getId() << " Leaves" << std::endl;
        barberChair = nullptr;
    } else {
        std::cout << "Not enough space so Customer " << cs->getId() << " Leaves" << std::endl;
    }

    //}
}

// std::thread BarberShop::addBarber() {
//     std::thread barberThread(&BarberShop::barberAction, this);
//     barberThread.detach();
// }

// std::thread BarberShop::addCustomer(int customerID) {
//     std::thread customerThread(&BarberShop::customerActon, this, customerID);
//     customerThread.detach();
// }