#pragma once

#include "person.h"
#include "customer.h"
#include "room.h"
#include <vector>
#include <iomanip>

// Forward declaration
class HotelManagementSystem;

class employee : public person {
  friend class manager;

 private:
  std::string position;

 protected:
  double salary;
  void updatePosition(
      const std::string &
          newPosition);  // Only Manager can update position (the derived class)
 public:
  employee();
  employee(const std::string name, const std::string phone,
           const std::string email, const int id, double salary);
  virtual ~employee() = default;

  void showInfo() override;
  std::string getName() override;
  int getID() const override;

  void giveDiscount(customer &c, int percent);
  void lockRoom(hotel &h, std::string id);
  void unlockRoom(hotel &h, std::string id);

  // Booking history methods for employee
  void viewHotelBookingHistory(const std::vector<customer *> &customers);
  void viewCustomerBookingHistory(customer *cust);
  void viewRoomBookingHistory(hotel &h, std::string roomID);
};