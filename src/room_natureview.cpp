#pragma once

#include "room_natureview.h"

//single nature normal room
void singleNormalRoom_NatureView::buildSingle_beds() { room->setSingle_beds(2); }
void singleNormalRoom_NatureView::buildLarge_beds() { room->setLarge_beds(0); }
void singleNormalRoom_NatureView::buildBathrooms() { room->setBathrooms(1); }
void singleNormalRoom_NatureView::buildBath() { room->setBath(0); }
void singleNormalRoom_NatureView::buildTV() { room->setTV(1); }
void singleNormalRoom_NatureView::buildBalcol() { room->setBalcol(0); }
void singleNormalRoom_NatureView::buildLoving_chair() { room->setLoving_chair(0); }
void singleNormalRoom_NatureView::buildFridge() { room->setFridge(1); }
void singleNormalRoom_NatureView::buildRooms() { room->setRooms(1); }
void singleNormalRoom_NatureView::buildView() { room->setView(nature); }
void singleNormalRoom_NatureView::buildPrice() { room->setPrice(100000); }

//double nature normal room
void doubleNormalRoom_NatureView::buildSingle_beds() { room->setSingle_beds(4); }
void doubleNormalRoom_NatureView::buildLarge_beds() { room->setLarge_beds(0); }
void doubleNormalRoom_NatureView::buildBathrooms() { room->setBathrooms(1); }
void doubleNormalRoom_NatureView::buildBath() { room->setBath(0); }
void doubleNormalRoom_NatureView::buildTV() { room->setTV(2); }
void doubleNormalRoom_NatureView::buildBalcol() { room->setBalcol(0); }
void doubleNormalRoom_NatureView::buildLoving_chair() { room->setLoving_chair(0); }
void doubleNormalRoom_NatureView::buildFridge() { room->setFridge(1); }
void doubleNormalRoom_NatureView::buildRooms() { room->setRooms(2); }
void doubleNormalRoom_NatureView::buildView() { room->setView(nature); }
void doubleNormalRoom_NatureView::buildPrice() { room->setPrice(200000); }

//single nature large room
void singleVipRoom_NatureView::buildSingle_beds() { room->setSingle_beds(0); }
void singleVipRoom_NatureView::buildLarge_beds() { room->setLarge_beds(1); }
void singleVipRoom_NatureView::buildBathrooms() { room->setBathrooms(1); }
void singleVipRoom_NatureView::buildBath() { room->setBath(1); }
void singleVipRoom_NatureView::buildTV() { room->setTV(1); }
void singleVipRoom_NatureView::buildBalcol() { room->setBalcol(1); }
void singleVipRoom_NatureView::buildLoving_chair() { room->setLoving_chair(1); }
void singleVipRoom_NatureView::buildFridge() { room->setFridge(1); }
void singleVipRoom_NatureView::buildRooms() { room->setRooms(1); }
void singleVipRoom_NatureView::buildView() { room->setView(nature); }
void singleVipRoom_NatureView::buildPrice() { room->setPrice(150000); }

//double nature large room;
void doubleVipRoom_NatureView::buildSingle_beds() { room->setSingle_beds(0); }
void doubleVipRoom_NatureView::buildLarge_beds() { room->setLarge_beds(2); }
void doubleVipRoom_NatureView::buildBathrooms() { room->setBathrooms(2); }
void doubleVipRoom_NatureView::buildBath() { room->setBath(1); }
void doubleVipRoom_NatureView::buildTV() { room->setTV(2); }
void doubleVipRoom_NatureView::buildBalcol() { room->setBalcol(1); }
void doubleVipRoom_NatureView::buildLoving_chair() { room->setLoving_chair(1); }
void doubleVipRoom_NatureView::buildFridge() { room->setFridge(1); }
void doubleVipRoom_NatureView::buildRooms() { room->setRooms(2); }
void doubleVipRoom_NatureView::buildView() { room->setView(nature); }
void doubleVipRoom_NatureView::buildPrice() { room->setPrice(200000); }