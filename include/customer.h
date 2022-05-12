#pragma once

class Customer {
   private:
    bool haircutCompleted;
    int id;

   public:
    explicit Customer(int idCus);
    ~Customer();

    bool getHaircutCompleted();
    void setHaircutCompleted(bool haircut);
    int getId();
};