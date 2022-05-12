#include "customer.h"

Customer::Customer(int idCus) : id(idCus) { haircutCompleted = false; }

Customer::~Customer() {}

bool Customer::getHaircutCompleted() { return haircutCompleted; }

void Customer::setHaircutCompleted(bool haircut) { haircutCompleted = haircut; }

int Customer::getId() { return id; }