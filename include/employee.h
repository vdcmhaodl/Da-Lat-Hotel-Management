#pragma once
#include "person.h"
#include "customer.h"
#include "room.h"
#include <vector>
#include <iomanip>

class employee : public person {
  friend class manager;

 private:
  std::string position = "Employee";  // Default position
 protected:
  double salary = 0.0;  // Initialize to prevent garbage values

  void updatePosition(const std::string &newPosition);

 public:
  employee() : person(), salary(0.0), position("Unknown") {}
  employee(std::string name, std::string phone,
           std::string email, int id, bool gender, double salary);
  virtual ~employee() = default;

  void showInfo() override;
  std::string getName() override;
  int getID() const override;

  // Setter with validation
  void setSalary(double sal);

  void giveDiscount(customer &c, int percent);
  void lockRoom(hotel &h, std::string id);
  void unlockRoom(hotel &h, std::string id);

  // Booking history methods for employee
  void viewHotelBookingHistory(const std::vector<customer *> &customers);
  void viewCustomerBookingHistory(customer *cust);
  void viewRoomBookingHistory(hotel &h, std::string roomID);
};