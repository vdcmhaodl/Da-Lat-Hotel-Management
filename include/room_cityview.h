#pragma once

#include "room_build.h"

class singleNormalRoom_CityView : public roomBuilder
{
    room_basic* room;
public:
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    void buildPrice() override;
    void buildView() override;
};

class doubleNormalRoom_CityView : public roomBuilder
{
    room_basic* room;
public:
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    void buildPrice() override;
    void buildView() override;
};

class singleVipRoom_CityView : public roomBuilder
{
    room_basic* room;
public:
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    void buildPrice() override;
    void buildView() override;
};

class doubleVipRoom_CityView : public roomBuilder
{
    room_basic* room;
public:
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    void buildPrice() override;
    void buildView() override;
};