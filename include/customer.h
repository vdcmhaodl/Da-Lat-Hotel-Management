#pragma once

#include "person.h"
#include "hotel.h"
#include <vector>
#include <sstream>

// Struct để lưu thông tin booking history
struct booking_record {
  std::string roomID;
  std::string roomTypeName;
  date checkin;
  date checkout;
  int totalCost;
  bool isPaid;
  date bookingDate;    // Ngày đặt phòng
  std::string status;  // "Completed", "Cancelled", "Current"
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

  // Vector lưu các phòng đang được book
  std::vector<current_booking> currentBookings;

  // Lịch sử booking của customer
  std::vector<booking_record> bookingHistory;

  int calculateNightStays(date checkin, date checkout);

 public:
  customer();
  virtual ~customer() = default;
  customer(std::string name, std::string phone, std::string email, int id);
  customer &operator=(const customer &other);

  void showInfo() override;
  std::string getName() override;
  int getID() const override;

  // New methods for hotel booking functionality
  bool bookRoom(hotel &h, std::string roomID, date checkin_date,
                date checkout_date);
  void viewAvailableRooms(hotel &h);
  bool cancelRoom(std::string roomID);
  void showBill();
  bool payBill(std::string roomID);
  void showCurrentBookings();

  // Booking history methods
  void addBookingRecord(const booking_record &record);
  void viewMyBookingHistory();  // Customer xem lịch sử của chính mình
  std::vector<booking_record> getBookingHistory() const;
  void updateBookingStatus(std::string roomID, date checkin,
                           std::string newStatus);

  // Additional utility methods
  int getDiscount() const;
  void setDiscount(int new_discount);
  int getTotalBill() const;
  std::vector<current_booking> getCurrentBookings() const;

  void saveToFile(std::ofstream &out);
  void loadFromFile(std::ifstream &in, hotel &h);
};