// Additional methods for GUI integration
// Add these methods to hotel.h and implement in hotel.cpp

/*
// Add to hotel class in hotel.h:

public:
    // GUI helper methods
    int getTotalRooms() const;
    int getAvailableRooms() const;
    int getOccupiedRooms() const;
    std::vector<room*> getAllRoomPointers();
    
// Add to floor_ class in hotel.h:

public:
    // GUI helper methods  
    std::vector<room*> getAllRoomPointers();
    int getTotalRoomsInFloor() const;
    int getAvailableRoomsInFloor() const;
*/

// Implementation suggestions for hotel.cpp:

/*
int hotel::getTotalRooms() const {
    int total = 0;
    for (const auto& floor : Floor) {
        total += floor.getTotalRoomsInFloor();
    }
    return total;
}

int hotel::getAvailableRooms() const {
    int available = 0;
    for (const auto& floor : Floor) {
        available += floor.getAvailableRoomsInFloor();
    }
    return available;
}

int hotel::getOccupiedRooms() const {
    return getTotalRooms() - getAvailableRooms();
}

std::vector<room*> hotel::getAllRoomPointers() {
    std::vector<room*> allRooms;
    for (auto& floor : Floor) {
        std::vector<room*> floorRooms = floor.getAllRoomPointers();
        allRooms.insert(allRooms.end(), floorRooms.begin(), floorRooms.end());
    }
    return allRooms;
}

int floor_::getTotalRoomsInFloor() const {
    return num_rooms;
}

int floor_::getAvailableRoomsInFloor() const {
    int available = 0;
    for (int type = 1; type <= 8; ++type) {
        for (const auto& room : rooms[type]) {
            if (room.isAvailable()) {
                available++;
            }
        }
    }
    return available;
}

std::vector<room*> floor_::getAllRoomPointers() {
    std::vector<room*> roomPtrs;
    for (int type = 1; type <= 8; ++type) {
        for (auto& room : rooms[type]) {
            roomPtrs.push_back(&room);
        }
    }
    return roomPtrs;
}
*/
