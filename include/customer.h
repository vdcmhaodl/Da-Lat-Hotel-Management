#pragma once

#include "person.h"
#include "hotel.h"
#include <vector>

class customer : public person {
  friend class manager;

 private:
  int discount = 0;
  int bill = 0;

  // date for booking
  date checkin;
  date checkout;

  // Booking history
  //  std::vector<room> booking_history;
  // bool checkBookingHistory(std::string roomID);

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
  std::string getPosition() override;
  int getID() const override;

  // New methods for hotel booking functionality
  bool bookRoom(hotel &h, std::string roomID, date checkin_date,
                date checkout_date);
  void viewAvailableRooms(hotel &h);
  bool cancelRoom(hotel &h, std::string roomID);
  void showBill();
  bool payBill();

  // Additional utility methods
  int getDiscount() const;
  void setDiscount(int new_discount);
  int getBill() const;
  void setBill(int amount);

  // WAITING FOR HOTEL AND ROOM TO COMPLETE
  // void viewBookingHistory(hotel &h);
  // void showBill(room &a);
  // bool payBill(room &a);
};