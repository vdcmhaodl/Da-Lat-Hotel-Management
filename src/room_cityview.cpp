#pragma once

#include "room_cityview.h"

//single City normal room
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
void singleNormalRoom_CityView::buildPrice() { room->setPrice(100000); }

//double City normal room
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
void doubleNormalRoom_CityView::buildPrice() { room->setPrice(200000); }

//single City large room
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
void singleVipRoom_CityView::buildPrice() { room->setPrice(150000); }

//double City large room;
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
void doubleVipRoom_CityView::buildPrice() { room->setPrice(200000); }