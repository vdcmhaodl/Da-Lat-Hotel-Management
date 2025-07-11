#include "room.h"

room::room(std::string roomNumber, double pricePerNight)
{
    this->roomNumber = roomNumber;
    this->pricePerNight = pricePerNight;
    this->isOccupied = 0;
    this->current_guest = "";
    int type = this->roomNumber[2] - '0';
    
    room_director director;
    room_item_director item_director;
    
    singleNormalRoom_CityView construct1;
    singleNormalRoom_NatureView construct2;
    doubleNormalRoom_CityView construct3;
    doubleNormalRoom_NatureView construct4;
    singleVipRoom_CityView construct5;
    singleVipRoom_NatureView construct6;
    doubleVipRoom_CityView construct7;
    doubleVipRoom_NatureView construct8;

    singleRoomItem item_construct1;
    doubleRoomItem item_construct2;

    switch (type)
    {
    case 1:
        director.construct(&construct1);
        item_director.construct(&item_construct1);

        this->typeName = "Single normal room with city view";
        this->roomType = director.getResult(&construct1);
        this->item = item_director.getResult(&item_construct1);
        break;

    case 2: 
        director.construct(&construct2);
        item_director.construct(&item_construct1);

        this->typeName = "Single normal room with nature view";
        this->roomType = director.getResult(&construct2);
        this->item = item_director.getResult(&item_construct1);
        break;

    case 3:
        director.construct(&construct3);
        item_director.construct(&item_construct2);

        this->typeName = "Double normal room with city view";
        this->roomType = director.getResult(&construct3);
        this->item = item_director.getResult(&item_construct2);
        break;

    case 4:
        director.construct(&construct4);
        item_director.construct(&item_construct2);

        this->typeName = "Double normal room with nature view";
        this->roomType = director.getResult(&construct4);
        this->item = item_director.getResult(&item_construct2);
        break;

    case 5:
        director.construct(&construct5);
        item_director.construct(&item_construct1);

        this->typeName = "Single vip room with city view";
        this->roomType = director.getResult(&construct5);
        this->item = item_director.getResult(&item_construct1);
        break;

    case 6:
        director.construct(&construct6);
        item_director.construct(&item_construct1);
        
        this->typeName = "Single vip room with nature view";
        this->roomType = director.getResult(&construct6);
        this->item = item_director.getResult(&item_construct1);
        break;

    case 7:
        director.construct(&construct7);
        item_director.construct(&item_construct2);
        
        this->typeName = "Double vip room with city view";
        this->roomType = director.getResult(&construct7);
        this->item = item_director.getResult(&item_construct2);
        break;

    case 8:
        director.construct(&construct8);
        item_director.construct(&item_construct2);
        
        this->typeName = "Double vip room with nature view";
        this->roomType = director.getResult(&construct8);
        this->item = item_director.getResult(&item_construct2);
        break;
    default:
        break;
    }
}