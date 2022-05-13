#include "barber.h"

Barber::Barber(int idBarb) : id(idBarb) { sleep = true; }

Barber::~Barber() {}

bool Barber::getSleep() { return sleep; }

void Barber::setSleep(bool sl) { sleep = sl; }

int Barber::getId() { return id; }