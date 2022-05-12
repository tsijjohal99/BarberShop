#include "barber.h"

Barber::Barber() {
    sleep = true;
}

Barber::~Barber() {
}

bool Barber::getSleep() { return sleep; }

void Barber::setSleep(bool sl) { sleep = sl; }