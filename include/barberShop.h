#pragma once
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

#include "barber.h"
#include "customer.h"

class BarberShop {
   private:
    std::mutex gLock;
    std::condition_variable gConditionVariable;
    std::shared_ptr<Barber> barberInShop;
    std::shared_ptr<Customer> barberChair;
    std::queue<std::shared_ptr<Customer>> waitingRoom;
    int noOfSeats = 5;
    int customersEntered;

   public:
    BarberShop();
    ~BarberShop();

    void turn();
    void barberAction();
    void customerActon(int customerID);
    std::thread addBarber();
    std::thread addCustomer(int customerID);
};
