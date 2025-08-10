#include "employee.h"
#include "hotel.h"
#include "fstream"
#include "iomanip"

void employee::updatePosition(const std::string& newPosition) {
  position = newPosition;
}

void employee::showInfo() {
  std::cout << "Employee " << id << "\n";
  std::cout << "Name: " << name << "\n";
  std::cout << "Phone: " << phone << "\n";
  std::cout << "Email: " << email << "\n";
  std::cout << "Salary: " << salary << "\n";
  std::cout << "Position: " << position << "\n";
}

std::string employee::getName() { return name; }

// std::string employee::getPosition() { return position; }

int employee::getID() const { return id; }

void employee::giveDiscount(customer& c, int percent) {
  if (percent < 0 || percent > 100) {
    std::cout << "Discount must be between 0 and 100.\n";
    return;
  }
  c.setDiscount(percent);
  std::cout << "Employee " << getName() << " gave " << percent
            << "% discount to Customer " << c.getName() << ".\n";
}

void employee::lockRoom(hotel& h, std::string id) {
  room* r = h.findRoomByNumber(id);
  r->lockRoom();
  std::cout << "Employee " << getName() << " locked room " << r->getID()
            << ".\n";
}

void employee::unlockRoom(hotel& h, std::string id) {
  room* r = h.findRoomByNumber(id);
  r->unlockRoom();
  std::cout << "Employee " << getName() << " unlocked room " << r->getID()
            << ".\n";
}

void employee::viewHotelBookingHistory(
    const std::vector<customer*>& customers) {
  std::cout << "\n=== HOTEL BOOKING HISTORY (Employee View) ===\n";
  std::cout << std::string(100, '=') << std::endl;

  if (customers.empty()) {
    std::cout << "No customers found.\n";
    return;
  }

  std::cout << std::left << std::setw(12) << "Customer ID" << std::setw(15)
            << "Customer Name" << std::setw(10) << "Room ID" << std::setw(15)
            << "Room Type" << std::setw(12) << "Check-in" << std::setw(12)
            << "Check-out" << std::setw(10) << "Cost" << std::setw(12)
            << "Status" << std::endl;
  std::cout << std::string(100, '-') << std::endl;

  int totalBookings = 0;
  double totalRevenue = 0;

  for (const auto& customer : customers) {
    auto history = customer->getBookingHistory();

    for (const auto& record : history) {
      std::cout << std::left << std::setw(12) << customer->getID()
                << std::setw(15) << customer->getName() << std::setw(10)
                << record.roomID << std::setw(15) << record.roomTypeName
                << std::setw(12)
                << (std::to_string(record.checkin.day) + "/" +
                    std::to_string(record.checkin.month) + "/" +
                    std::to_string(record.checkin.year))
                << std::setw(12)
                << (std::to_string(record.checkout.day) + "/" +
                    std::to_string(record.checkout.month) + "/" +
                    std::to_string(record.checkout.year))
                << std::setw(10) << ("$" + std::to_string(record.totalCost))
                << std::setw(12) << record.status << std::endl;

      totalBookings++;
      if (record.isPaid) {
        totalRevenue += record.totalCost;
      }
    }
  }

  std::cout << std::string(100, '=') << std::endl;
  std::cout << "Total Bookings: " << totalBookings << std::endl;
  std::cout << "Total Revenue: $" << totalRevenue << std::endl;
  std::cout << std::string(100, '=') << std::endl;
}

// Employee xem booking history của một customer cụ thể
void employee::viewCustomerBookingHistory(customer* cust) {
  if (!cust) {
    std::cout << "Customer not found!\n";
    return;
  }

  std::cout << "\n=== CUSTOMER BOOKING HISTORY (Employee View) ===\n";
  std::cout << "Customer: " << cust->getName() << " (ID: " << cust->getID()
            << ")\n";

  // Gọi method của customer để hiển thị
  cust->viewMyBookingHistory();
}

// Employee xem booking history của một phòng cụ thể
void employee::viewRoomBookingHistory(hotel& h, std::string roomID) {
  room* foundRoom = h.findRoomByNumber(roomID);
  if (!foundRoom) {
    std::cout << "Room " << roomID << " not found!\n";
    return;
  }

  std::cout << "\n=== ROOM BOOKING HISTORY ===\n";
  std::cout << "Room ID: " << roomID << std::endl;
  std::cout << "Room Type: " << foundRoom->getTypeName() << std::endl;
  std::cout << "Current Price: $" << foundRoom->checkPrice() << "/night\n";
  std::cout << std::string(60, '=') << std::endl;

  // Hiển thị booking history của room
  foundRoom->displayBookingHistory();
}

// employee.cpp
void employee::saveToFile(std::ofstream& out) {
  out << name << "," << phone << "," << email << "," << id << "," << salary
      << "\n";
}

void employee::loadFromFile(std::ifstream& in) {
  std::string idStr, salaryStr;

  std::getline(in, name, ',');
  std::getline(in, phone, ',');
  std::getline(in, email, ',');
  std::getline(in, idStr, ',');
  std::getline(in, salaryStr);

  id = std::stoi(idStr);
  salary = std::stod(salaryStr);
}
