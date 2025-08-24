#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <queue>

#include "room_basic.h"
#include "room_director.h"
#include "room_concrete.h"
#include "room_item.h"


enum status
{
  in,
  out
};

struct service
{
  std::string name;
  double cost;
};

struct date
{
  int day;
  int month;
  int year;
};

struct date_satus
{
  date Date;
  status Status;
  std::string guest;
};

class room
{
  friend class manager;

private:
  std::string ID;
  room_basic *roomType;
  std::string typeName;
  int typeNum;

  view View;
  room_item *item;
  double pricePerNight;
  std::string current_guest; // guest name
   std::string currentGuestId; // guest id
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

  void displayFurniture();
  void displayItem();
  
  void lockRoom();
  void unlockRoom();
  bool isLocked() const;
  void setGuest(std::string id);
  std::string getTypeName();
  ~room();

  // loading and saving
  void loadFromFile(std::istream& in);
  void saveToFile(std::ofstream& out);
};