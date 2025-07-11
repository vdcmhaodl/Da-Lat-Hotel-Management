#pragma once

#include "room_build.h"

class singleNormalRoom_NatureView : public roomBuilder
{
    room_basic* room;
public:
    singleNormalRoom_NatureView();
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
    room_basic* getResult() override;
};

class doubleNormalRoom_NatureView : public roomBuilder
{
    room_basic* room;
public:
    doubleNormalRoom_NatureView();
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
    room_basic* getResult() override;
};

class singleVipRoom_NatureView : public roomBuilder
{
    room_basic* room;
public:
    singleVipRoom_NatureView();
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
    room_basic* getResult() override;
};

class doubleVipRoom_NatureView : public roomBuilder
{
    room_basic* room;
public:
    doubleVipRoom_NatureView();
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
    room_basic* getResult() override;
};