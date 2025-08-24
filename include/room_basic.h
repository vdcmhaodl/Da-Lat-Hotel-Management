#pragma once
#include <string>

// Fixed enum with explicit positive values
enum view {
  city = 0,   // Explicitly set to 0 (positive)
  nature = 1  // Explicitly set to 1 (positive)
};

class room_basic {
 private:
  int single_beds = 0;  // Initialize to prevent garbage values
  int large_beds = 0;
  int bathrooms = 1;  // At least 1 bathroom
  bool bath = false;
  int TV = 0;
  bool balcol = false;
  bool loving_chair = false;
  bool fridge = false;
  int rooms = 1;  // At least 1 room
 public:
  room_basic();
  room_basic(room_basic& a);

  // Setters with validation
  void setSingle_beds(int num);
  void setLarge_beds(int num);
  void setBathrooms(int num);
  void setBath(bool flag);
  void setTV(int num);
  void setBalcol(bool flag);
  void setLoving_chair(bool flag);
  void setFridge(bool flag);
  void setRooms(int num);

  // Getters
  int getSingle_beds();
  int getLarge_beds();
  int getBathrooms();
  bool getBath();
  int getTV();
  bool getBalcol();
  bool getLoving_chair();
  bool getFridge();
  int getRooms();
};

class room_item {
 private:
  int towel = 0;
  int sleep_dress = 0;
  int sandals = 0;
  int hair_dryer = 0;

 public:
  room_item();
  room_item(room_item& a);

  // Setters with validation
  void setTowel(int num);
  void setHair_dryer(int num);
  void setSleep_dress(int num);
  void setSandals(int num);

  // Getters
  int getTowel();
  int getHair_dryer();
  int getSleep_dress();
  int getSandals();
};