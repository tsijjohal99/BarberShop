#pragma once

class Customer {
   private:
    bool haircutCompleted = false;

   public:
    Customer(/* args */);
    ~Customer();

    bool getHaircutCompleted();
    void setHaircutCompleted(bool haircut);
};