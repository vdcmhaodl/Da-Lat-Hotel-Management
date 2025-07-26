#pragma once

#include "employee.h"
#include <vector>

class manager : public employee 
{
private: 
    std::vector<IPerson*> ListOfEmployees; 
public:
    // mananager_init
    manager();
    manager(const std::string name, const std::string phone,
            const std::string email, const int id, double salary, const std::string position);
    virtual ~manager() = default; 

    // manager_fucntion
    void add(IPerson* person); // hireEmployee
    void remove(int id); // fireEmployee
    void viewEmployeeList();
    void updateEmployeePosition(int id, const std::string& newPosition);
    void generateReport();
    void showInfo() override; 
    std::string getName() override;
    std::string getPosition() override;
    int getID() const override;
};