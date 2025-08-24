#pragma once
#include "person_interface.h"
#include "room.h"
#include <string>

// Fixed enum with explicit positive values
enum class Role {
  None = 0,      // Explicitly set to 0
  Customer = 1,  // Explicitly set to 1
  Employee = 2,  // Explicitly set to 2
  Manager = 3    // Explicitly set to 3
};

class person : public IPerson {
 protected:
  std::string name = "";
  std::string phone = "";
  std::string email = "";
  int id = 0;  // Initialize to prevent garbage values
 public:
  person();
  virtual ~person() = default;
  person(std::string name, std::string phone, std::string email, int id);
  person& operator=(const person& other);

  // Getters
  std::string getPhone();
  std::string getEmail();
  int getID() const override;

  // Setters with validation
  void setName(std::string name);
  bool setPhone(std::string phone);
  bool setEmail(std::string email);
  void setID(int ID);  // Prevent negative IDs

  void showInfo() override;
  std::string getName() override;
};