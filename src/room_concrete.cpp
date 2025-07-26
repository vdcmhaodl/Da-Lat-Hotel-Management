#include "room_concrete.h"

//single City normal room
singleNormalRoom::singleNormalRoom() { room = new room_basic(); }
void singleNormalRoom::buildSingle_beds() { room->setSingle_beds(2); }
void singleNormalRoom::buildLarge_beds() { room->setLarge_beds(0); }
void singleNormalRoom::buildBathrooms() { room->setBathrooms(1); }
void singleNormalRoom::buildBath() { room->setBath(0); }
void singleNormalRoom::buildTV() { room->setTV(1); }
void singleNormalRoom::buildBalcol() { room->setBalcol(0); }
void singleNormalRoom::buildLoving_chair() { room->setLoving_chair(0); }
void singleNormalRoom::buildFridge() { room->setFridge(1); }
void singleNormalRoom::buildRooms() { room->setRooms(1); }
room_basic* singleNormalRoom::getResult() { return new room_basic(*room); }
singleNormalRoom::~singleNormalRoom() { delete room; }

//double City normal room
doubleNormalRoom::doubleNormalRoom() { room = new room_basic(); }
void doubleNormalRoom::buildSingle_beds() { room->setSingle_beds(4); }
void doubleNormalRoom::buildLarge_beds() { room->setLarge_beds(0); }
void doubleNormalRoom::buildBathrooms() { room->setBathrooms(1); }
void doubleNormalRoom::buildBath() { room->setBath(0); }
void doubleNormalRoom::buildTV() { room->setTV(2); }
void doubleNormalRoom::buildBalcol() { room->setBalcol(0); }
void doubleNormalRoom::buildLoving_chair() { room->setLoving_chair(0); }
void doubleNormalRoom::buildFridge() { room->setFridge(1); }
void doubleNormalRoom::buildRooms() { room->setRooms(2); }
room_basic* doubleNormalRoom::getResult() { return new room_basic(*room); }
doubleNormalRoom::~doubleNormalRoom() { delete room; }

//single City large room
singleVipRoom::singleVipRoom() { room = new room_basic(); }
void singleVipRoom::buildSingle_beds() { room->setSingle_beds(0); }
void singleVipRoom::buildLarge_beds() { room->setLarge_beds(1); }
void singleVipRoom::buildBathrooms() { room->setBathrooms(1); }
void singleVipRoom::buildBath() { room->setBath(1); }
void singleVipRoom::buildTV() { room->setTV(1); }
void singleVipRoom::buildBalcol() { room->setBalcol(1); }
void singleVipRoom::buildLoving_chair() { room->setLoving_chair(1); }
void singleVipRoom::buildFridge() { room->setFridge(1); }
void singleVipRoom::buildRooms() { room->setRooms(1); }
room_basic* singleVipRoom::getResult() { return new room_basic(*room); }
singleVipRoom::~singleVipRoom() { delete room; }

//double City large room;
doubleVipRoom::doubleVipRoom() { room = new room_basic(); }
void doubleVipRoom::buildSingle_beds() { room->setSingle_beds(0); }
void doubleVipRoom::buildLarge_beds() { room->setLarge_beds(2); }
void doubleVipRoom::buildBathrooms() { room->setBathrooms(2); }
void doubleVipRoom::buildBath() { room->setBath(1); }
void doubleVipRoom::buildTV() { room->setTV(2); }
void doubleVipRoom::buildBalcol() { room->setBalcol(1); }
void doubleVipRoom::buildLoving_chair() { room->setLoving_chair(1); }
void doubleVipRoom::buildFridge() { room->setFridge(1); }
void doubleVipRoom::buildRooms() { room->setRooms(2); }
room_basic* doubleVipRoom::getResult() { return new room_basic(*room); }
doubleVipRoom::~doubleVipRoom() { delete room; }