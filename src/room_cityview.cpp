#pragma once

#include "room_cityview.h"

//single City normal room
void singleCityNormalRoom::buildSingle_beds() { room->setSingle_beds(2); }
void singleCityNormalRoom::buildLarge_beds() { room->setLarge_beds(0); }
void singleCityNormalRoom::buildBathrooms() { room->setBathrooms(1); }
void singleCityNormalRoom::buildBath() { room->setBath(0); }
void singleCityNormalRoom::buildTV() { room->setTV(1); }
void singleCityNormalRoom::buildBalcol() { room->setBalcol(0); }
void singleCityNormalRoom::buildLoving_chair() { room->setLoving_chair(0); }
void singleCityNormalRoom::buildFridge() { room->setFridge(1); }
void singleCityNormalRoom::buildRooms() { room->setRooms(1); }
void singleCityNormalRoom::buildView() { room->setView(city); }
void singleCityNormalRoom::buildPrice() { room->setPrice(100000); }

//double City normal room
void doubleCityNormalRoom::buildSingle_beds() { room->setSingle_beds(4); }
void doubleCityNormalRoom::buildLarge_beds() { room->setLarge_beds(0); }
void doubleCityNormalRoom::buildBathrooms() { room->setBathrooms(1); }
void doubleCityNormalRoom::buildBath() { room->setBath(0); }
void doubleCityNormalRoom::buildTV() { room->setTV(2); }
void doubleCityNormalRoom::buildBalcol() { room->setBalcol(0); }
void doubleCityNormalRoom::buildLoving_chair() { room->setLoving_chair(0); }
void doubleCityNormalRoom::buildFridge() { room->setFridge(1); }
void doubleCityNormalRoom::buildRooms() { room->setRooms(2); }
void doubleCityNormalRoom::buildView() { room->setView(city); }
void doubleCityNormalRoom::buildPrice() { room->setPrice(200000); }

//single City large room
void singleCityLargeRoom::buildSingle_beds() { room->setSingle_beds(0); }
void singleCityLargeRoom::buildLarge_beds() { room->setLarge_beds(1); }
void singleCityLargeRoom::buildBathrooms() { room->setBathrooms(1); }
void singleCityLargeRoom::buildBath() { room->setBath(1); }
void singleCityLargeRoom::buildTV() { room->setTV(1); }
void singleCityLargeRoom::buildBalcol() { room->setBalcol(1); }
void singleCityLargeRoom::buildLoving_chair() { room->setLoving_chair(1); }
void singleCityLargeRoom::buildFridge() { room->setFridge(1); }
void singleCityLargeRoom::buildRooms() { room->setRooms(1); }
void singleCityLargeRoom::buildView() { room->setView(city); }
void singleCityLargeRoom::buildPrice() { room->setPrice(150000); }

//double City large room;
void doubleCityLargeRoom::buildSingle_beds() { room->setSingle_beds(0); }
void doubleCityLargeRoom::buildLarge_beds() { room->setLarge_beds(2); }
void doubleCityLargeRoom::buildBathrooms() { room->setBathrooms(2); }
void doubleCityLargeRoom::buildBath() { room->setBath(1); }
void doubleCityLargeRoom::buildTV() { room->setTV(2); }
void doubleCityLargeRoom::buildBalcol() { room->setBalcol(1); }
void doubleCityLargeRoom::buildLoving_chair() { room->setLoving_chair(1); }
void doubleCityLargeRoom::buildFridge() { room->setFridge(1); }
void doubleCityLargeRoom::buildRooms() { room->setRooms(2); }
void doubleCityLargeRoom::buildView() { room->setView(city); }
void doubleCityLargeRoom::buildPrice() { room->setPrice(200000); }