#include "room.h"
#include "fstream"
#include <string> 
#include "init_price_type.h"

int compareDate(const date &a, const date &b) {
  if (a.year == b.year) {
    if (a.month == b.month) {
      if (a.day == b.day) return 0;
      if (a.day < b.day) return -1;
      return 1;
    }
    if (a.month < b.month) return -1;
    return 1;
  }
  if (a.year < b.year) return -1;
  return 1;
}

bool room::book(std::string guest_name, date checkin_date, date checkout_date) {
  if (booking_queue.empty() ||
      compareDate(booking_queue[booking_queue.size() - 1].Date, checkin_date) ==
          -1) {
    date_satus temp{checkin_date, in, guest_name};
    booking_queue.push_back(temp);
    temp.Date = checkout_date;
    temp.Status = out;
    booking_queue.push_back(temp);
    return 1;
  }
  if (compareDate(checkout_date, booking_queue[0].Date) == -1) {
    date_satus temp{checkout_date, out, guest_name};
    booking_queue.insert(booking_queue.begin() + 1, temp);
    temp.Date = checkin_date;
    temp.Status = in;
    booking_queue.insert(booking_queue.begin() + 1, temp);
    return 1;
  }
  int n = booking_queue.size();
  int indx = 1;
  for (int i = 1; i < n - 2; i += 2) {
    if (compareDate(booking_queue[i].Date, checkin_date) == -1 &&
        (i + 1 == n ||
         compareDate(checkout_date, booking_queue[i + 1].Date) == -1)) {
      date_satus temp{checkout_date, out, guest_name};
      booking_queue.insert(booking_queue.begin() + i + 1, temp);
      temp.Date = checkin_date;
      temp.Status = in;
      booking_queue.insert(booking_queue.begin() + i + 1, temp);
      return 1;
    }
  }
  return 0;
}

bool room::cancel(std::string guest_name) {
  int n = booking_queue.size();
  for (int i = 0; i < n; i += 2)
    if (booking_queue[i].guest == guest_name) {
      booking_queue.erase(booking_queue.begin() + i,
                          booking_queue.begin() + i + 2);
      return 1;
    }
  return 0;  // not found
}

void room::checkIn(date checkin, std::string cur_guest) {
  this->current_guest = cur_guest;
  this->locked = true;

  date_satus temp;
  temp.Date = checkin;
  temp.Status = in;
  temp.guest = cur_guest;
  this->book_history.push_back(temp);
}

void room::checkOut(date checkout) {
  this->locked = false;

  date_satus temp;
  temp.Date = checkout;
  temp.Status = out;
  temp.guest = this->current_guest;
  this->book_history.push_back(temp);
  this->Service.clear();
  this->current_guest = "";
}

void room::addService(std::string name, double cost) {
  service temp;
  temp.name = name;
  temp.cost = cost;
  this->Service.push_back(temp);
}

double room::calculateStayCost() {
  double cost = 0;
  for (int i = 0; i < this->Service.size(); i++) cost += this->Service[i].cost;
  return cost;
}

void room::displayInfo() {
  std::cout << "Room number: " << this->ID << '\n';
  std::cout << "Room type: " << this->typeName << '\n';
  std::cout << "Price: " << this->pricePerNight << '\n';
  std::cout << "Room status: "
            << ((this->isAvailable()) ? "Available" : "Not available") << '\n';
}

void room::displayFurniture()
{
    std::cout << "----Room " << this->ID << "'s furnitures----\n";
    room_basic* temp = this->roomType;
    if(this->roomType->getSingle_beds() != 0) std::cout << "Single beds: " << temp->getSingle_beds() << '\n';
    else std::cout << "Large beds: " << temp->getLarge_beds() << '\n';
    std::cout << "Bathrooms: " << temp->getBathrooms() << '\n';
    if(temp->getBath()) std::cout << "Room has bath\n";
    else std::cout << "Room does not have bath\n";
    std::cout << "TV: " << temp->getTV();
    if(temp->getBalcol()) std::cout << "Room has balcony\n";
    else std::cout << "Room does not have balcony\n";
    if(temp->getLoving_chair()) std::cout << "Room have loving chair\n";
    else std::cout << "Room does not have loving chair\n";
    std::cout << "Room have fridge\n";
    std::cout << "Rooms: " << temp->getRooms() << '\n';
}

void room::displayItem()
{
    room_item *temp = this->item;
    std::cout << "----Room " << this->ID << "'s items---- \n";
    std::cout << "Towels: " << temp->getTowel() << '\n';
    std::cout << "Sleep dresses: " << temp->getSleep_dress() << '\n';
    std::cout << "Sandals: " << temp->getSandals() << '\n';
    std::cout << "Hair dryers: " << temp->getHair_dryer() << '\n';
}

#include <string> 

std::string room::displayAmenties() { 
  room_item *temp = this->item;
    return "Towels: " + std::to_string(temp->getTowel()) +
     ", Sleep dresses: " + std::to_string(temp->getSleep_dress()) + 
    ", Sandals: " + std::to_string(temp->getSandals()) + '\n' +
    ", Hair dryers: " + std::to_string(temp->getHair_dryer()) + '\n';
}

void room::updatePrice(double price) { this->pricePerNight = price; }

std::string room::getID() const { return this->ID; }

double room::checkPrice() { return this->pricePerNight; }

void room::displayBookingHistory() {
  std::cout << "Display booking queue: \n";
  std::cout << "Size of queue: " << booking_queue.size() << std::endl;
  for (auto it : booking_queue) {
    std::cout << it.guest << " " << it.Date.day << "/" << it.Date.month << "/"
              << it.Date.year << std::endl;
  }
}

void room ::displayBookingQueue() {
  std::cout << "Display booking queue: \n";
  for (auto it : booking_queue) {
    std::cout << it.guest << " " << (it.Status == in ? "checkin" : "checkout")
              << " " << it.Date.day << "/" << it.Date.month << "/"
              << it.Date.year << std::endl;
  }
}

void room::lockRoom() {
  locked = true;
  std::cout << "Room " << ID << " has been locked.\n";
}

void room::unlockRoom() {
  locked = false;
  current_guest = "";
  currentGuestId = "";
  std::cout << "Room " << ID << " has been unlocked.\n";
}
bool room::isLocked() const { return locked; }

bool room::isAvailable() { return !locked; }

std::string room::getTypeName() { return typeName; }

void room::loadFromFile(std::istream &in) {
  std::string typeNumStr, priceStr, viewStr, lockStr, guest;

  std::getline(in, ID, ',');
  std::getline(in, typeNumStr, ',');
  std::getline(in, priceStr, ',');
  std::getline(in, viewStr, ',');
  std::getline(in, lockStr, ',');
  std::getline(in, guest);

  int typeNum = std::stoi(typeNumStr);
  pricePerNight = std::stod(priceStr);
  View = static_cast<view>(std::stoi(viewStr));
  locked = (std::stoi(lockStr) == 1);
  currentGuestId = guest;
  this->typeNum = typeNum;
}

int room::getRoomTypeNumber() { return typeNum; }

void room::setGuest(std::string id) { currentGuestId = id; }

std::string room::getCurrentGuest() {
  return currentGuestId;  
}

void room::saveToFile(std::ofstream &out) {
  out << ID << "," << typeNum << "," << pricePerNight << ","
      << static_cast<int>(View) << "," << locked << "," << currentGuestId
      << "\n";
}