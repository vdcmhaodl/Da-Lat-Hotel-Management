#include "hotel.h"

hotel::hotel() { this->num_floor = 0; }

hotel::hotel(int flr) {
  this->num_floor = flr;
  for (int i = 0; i < flr; i++) {
    floor_ temp(i);
    this->Floor.push_back(temp);
  }
}

void hotel::updatePrice(int roomType, double price) {
  for (int i = 0; i < num_floor; i++) Floor[i].updateRoomPrice(roomType, price);
}

void hotel::addRoom(int flr, int type) { Floor[flr].addRoom(type); }

void hotel::removeRoom(int flr, std::string ID) { Floor[flr].removeRoom(ID); }

void hotel::addFloor() {
  num_floor++;
  floor_ temp(num_floor);
  Floor.push_back(temp);
}

void hotel::addFloor(floor_ fl) {
  num_floor++;
  Floor.push_back(fl);
}

room* hotel::findRoomByNumber(std::string ID) {
  int findFl = int(ID[0] - '0') * 10 + int(ID[1] - '0');
  std::cout << findFl << std::endl;
  if (findFl >= 0 && findFl < num_floor)
    return Floor[findFl].findRoomByNumber(ID);
  return nullptr;
}

std::vector<floor_> hotel::findRoomsByType(int type) {
  std::vector<floor_> ans;
  for (int i = 0; i < num_floor; i++) {
    floor_ temp(i, Floor[i].findRoomsByType(type), type);
    ans.push_back(temp);
  }
  return ans;
}

void hotel::displayAllFloorRooms(int flr) {
  std::cout << "Floor " << flr << ":\n";
  Floor[flr].displayAllFloorRooms();
}

void hotel::displayAllRooms() {
  for (int i = 0; i < num_floor; i++) {
    std::cout << "Floor " << i << ":\n";
    Floor[i].displayAllFloorRooms();
  }
}

std::vector<room> hotel::sortFloorRoomByPrice(int flr, bool ascend) {
  return Floor[flr].sortRoomsByPrice(ascend);
}

std::vector<floor_> hotel::sortRoomsByPrice(bool ascend) {
  std::vector<floor_> ans;
  for (int i = 0; i < num_floor; i++) {
    floor_ temp(i, Floor[i].sortRoomsByPrice(ascend), 0);
    ans.push_back(temp);
  }
  return ans;
}

std::vector<floor_> hotel::sortAvailableRoomByPrice(bool ascend) {
  std::vector<floor_> ans;
  for (int i = 0; i < num_floor; i++) {
    floor_ temp(i, Floor[i].sortAvailableRoomsByPrice(ascend), 0);
    ans.push_back(temp);
  }
  return ans;
}

std::vector<floor_> hotel::findAvailableRooms() {
  std::vector<floor_> ans;
  for (int i = 0; i < Floor.size(); i++) {
    floor_ temp(i, Floor[i].findAvailableRooms(), 0);
    ans.push_back(temp);
  }
  return ans;
}

void hotel::displayAllAvailableRooms() {
  std::vector<floor_> availableRooms = this->findAvailableRooms();
  for (int i = 0; i < availableRooms.size(); i++) {
    std::cout << "Floor " << i << ": \n";
    availableRooms[i].displayAllFloorRooms();
  }
}

void hotel::addRoomToFloor(int flr, room& r) {
  if (flr >= 0 && flr < num_floor)
    Floor[flr].addRoom(r);
  else
    std::cout << "Invalid floor and room!\n";
  return;
}

std::vector<floor_> hotel::getFloors() const { return Floor; }

void hotel::saveToFile(std::ofstream& out) {
  std::cout << "DEBUG: Saving hotel with " << num_floor << " floors\n";
  out << num_floor << "\n";

  for (int i = 0; i < num_floor; i++) {
    std::cout << "DEBUG: Saving floor " << i << "\n";

    // Get all rooms from this floor
    std::vector<room> allRooms = Floor[i].findAllRooms();
    std::cout << "DEBUG: Floor " << i << " has " << allRooms.size()
              << " rooms\n";

    // Save number of rooms in this floor
    out << allRooms.size() << "\n";

    // Save each room
    for (const auto& currentRoom : allRooms) {
      std::cout << "DEBUG: Saving room " << currentRoom.getID() << "\n";
      const_cast<room&>(currentRoom).saveToFile(out);
    }
  }
  std::cout << "DEBUG: Hotel save completed\n";
}

void hotel::loadFromFile(std::ifstream& in) {
  std::cout << "DEBUG: Starting hotel load\n";

  // Clear existing floors
  Floor.clear();

  // Read number of floors
  if (!(in >> num_floor)) {
    std::cout << "DEBUG: Failed to read num_floor\n";
    throw std::runtime_error("Failed to read number of floors");
  }
  in.ignore();  // ignore newline

  std::cout << "DEBUG: Loading hotel with " << num_floor << " floors\n";

  // Initialize floors
  for (int i = 0; i < num_floor; i++) {
    Floor.push_back(floor_(i));
  }

  // Load each floor
  for (int i = 0; i < num_floor; i++) {
    std::cout << "DEBUG: Loading floor " << i << "\n";

    int numRooms;
    if (!(in >> numRooms)) {
      std::cout << "DEBUG: Failed to read numRooms for floor " << i << "\n";
      throw std::runtime_error("Failed to read number of rooms for floor " +
                               std::to_string(i));
    }
    in.ignore();  // ignore newline

    std::cout << "DEBUG: Floor " << i << " should have " << numRooms
              << " rooms\n";

    // Load each room in this floor
    for (int j = 0; j < numRooms; j++) {
      std::cout << "DEBUG: Loading room " << j << " in floor " << i << "\n";

      try {
        room newRoom;
        newRoom.loadFromFile(in);

        std::cout << "DEBUG: Room loaded, ID: " << newRoom.getID() << "\n";

        // Construct room features based on type
        newRoom.construct();

        // Add room to floor - check if addRoom(room&) method exists
        Floor[i].addRoom(newRoom);

        std::cout << "DEBUG: Room " << newRoom.getID() << " added to floor "
                  << i << "\n";

      } catch (const std::exception& e) {
        std::cout << "DEBUG: Error loading room " << j << " in floor " << i
                  << ": " << e.what() << "\n";
        throw;
      }
    }

    std::cout << "DEBUG: Floor " << i << " loaded with "
              << Floor[i].getNumRooms() << " rooms\n";
  }

  std::cout << "DEBUG: Hotel load completed\n";
}