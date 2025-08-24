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

// Struct để lưu thông tin phòng hiện tại đang book
struct current_booking {
  std::string roomID;
  room *roomPtr;
  date checkin;
  date checkout;
  int bill;
};

class customer : public person {
  friend class manager;

 private:
  int discount = 0;
<<<<<<< Updated upstream
  std::vector<BookedRoom> bookedRooms;
=======

  // Vector lưu các phòng đang được book
  std::vector<current_booking> currentBookings;

  // Lịch sử booking của customer
  std::vector<booking_record> bookingHistory;

>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
  void viewAvailableRooms(hotel& h);
  bool cancelRoom(std::string roomID);
  void showBill();
  bool payBill(std::string roomID);
  void viewBookedRooms();
=======
  void viewAvailableRooms(hotel &h);
  bool cancelRoom(std::string roomID);
  void showBill();
  bool payBill(std::string roomID);
  void showCurrentBookings();
>>>>>>> Stashed changes

  int getDiscount() const;
  void setDiscount(int new_discount);
  int getTotalBill() const;
<<<<<<< Updated upstream
  BookedRoom* findBookedRoom(std::string roomID);
=======
  std::vector<current_booking> getCurrentBookings() const;
>>>>>>> Stashed changes

  void saveToFile(std::ofstream& out);
  void loadFromFile(std::ifstream& in, hotel& h);
};