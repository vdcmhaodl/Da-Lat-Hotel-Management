#pragma once

#include "room_basic.h"


void basic_room::setSingle_beds(int num) { single_beds = num; }
void basic_room::setLarge_beds(int num) { large_beds = num; }
void basic_room::setBathrooms(int num) { bathrooms = num; }
void basic_room::setBath(bool flag) { bath = flag; }
void basic_room::setTV(int num) { TV = num; }
void basic_room::setBalcol(bool flag) { balcol = flag; }
void basic_room::setLoving_chair(bool flag) { loving_chair = flag;}
void basic_room::setFridge(bool flag) { fridge = flag; }
void basic_room::setRooms(int num) { rooms = num; }
void basic_room::setPrice(double price) { this->price = price; }
void basic_room::setView(view v) { this->v = v; }