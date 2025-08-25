#pragma once
#include "person.h"
#include "hotel.h"
#include <vector>
#include <sstream>

struct booking_record
{
  std::string roomID = "";
  std::string roomTypeName = "";
  date checkin;
  date checkout;
  int totalCost = 0; // Initialize to prevent garbage values
  bool isPaid = false;
  date bookingDate;
  std::string status = "Current";

  // Constructor with validation
  booking_record()
      : checkin(1, 1, 2024), checkout(1, 1, 2024), bookingDate(1, 1, 2024)
  {
    totalCost = (totalCost < 0) ? 0 : totalCost;
  }
};

struct current_booking
{
  std::string roomID = "";
  room *roomPtr = nullptr;
  date checkin;
  date checkout;
  int bill = 0; // Initialize to prevent garbage values

  // Constructor with validation
  current_booking() : checkin(1, 1, 2024), checkout(1, 1, 2024)
  {
    bill = (bill < 0) ? 0 : bill;
  }
};

class customer : public person
{
  friend class manager;

private:
  int discount = 0; // Initialize to prevent garbage values
  std::vector<current_booking> currentBookings;
  std::vector<booking_record> bookingHistory;

  int calculateNightStays(date checkin, date checkout);

public:
  customer();
  virtual ~customer() = default;
  customer(std::string name, std::string phone, std::string email, int id, bool gender);
  customer &operator=(const customer &other);

  void showInfo() override;
  std::string getName() override;
  int getID() const override;

  // Booking methods
  bool bookRoom(hotel &h, std::string roomID, date checkin_date,
                date checkout_date);
  void viewAvailableRooms(hotel &h);
  void viewAllRooms(hotel &h);
  bool cancelRoom(std::string roomID);
  void showBill();
  bool payBill(std::string roomID);
  void showCurrentBookings();

  // Booking history methods
  void addBookingRecord(const booking_record &record);
  void viewMyBookingHistory();
  std::vector<booking_record> getBookingHistory() const;
  void updateBookingStatus(std::string roomID, date checkin,
                           std::string newStatus);

  // Utility methods with validation
  int getDiscount() const;
  void setDiscount(int new_discount);
  int getTotalBill() const;
  std::vector<current_booking> getCurrentBookings() const;

  void saveToFile(std::ofstream &out);
  void loadFromFile(std::ifstream &in, hotel &h);
};