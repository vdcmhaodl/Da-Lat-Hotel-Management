#include "hotel.h"

floor::floor()
{
    this->flr = 0;
    price[0] = 0;
    price[1] = priceSingleNormalCity;
    price[2] = priceSingleNormalNature;
    price[3] = priceDoubleNormalCity;
    price[4] = priceDoubleNormalNature;
    price[5] = priceSingleVipCity;
    price[6] = priceSingleVipNature;
    price[7] = priceDoubleVipCity;
    price[8] = priceDoubleVipNature;
    num_rooms = 0;
    for(int i = 0; i <= 8; i++)
        Type[i] = 0;
}

floor::floor(int flr)
{
    this->flr = flr;
    price[0] = 0;
    price[1] = priceSingleNormalCity;
    price[2] = priceSingleNormalNature;
    price[3] = priceDoubleNormalCity;
    price[4] = priceDoubleNormalNature;
    price[5] = priceSingleVipCity;
    price[6] = priceSingleVipNature;
    price[7] = priceDoubleVipCity;
    price[8] = priceDoubleVipNature;
    num_rooms = 0;
    for(int i = 0; i <= 8; i++)
        Type[i] = 0;
}

floor::floor(int flr, std::vector<room> rooms, int type)
{
    this->flr = flr;
    price[0] = 0;
    price[1] = priceSingleNormalCity;
    price[2] = priceSingleNormalNature;
    price[3] = priceDoubleNormalCity;
    price[4] = priceDoubleNormalNature;
    price[5] = priceSingleVipCity;
    price[6] = priceSingleVipNature;
    price[7] = priceDoubleVipCity;
    price[8] = priceDoubleVipNature;
    for(int i = 0; i <= 8; i++)
        Type[i] = 0;
    for(int i = 0; i < rooms.size(); i++)
    {   
        room temp(rooms[i]);
        this->rooms[type].push_back(temp);
    }
    Type[type] = rooms.size();
    num_rooms = Type[type];
}

int floor::getNumRooms()
{
    return num_rooms;
}

void floor::updateRoomPrice(int roomType, double price)
{
    switch(roomType)
    {
        case 1: priceSingleNormalCity = price; break;
        case 2: priceSingleNormalNature = price; break;
        case 3: priceDoubleNormalCity = price; break;
        case 4: priceDoubleNormalNature = price; break;
        case 5: priceSingleVipCity = price; break;
        case 6: priceSingleVipNature = price; break;
        case 7: priceDoubleVipCity = price; break;
        case 8: priceDoubleVipNature = price; break;
    }
    this->price[roomType] = price;
    for(int i = 0; i < rooms[roomType].size(); i++)
        rooms[roomType][i].updatePrice(price);
}
    
void floor::addRoom(int roomType)
{
    std::string type_num = "01234567";
    std::string ID = std::to_string(this->flr);
    if(flr < 10) ID = '0' + ID;
    ID += type_num[roomType];
    std::string suffix_ID = std::to_string(this->Type[roomType]);
    if(this->Type[roomType < 10]) suffix_ID = '0' + suffix_ID;
    ID += suffix_ID;
    
    num_rooms++;
    Type[roomType]++;
    room temp(ID, this->price[roomType]);
    rooms[roomType].push_back(temp);
}

bool floor::removeRoom(std::string ID)
{
    int type = ID[2] - '0';
    int indx = -1;
    for(int i = 0; i < rooms[type].size(); i++)
        if(rooms[type][i].getID() == ID)
        {
            indx = i;
            break;
        }
    if(indx == -1) return 0;
    this->rooms[type].erase(this->rooms[type].begin() + indx);
    num_rooms--;
    return 1;
}

room& floor::findRoomByNumber(std::string ID)
{
    int type = ID[2] - '0';
    int indx = -1;
    for(int i = 0; i < rooms[type].size(); i++)
        if(rooms[type][i].getID() == ID)
        {
            indx = i;
            break;
        }
    return rooms[type][indx];
}

std::vector<room> floor::findAvailableRooms()
{
    std::vector<room> ans;
    for(int i = 1; i <= 8; i++)
        for(int j = 0; j < rooms[i].size(); j++)
            if(rooms[i][j].isAvailable()) 
            {
                room temp(rooms[i][j]);
                ans.push_back(temp);
            }
    return ans;
}

std::vector<room> floor::findRoomsByType(int type)
{
    std::vector<room> ans;
    for(int i = 0; i < rooms[type].size(); i++)
    {
        room temp(rooms[type][i]);
        ans.push_back(temp);
    }
    return ans;
}

std::vector<room> floor::findAllRooms()
{
    std::vector<room> ans;
    for(int i = 1; i <= 8; i++)
        for(int j = 0; j < rooms[i].size(); j++)
        {
            room temp(rooms[i][j]);
            ans.push_back(temp);
        }
    return ans;
}

void floor::displayAllFloorRooms()
{
    for(int i = 0; i <= 8; i++)
        for(int j = 0; j < rooms[i].size(); j++)
        {
            std::cout << "Room: " << rooms[i][j].getID() << ' ';
            std::cout << "State: " << ((rooms[i][j].isAvailable() == 1) ? "Available" : "Not available") << ' ';
            std::cout << "Type: " << nameType[i] << '\n';
        }
}

bool cmp(room a, room b)
{
    return a.checkPrice() <= b.checkPrice();
}

std::vector<room> floor::sortRoomsByPrice(bool ascend)
{
    std::vector<room> ans;
    for(int i = 1; i <= 8; i++)
        for(int j = 0; j < rooms[i].size(); j++)
            ans.push_back(rooms[i][j]);
    if(ascend) std::sort(ans.begin(), ans.end(), cmp);
    else std::sort(ans.begin(), ans.end(), !cmp);
    return ans;
}

std::vector<room> floor::sortAvailableRoomsByPrice(bool ascend)
{
    std::vector<room> ans;
    for(int i = 1; i <= 8; i++)
        for(int j = 0; j < rooms[i].size(); j++)
            if(rooms[i][j].isAvailable()) ans.push_back(rooms[i][j]);
    if(ascend) std::sort(ans.begin(), ans.end(), cmp);
    else std::sort(ans.begin(), ans.end(), !cmp);
    return ans;
}