#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <queue>

#include "room_basic.h"
#include "room_director.h"
#include "room_concrete.h"
#include "room_item.h"

enum status {
  in = 0,  // Explicitly set to 0
  out = 1  // Explicitly set to 1
};

struct service {
  std::string name;
  double cost = 0.0;  // Initialize to prevent garbage values
};

struct date {
  int day = 1;      // Default to valid date
  int month = 1;    // Default to valid month
  int year = 2024;  // Default to current year

  date() = default;
  // Constructor with validation
  date(int d, int m, int y) {
    day = (d < 1 || d > 31) ? 1 : d;
    month = (m < 1 || m > 12) ? 1 : m;
    year = (y < 1900 || y > 2100) ? 2024 : y;
  }
};

struct date_satus {
  date Date;
  status Status = out;  // Default status
  std::string guest = "";

  date_satus() = default;  // Constructor mặc định

  date_satus(date d, status s, std::string g)
      : Date(d), Status(s), guest(std::move(g)) {}
};
class room {
  friend class manager;

 private:
  std::string ID;
  room_basic *roomType;
  std::string typeName;
  int typeNum;

  view View;
  room_item *item;
  double pricePerNight;
  std::string current_guest;   // guest name
  std::string currentGuestId;  // guest id
  std::vector<date_satus> book_history;
  std::vector<date_satus> booking_queue;
  std::vector<service> Service;

  bool locked = false;

 public:
  room();
  room(std::string roomNumber, double pricePerNight);
  room(const room &a);
  room &operator=(const room &a);
  std::string getID() const;
  void construct();
  bool book(std::string guest_name, date checkin_date, date checkout_date);
  bool cancel(std::string guest_name);
  void updatePrice(double price);
  void checkIn(date checkin, std::string cur_guest);
  void checkOut(date checkout);
  bool isAvailable();
  double checkPrice();
  void addService(std::string name, double cost);
  double calculateStayCost();
  void displayInfo();
  void displayBookingHistory();
  void displayBookingQueue();
  int getRoomTypeNumber();

  void lockRoom();
  void unlockRoom();
  bool isLocked() const;
  void setGuest(std::string id);
  std::string getTypeName();
  ~room();

  // loading and saving
  void loadFromFile(std::istream &in);
  void saveToFile(std::ofstream &out);
  void reinitializeRoomType();
};