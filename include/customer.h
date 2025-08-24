#pragma once

#include "person.h"
#include "hotel.h"
#include <vector>

struct BookedRoom {
  std::string roomID;
  room* roomPtr;
  date checkin;
  date checkout;
  int bill;
  int nightStays;
};

class customer : public person {
  friend class manager;

 private:
  int discount = 0;
  std::vector<BookedRoom> bookedRooms;
  int calculateNightStays(date checkin, date checkout);

 public:
  customer();
  virtual ~customer() = default;
  customer(std::string name, std::string phone, std::string email, int id);
  customer& operator=(const customer& other);

  void showInfo() override;
  std::string getName() override;
  int getID() const override;

  bool bookRoom(hotel& h, std::string roomID, date checkin_date,
                date checkout_date);
  void viewAvailableRooms(hotel& h);
  bool cancelRoom(std::string roomID);
  void showBill();
  bool payBill(std::string roomID);
  void viewBookedRooms();

  int getDiscount() const;
  void setDiscount(int new_discount);
  int getTotalBill() const;
  BookedRoom* findBookedRoom(std::string roomID);

  void saveToFile(std::ofstream& out);
  void loadFromFile(std::ifstream& in, hotel& h);
};