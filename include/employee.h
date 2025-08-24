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
  employee();
  employee(const std::string name, const std::string phone,
           const std::string email, const int id, const bool gender, double salary);
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