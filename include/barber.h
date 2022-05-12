#pragma once

class Barber {
   private:
    bool sleep;

   public:
    Barber(/* args */);
    ~Barber();

    bool getSleep();
    void setSleep(bool sl);
};
