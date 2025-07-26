#include "room.h"

room::room(std::string roomNumber, double pricePerNight)
{
    this->ID = roomNumber;
    this->pricePerNight = pricePerNight;
    this->isOccupied = 0;
    this->current_guest = "";
    int type = this->ID[2] - '0';
    
    room_director director;
    room_item_director item_director;
    
    singleNormalRoom construct1;
    doubleNormalRoom construct2;
    singleVipRoom construct3;
    doubleVipRoom construct4;

    singleRoomItem item_construct1;
    doubleRoomItem item_construct2;

    if(type % 2) View = city;
    else View = nature;

    switch (type)
    {
    case 1: case 2:
        director.construct(&construct1);
        item_director.construct(&item_construct1);
        if(type == 1) this->typeName = "Single normal room with city view";
        else this->typeName = "Single normal room with nature view";
        this->roomType = director.getResult(&construct1);
        this->item = item_director.getResult(&item_construct1);
        break;
    case 3: case 4:
        director.construct(&construct2);
        item_director.construct(&item_construct2);
        if(type == 3) this->typeName = "Double normal room with city view";
        else this->typeName = "Double normal room with nature view";
        this->roomType = director.getResult(&construct2);
        this->item = item_director.getResult(&item_construct2);
        break;

    case 5: case 6:
        director.construct(&construct3);
        item_director.construct(&item_construct2);
        if(type == 5) this->typeName = "Single VIP room with city view";
        else this->typeName = "Single VIP room with nature view";
        this->roomType = director.getResult(&construct3);
        this->item = item_director.getResult(&item_construct2);
        break;

    case 7: case 8:
        director.construct(&construct4);
        item_director.construct(&item_construct1);
        if(type == 6) this->typeName = "Double VIP room with city view";
        else this->typeName = "Double VIP room with nature view";
        this->roomType = director.getResult(&construct4);
        this->item = item_director.getResult(&item_construct1);
        break;
    default:
        break;
    }
}

room::room(room &a)
{
    this->ID = a.ID;
    roomType = new room_basic;
    roomType->setSingle_beds(a.roomType->getSingle_beds());
    roomType->setLarge_beds(a.roomType->getLarge_beds());
    roomType->setBathrooms(a.roomType->getBathrooms());
    roomType->setBath(a.roomType->getBath());
    roomType->setTV(a.roomType->getTV());
    roomType->setBalcol(a.roomType->getBalcol());
    roomType->setLoving_chair(a.roomType->getLoving_chair());
    roomType->setFridge(a.roomType->getFridge());
    roomType->setRooms(a.roomType->getRooms());

    item = new room_item;
    item->setTowel(a.item->getTowel());
    item->setHair_dryer(a.item->getHair_dryer());
    item->setSandals(a.item->getSandals());
    item->setSleep_dress(a.item->getSleep_dress());
    
    typeName = a.typeName;
    pricePerNight = a.pricePerNight;
    isOccupied = a.isOccupied;
    current_guest = a.current_guest;
    book_history = a.book_history;
    Service = a.Service;
}

room& room::operator=(const room& a)
{
    if(this == &a) return *this;
    
    this->ID = a.ID;

    delete roomType;
    roomType = new room_basic;
    roomType->setSingle_beds(a.roomType->getSingle_beds());
    roomType->setLarge_beds(a.roomType->getLarge_beds());
    roomType->setBathrooms(a.roomType->getBathrooms());
    roomType->setBath(a.roomType->getBath());
    roomType->setTV(a.roomType->getTV());
    roomType->setBalcol(a.roomType->getBalcol());
    roomType->setLoving_chair(a.roomType->getLoving_chair());
    roomType->setFridge(a.roomType->getFridge());
    roomType->setRooms(a.roomType->getRooms());
    
    delete item;
    item = new room_item;
    item->setTowel(a.item->getTowel());
    item->setHair_dryer(a.item->getHair_dryer());
    item->setSandals(a.item->getSandals());
    item->setSleep_dress(a.item->getSleep_dress());
    
    typeName = a.typeName;
    pricePerNight = a.pricePerNight;
    isOccupied = a.isOccupied;
    current_guest = a.current_guest;
    book_history = a.book_history;
    Service = a.Service;
    return *this;
}

room::~room()
{
    delete roomType;
    delete item;
}