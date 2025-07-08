#pragma once

#include "room_natureview.h"

//single nature normal room
void singleNatureNormalRoom::buildSingle_beds() { room->setSingle_beds(2); }
void singleNatureNormalRoom::buildLarge_beds() { room->setLarge_beds(0); }
void singleNatureNormalRoom::buildBathrooms() { room->setBathrooms(1); }
void singleNatureNormalRoom::buildBath() { room->setBath(0); }
void singleNatureNormalRoom::buildTV() { room->setTV(1); }
void singleNatureNormalRoom::buildBalcol() { room->setBalcol(0); }
void singleNatureNormalRoom::buildLoving_chair() { room->setLoving_chair(0); }
void singleNatureNormalRoom::buildFridge() { room->setFridge(1); }
void singleNatureNormalRoom::buildRooms() { room->setRooms(1); }
void singleNatureNormalRoom::buildView() { room->setView(nature); }
void singleNatureNormalRoom::buildPrice() { room->setPrice(100000); }

//double nature normal room
void doubleNatureNormalRoom::buildSingle_beds() { room->setSingle_beds(4); }
void doubleNatureNormalRoom::buildLarge_beds() { room->setLarge_beds(0); }
void doubleNatureNormalRoom::buildBathrooms() { room->setBathrooms(1); }
void doubleNatureNormalRoom::buildBath() { room->setBath(0); }
void doubleNatureNormalRoom::buildTV() { room->setTV(2); }
void doubleNatureNormalRoom::buildBalcol() { room->setBalcol(0); }
void doubleNatureNormalRoom::buildLoving_chair() { room->setLoving_chair(0); }
void doubleNatureNormalRoom::buildFridge() { room->setFridge(1); }
void doubleNatureNormalRoom::buildRooms() { room->setRooms(2); }
void doubleNatureNormalRoom::buildView() { room->setView(nature); }
void doubleNatureNormalRoom::buildPrice() { room->setPrice(200000); }

//single nature large room
void singleNatureLargeRoom::buildSingle_beds() { room->setSingle_beds(0); }
void singleNatureLargeRoom::buildLarge_beds() { room->setLarge_beds(1); }
void singleNatureLargeRoom::buildBathrooms() { room->setBathrooms(1); }
void singleNatureLargeRoom::buildBath() { room->setBath(1); }
void singleNatureLargeRoom::buildTV() { room->setTV(1); }
void singleNatureLargeRoom::buildBalcol() { room->setBalcol(1); }
void singleNatureLargeRoom::buildLoving_chair() { room->setLoving_chair(1); }
void singleNatureLargeRoom::buildFridge() { room->setFridge(1); }
void singleNatureLargeRoom::buildRooms() { room->setRooms(1); }
void singleNatureLargeRoom::buildView() { room->setView(nature); }
void singleNatureLargeRoom::buildPrice() { room->setPrice(150000); }

//double nature large room;
void doubleNatureLargeRoom::buildSingle_beds() { room->setSingle_beds(0); }
void doubleNatureLargeRoom::buildLarge_beds() { room->setLarge_beds(2); }
void doubleNatureLargeRoom::buildBathrooms() { room->setBathrooms(2); }
void doubleNatureLargeRoom::buildBath() { room->setBath(1); }
void doubleNatureLargeRoom::buildTV() { room->setTV(2); }
void doubleNatureLargeRoom::buildBalcol() { room->setBalcol(1); }
void doubleNatureLargeRoom::buildLoving_chair() { room->setLoving_chair(1); }
void doubleNatureLargeRoom::buildFridge() { room->setFridge(1); }
void doubleNatureLargeRoom::buildRooms() { room->setRooms(2); }
void doubleNatureLargeRoom::buildView() { room->setView(nature); }
void doubleNatureLargeRoom::buildPrice() { room->setPrice(200000); }