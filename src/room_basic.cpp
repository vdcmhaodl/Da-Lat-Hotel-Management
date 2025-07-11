#pragma once

#include "room_basic.h"


void room_basic::setSingle_beds(int num) { single_beds = num; }
void room_basic::setLarge_beds(int num) { large_beds = num; }
void room_basic::setBathrooms(int num) { bathrooms = num; }
void room_basic::setBath(bool flag) { bath = flag; }
void room_basic::setTV(int num) { TV = num; }
void room_basic::setBalcol(bool flag) { balcol = flag; }
void room_basic::setLoving_chair(bool flag) { loving_chair = flag;}
void room_basic::setFridge(bool flag) { fridge = flag; }
void room_basic::setRooms(int num) { rooms = num; }
void room_basic::setPrice(double price) { this->price = price; }
void room_basic::setView(view v) { this->v = v; }


void room_item::setTowel(int num) { this->towel = num; }
void room_item::setHair_dryer(int num) { this->hair_dryer = num; }
void room_item::setSleep_dress(int num) { this->sleep_dress = num; }
void room_item::setSandals(int num) { this->sandals = num; }