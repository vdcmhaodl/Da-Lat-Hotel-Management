#pragma once

#include "person.h"
#include "hotel.h"
#include <vector>

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

class customer : public person {
  friend class manager;

 private:
  int discount = 0;
  int bill = 0;

  // date for booking
  date checkin;
  date checkout;
  room *roomStay = nullptr;

  // Lịch sử booking của customer
  std::vector<booking_record> bookingHistory;

  int calculateNightStays();

 public:
  customer();
  virtual ~customer() = default;
  customer(std::string name, std::string phone, std::string email, int id, bool gender);
  customer &operator=(const customer &other);

  void setCheckinDate(date checkin_date);
  void setCheckoutDate(date checkout_date);
  void showInfo() override;
  std::string getName() override;
  int getID() const override;

  // New methods for hotel booking functionality
  bool bookRoom(hotel &h, std::string roomID, date checkin_date,
                date checkout_date);
  void viewAllRooms(hotel &h);
  bool cancelRoom();
  void showBill();
  bool payBill();

  // Booking history methods
  void addBookingRecord(const booking_record &record);
  void viewMyBookingHistory();  // Customer xem lịch sử của chính mình
  std::vector<booking_record> getBookingHistory() const;
  void updateBookingStatus(std::string roomID, date checkin,
                           std::string newStatus);

  // Additional utility methods
  int getDiscount() const;
  void setDiscount(int new_discount);
  int getBill() const;
  void setBill(int amount);

  void saveToFile(std::ofstream &out);
  void loadFromFile(std::ifstream &in, hotel &h);
};