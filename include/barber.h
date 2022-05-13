#pragma once

class Barber {
   private:
    bool sleep;
    int id;

   public:
    explicit Barber(int idBarb);
    ~Barber();

    bool getSleep();
    void setSleep(bool sl);
    int getId();
};
