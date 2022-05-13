#include "barberShop.h"

#include <chrono>
#include <iostream>
#include <thread>

BarberShop::BarberShop() {
    customersEntered = 0;
    std::cout << "The Barber Shop is now open" << std::endl;
    toWake = 0;
}

BarberShop::~BarberShop() { std::cout << "The Barber Shop has closed" << std::endl; }

void BarberShop::barberAction(int id) {
    barberAndCustomer.push_back(std::make_pair(std::make_shared<Barber>(id), nullptr));

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::unique_lock<std::mutex> lock(gLock);
        if (barberAndCustomer[id].second == nullptr) {
            // lock.unlock();
            // auto now = std::chrono::system_clock::now();

            // lock.lock();

            if (waitingRoom.empty()) {
                std::cout << "Barber " << id << " sleeps." << std::endl;
                barberAndCustomer[id].first->setSleep(true);
                // lock.unlock();
                gConditionVariable.wait(lock, [&] { return !barberAndCustomer[id].first->getSleep(); });
                // lock.lock();
                //    barberAndCustomer[id].first->setSleep(false);
                std::cout << "Barber " << id << " wakes" << std::endl;
                gConditionVariable.wait(lock, [&] { return !waitingRoom.empty(); });
            }
            int randomCustomer = rand() % barberAndCustomer.size();
            barberAndCustomer[randomCustomer].second = waitingRoom.front();
            std::cout << "Barber " << randomCustomer << " get Customer "
                      << barberAndCustomer[randomCustomer].second->getId() << std::endl;
            waitingRoom.pop();
            std::cout << "Barber " << randomCustomer << " cuts Customer "
                      << barberAndCustomer[randomCustomer].second->getId() << " hair." << std::endl;
            barberAndCustomer[randomCustomer].second->setHaircutCompleted(true);
            gConditionVariable.notify_one();
            lock.unlock();
            // std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

void BarberShop::customerActon(int customerID) {
    std::shared_ptr<Customer> cs = std::make_shared<Customer>(customerID);
    // std::this_thread::sleep_for(std::chrono::seconds(2));
    std::unique_lock<std::mutex> lock(gLock);
    // std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Customer " << cs->getId() << " enters" << std::endl;
    std::vector<int> barberSleepingIds;
    for (const auto& barber : barberAndCustomer)
        if (barber.first->getSleep())
            barberSleepingIds.push_back(barber.first->getId());
    if (!barberSleepingIds.empty()) {
        std::cout << "Customer " << cs->getId() << " wakes Barber "
                  << barberAndCustomer[barberSleepingIds[0]].first->getId() << std::endl;
        barberAndCustomer[barberSleepingIds[0]].first->setSleep(false);
        gConditionVariable.notify_all();
    }
    // lock.unlock();
    //  if (barberAndCustomer[0].first->getSleep()) {
    //      std::cout << "Customer " << cs->getId() << " wakes Barber" << std::endl;
    //      barberAndCustomer[0].first->setSleep(false);
    //  }

    if (waitingRoom.size() < 5) {
        waitingRoom.push(cs);
        // lock.lock();
        std::cout << "Add Customer " << cs->getId() << " to waiting room" << std::endl;

        gConditionVariable.notify_all();
        // lock.unlock();
        //  int id = 0;
        int id;
        gConditionVariable.wait(lock, [&] { return checkIfHaircutCompleted(cs, id); });
        // lock.lock();
        // int id = findIdOfBarber(cs);
        // lock.lock();
        std::cout << "Customer " << barberAndCustomer[id].second->getId()
                  << " haircut complete" << std::endl;
        std::cout << "Customer " << barberAndCustomer[id].second->getId()
                  << " Leaves" << std::endl;
        barberAndCustomer[id].second = nullptr;
    } else {
        // lock.lock();
        std::cout << "Not enough space so Customer " << cs->getId() << " Leaves" << std::endl;
    }
    // lock.unlock();
}

int BarberShop::findIdOfBarber(std::shared_ptr<Customer> cs) {
    while (true)
        for (const auto& barber : barberAndCustomer)
            if (barber.second == cs)
                return barber.second->getId();
}

bool BarberShop::checkIfHaircutCompleted(std::shared_ptr<Customer> cs, int& id) {
    // while (id == -1) findIdOfBarber(cs);
    // for (const auto& barber : barberAndCustomer) {
    //     if (barber.second == cs) {
    //         int id = barber.second->getId();
    //         if (barberAndCustomer[id].second == nullptr)
    //             return false;
    //         else
    //             return barberAndCustomer[id].second->getHaircutCompleted();
    //     }
    // }
    // return false;

    id = rand() % barberAndCustomer.size();
    if (barberAndCustomer[id].second == nullptr)
        return false;
    else
        return barberAndCustomer[id].second->getHaircutCompleted();
}