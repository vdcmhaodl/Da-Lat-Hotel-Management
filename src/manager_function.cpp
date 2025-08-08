#include "manager.h"
#include <vector>
#include <iostream>
#include <algorithm>

void manager::add(IPerson* person)
{
    // If the pointer points to a custormer, no operation
    if (dynamic_cast<employee *>(person))
    {
        ListOfEmployees.push_back(person);
    }
    else
    {
        // Error !
        std::cout << "Only Employees can be managed by Manager.\n";
    }
}
void manager::remove(int id)
{
    auto it = std::remove_if(ListOfEmployees.begin(), ListOfEmployees.end(),
                             [id](IPerson *p)
                             {
                                 return p->getID() == id;
                             });
    if (it != ListOfEmployees.end())
    {
        std::cout << "Removed employee with ID: " << id << " successfully.\n";
        ListOfEmployees.erase(it, ListOfEmployees.end());
    }
    else
    {
        std::cout << "Employee with ID: " << id << " not found.\n";
    }
}
void manager::viewEmployeeList()
{
    std::cout << "=====================\n";
    std::cout << "List of Employees:" << std::endl;
    for (auto person : ListOfEmployees)
    {
        std::cout << "------------------\n";
        employee *emp = dynamic_cast<employee *>(person);
        if (emp)
        {
            emp->showInfo();
        }
        else
        {
            // If Error in casting
            std::cout << "Not an employee.\n";
        }
    }
    std::cout << "=====================\n";
}

void manager::updateEmployeePosition(int id, const std::string &newPosition)
{
    for (auto it : ListOfEmployees)
    {
        employee *emp = dynamic_cast<employee *>(it);
        if (emp->getID() == id)
        {
            emp->updatePosition(newPosition);
            std::cout << "Updated position for employee id:" << id << " to " << newPosition << std::endl;
            return;
        }
    }
    std::cout << "Employee with ID " << id << " not found." << std::endl;
}
void manager::generateReport()
{
    std::cout << "Number of Employees: " << ListOfEmployees.size() << std::endl;
    for (auto it : ListOfEmployees)
    {
        employee *emp = dynamic_cast<employee *>(it);
        emp->showInfo();
        std::cout << "\n";
    }
    /* Additional things will be added here:
    + Average, mininum, maximum salary employees
    + Total number of rooms available
    + Total number of rooms booked
    + Total revenue generated from bookings
    */
}

void manager::showInfo()
{
    std::cout << "Manager " << id << ":\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Phone: " << phone << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "Salary: " << salary << "\n";
    std::cout << "Position: " << position << "\n";
}

std::string manager::getName()
{
    return name;
}

int manager::getID() const
{
    return id;
}

bool manager::hasEmployee(int id) {
    for (auto p : ListOfEmployees) {
        if (p->getID() == id) return true;
    }
    return false;
}

std::vector<IPerson*> manager::getEmployeeList() { 
    return ListOfEmployees;
}