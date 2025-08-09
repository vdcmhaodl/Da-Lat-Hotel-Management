#pragma once

#include "person.h"
#include "hotel.h"
#include <vector>

class customer : public person
{
  friend class manager;

private:
  int discount = 0;
  int bill = 0;

  // date for booking
  date checkin;
  date checkout;
  room *roomStay = nullptr;
  int calculateNightStays();

public:
  customer();
  virtual ~customer() = default;
  customer(std::string name, std::string phone, std::string email, int id);
  customer &operator=(const customer &other);

  void setCheckinDate(date checkin_date);
  void setCheckoutDate(date checkout_date);
  void showInfo() override;
  std::string getName() override;
 //std::string getPosition() override;
  int getID() const override;

  // New methods for hotel booking functionality
  bool bookRoom(hotel &h, std::string roomID, date checkin_date,
                date checkout_date);
  void viewAvailableRooms(hotel &h);
  bool cancelRoom();
  void showBill();
  bool payBill();

  // Additional utility methods
  int getDiscount() const;
  void setDiscount(int new_discount);
  int getBill() const;
  void setBill(int amount);

  // ALREADY IN CUSTORMER
  // void viewBookingHistory(hotel &h);
  // void showBill(room &a);
  // bool payBill(room &a);

  void saveToFile(std::ofstream& out);
  void loadFromFile(std::ifstream& in, hotel& h);
};