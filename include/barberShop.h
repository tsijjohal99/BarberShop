#pragma once
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "barber.h"
#include "customer.h"

class BarberShop {
   private:
    std::mutex gLock;
    std::condition_variable gConditionVariable;
    std::vector<std::pair<std::shared_ptr<Barber>, std::shared_ptr<Customer>>> barberAndCustomer;
    std::queue<std::shared_ptr<Customer>> waitingRoom;
    int noOfSeats = 8;
    int customersEntered;
    const static int totalCustomers = 100;

   public:
    BarberShop();
    ~BarberShop();

    void turn();
    void barberAction(int id);
    void customerActon(int customerID);
    bool checkIfHaircutCompleted(std::shared_ptr<Customer> cs, int& id);
};
