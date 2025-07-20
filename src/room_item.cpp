#include "Room_item.h"

singleRoomItem::singleRoomItem() { item = new room_item(); }
void singleRoomItem::buildTowel() { item->setTowel(2); }
void singleRoomItem::buildHair_dryer() { item->setHair_dryer(1); }
void singleRoomItem::buildSleep_dress() { item->setSleep_dress(2); }
void singleRoomItem::buildSandals() { item->setSandals(2); }
room_item* singleRoomItem::getResult() { return new room_item(*item); }

doubleRoomItem::doubleRoomItem() { item = new room_item(); }
void doubleRoomItem::buildTowel() { item->setTowel(4); }
void doubleRoomItem::buildHair_dryer() { item->setHair_dryer(2); }
void doubleRoomItem::buildSleep_dress() { item->setSleep_dress(4); }
void doubleRoomItem::buildSandals() { item->setSandals(4); }
room_item* doubleRoomItem::getResult() { return new room_item(*item); }