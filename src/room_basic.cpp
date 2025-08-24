#include "room_basic.h"

room_basic::room_basic() {
  single_beds = 0;
  large_beds = 0;
  bathrooms = 0;
  bath = 0;
  TV = 0;
  balcol = 0;
  loving_chair = 0;
  fridge = 0;
  rooms = 0;
}

room_basic::room_basic(room_basic& a) {
  single_beds = a.single_beds;
  large_beds = a.large_beds;
  bathrooms = a.bathrooms;
  bath = a.bath;
  TV = a.TV;
  balcol = a.balcol;
  loving_chair = a.loving_chair;
  fridge = a.fridge;
  rooms = a.rooms;
}

void room_basic::setSingle_beds(int num) { single_beds = num; }
void room_basic::setLarge_beds(int num) { large_beds = num; }
void room_basic::setBathrooms(int num) { bathrooms = num; }
void room_basic::setBath(bool flag) { bath = flag; }
void room_basic::setTV(int num) { TV = num; }
void room_basic::setBalcol(bool flag) { balcol = flag; }
void room_basic::setLoving_chair(bool flag) { loving_chair = flag; }
void room_basic::setFridge(bool flag) { fridge = flag; }
void room_basic::setRooms(int num) { rooms = num; }

int room_basic::getSingle_beds() { return single_beds; }
int room_basic::getLarge_beds() { return large_beds; }
int room_basic::getBathrooms() { return bathrooms; }
bool room_basic::getBath() { return bath; }
int room_basic::getTV() { return TV; }
bool room_basic::getBalcol() { return balcol; }
bool room_basic::getLoving_chair() { return loving_chair; }
bool room_basic::getFridge() { return fridge; }
int room_basic::getRooms() { return rooms; }

room_item::room_item() {
  towel = 0;
  sleep_dress = 0;
  sandals = 0;
  hair_dryer = 0;
}

room_item::room_item(room_item& a) {
  towel = a.towel;
  sleep_dress = a.sleep_dress;
  sandals = a.sandals;
  hair_dryer = a.hair_dryer;
}
void room_item::setTowel(int num) { this->towel = num; }
void room_item::setHair_dryer(int num) { this->hair_dryer = num; }
void room_item::setSleep_dress(int num) { this->sleep_dress = num; }
void room_item::setSandals(int num) { this->sandals = num; }

int room_item::getTowel() { return this->towel; }
int room_item::getHair_dryer() { return this->hair_dryer; }
int room_item::getSleep_dress() { return this->sleep_dress; }
int room_item::getSandals() { return this->sandals; }