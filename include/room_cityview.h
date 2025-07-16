#pragma once

#include "room_build.h"

class singleNormalRoom_CityView : public roomBuilder
{
    room_basic* room;
public:
    singleNormalRoom_CityView();
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    void buildView() override;
    room_basic* getResult() override;
};

class doubleNormalRoom_CityView : public roomBuilder
{
    room_basic* room;
public:
    doubleNormalRoom_CityView();
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    void buildView() override;
    room_basic* getResult() override;
};

class singleVipRoom_CityView : public roomBuilder
{
    room_basic* room;
public:
    singleVipRoom_CityView();
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    void buildView() override;
    room_basic* getResult() override;
};

class doubleVipRoom_CityView : public roomBuilder
{
    room_basic* room;
public:
    doubleVipRoom_CityView();
    void buildSingle_beds() override;
    void buildLarge_beds() override;
    void buildBathrooms() override;
    void buildBath() override;
    void buildTV() override;
    void buildBalcol() override;
    void buildLoving_chair() override;
    void buildFridge() override;
    void buildRooms() override;
    void buildView() override;
    room_basic* getResult() override;
};