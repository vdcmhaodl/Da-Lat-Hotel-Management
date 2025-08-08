#include "employee.h"
#include "hotel.h"
#include "fstream"

void employee::updatePosition(const std::string &newPosition)
{
  position = newPosition;
}

void employee::showInfo()
{
  std::cout << "Employee " << id << "\n";
  std::cout << "Name: " << name << "\n";
  std::cout << "Phone: " << phone << "\n";
  std::cout << "Email: " << email << "\n";
  std::cout << "Salary: " << salary << "\n";
  std::cout << "Position: " << position << "\n";
}

std::string employee::getName() { return name; }

//std::string employee::getPosition() { return position; }

int employee::getID() const { return id; }

void employee::giveDiscount(customer& c, int percent)
{
  
  if (percent < 0 || percent > 100)
  {
    std::cout << "Discount must be between 0 and 100.\n";
    return;
  }
  c.setDiscount(percent);
  std::cout << "Employee " << getName() << " gave " << percent
            << "% discount to Customer " << c.getName() << ".\n";
}

void employee::lockRoom(hotel& h, std::string id)
{
  room* r = &h.findRoomByNumber(id);
  r->lockRoom();
  std::cout << "Employee " << getName() << " locked room " << r->getID()
            << ".\n";
}

void employee::unlockRoom(hotel& h, std::string id)
{
  room* r = &h.findRoomByNumber(id);
  r->unlockRoom();
  std::cout << "Employee " << getName() << " unlocked room " << r->getID()
            << ".\n";
}

// employee.cpp
void employee::saveToFile(std::ofstream& out) {
    out << name << " " << phone << " " << email << " " << id << " " << salary << "\n";
}

void employee::loadFromFile(std::ifstream& in) {
    in >> name >> phone >> email >> id >> salary;
}
