#pragma once

#include "room_cityview.h"

//single City normal room
singleNormalRoom_CityView::singleNormalRoom_CityView() { room = new room_basic(); }
void singleNormalRoom_CityView::buildSingle_beds() { room->setSingle_beds(2); }
void singleNormalRoom_CityView::buildLarge_beds() { room->setLarge_beds(0); }
void singleNormalRoom_CityView::buildBathrooms() { room->setBathrooms(1); }
void singleNormalRoom_CityView::buildBath() { room->setBath(0); }
void singleNormalRoom_CityView::buildTV() { room->setTV(1); }
void singleNormalRoom_CityView::buildBalcol() { room->setBalcol(0); }
void singleNormalRoom_CityView::buildLoving_chair() { room->setLoving_chair(0); }
void singleNormalRoom_CityView::buildFridge() { room->setFridge(1); }
void singleNormalRoom_CityView::buildRooms() { room->setRooms(1); }
void singleNormalRoom_CityView::buildView() { room->setView(city); }
room_basic* singleNormalRoom_CityView::getResult() { return new room_basic(*room); }

//double City normal room
doubleNormalRoom_CityView::doubleNormalRoom_CityView() { room = new room_basic(); }
void doubleNormalRoom_CityView::buildSingle_beds() { room->setSingle_beds(4); }
void doubleNormalRoom_CityView::buildLarge_beds() { room->setLarge_beds(0); }
void doubleNormalRoom_CityView::buildBathrooms() { room->setBathrooms(1); }
void doubleNormalRoom_CityView::buildBath() { room->setBath(0); }
void doubleNormalRoom_CityView::buildTV() { room->setTV(2); }
void doubleNormalRoom_CityView::buildBalcol() { room->setBalcol(0); }
void doubleNormalRoom_CityView::buildLoving_chair() { room->setLoving_chair(0); }
void doubleNormalRoom_CityView::buildFridge() { room->setFridge(1); }
void doubleNormalRoom_CityView::buildRooms() { room->setRooms(2); }
void doubleNormalRoom_CityView::buildView() { room->setView(city); }
room_basic* doubleNormalRoom_CityView::getResult() { return new room_basic(*room); }

//single City large room
singleVipRoom_CityView::singleVipRoom_CityView() { room = new room_basic(); }
void singleVipRoom_CityView::buildSingle_beds() { room->setSingle_beds(0); }
void singleVipRoom_CityView::buildLarge_beds() { room->setLarge_beds(1); }
void singleVipRoom_CityView::buildBathrooms() { room->setBathrooms(1); }
void singleVipRoom_CityView::buildBath() { room->setBath(1); }
void singleVipRoom_CityView::buildTV() { room->setTV(1); }
void singleVipRoom_CityView::buildBalcol() { room->setBalcol(1); }
void singleVipRoom_CityView::buildLoving_chair() { room->setLoving_chair(1); }
void singleVipRoom_CityView::buildFridge() { room->setFridge(1); }
void singleVipRoom_CityView::buildRooms() { room->setRooms(1); }
void singleVipRoom_CityView::buildView() { room->setView(city); }
room_basic* singleVipRoom_CityView::getResult() { return new room_basic(*room); }

//double City large room;
doubleVipRoom_CityView::doubleVipRoom_CityView() { room = new room_basic(); }
void doubleVipRoom_CityView::buildSingle_beds() { room->setSingle_beds(0); }
void doubleVipRoom_CityView::buildLarge_beds() { room->setLarge_beds(2); }
void doubleVipRoom_CityView::buildBathrooms() { room->setBathrooms(2); }
void doubleVipRoom_CityView::buildBath() { room->setBath(1); }
void doubleVipRoom_CityView::buildTV() { room->setTV(2); }
void doubleVipRoom_CityView::buildBalcol() { room->setBalcol(1); }
void doubleVipRoom_CityView::buildLoving_chair() { room->setLoving_chair(1); }
void doubleVipRoom_CityView::buildFridge() { room->setFridge(1); }
void doubleVipRoom_CityView::buildRooms() { room->setRooms(2); }
void doubleVipRoom_CityView::buildView() { room->setView(city); }
room_basic* doubleVipRoom_CityView::getResult() { return new room_basic(*room); }