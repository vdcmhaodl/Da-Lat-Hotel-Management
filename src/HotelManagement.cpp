#include "HotelManagement.h"
#include <fstream>

HotelManagementSystem::~HotelManagementSystem()
{
    for (customer *cust : listOfCustormer)
    {
        delete cust; // Free the memory for each customer object
    }
}
void HotelManagementSystem::hireEmployee(IPerson *person)
{
    m.add(person);
}
void HotelManagementSystem::fireEmployee(int id)
{
    m.remove(id);
}
void HotelManagementSystem::viewEmployees()
{
    m.viewEmployeeList();
}
void HotelManagementSystem::addRoom(int flr, int type)
{
    h.addRoom(flr, type);
}
customer *HotelManagementSystem::addCustomer()
{
    std::string name, phone, email;

    std::cin.ignore();

    std::cout << "Enter customer's name: ";
    std::getline(std::cin, name);

    std::cout << "Enter customer's phone: ";
    std::cin >> phone;

    std::cout << "Enter customer's email: ";
    std::cin >> email;

    // Create a new customer object with a unique ID
    customer *newCustomer = new customer(name, phone, email, ++nextCustomerId);
    listOfCustormer.push_back(newCustomer);

    std::cout << "Customer " << newCustomer->getName() << " added with ID " << newCustomer->getID() << "." << std::endl;
    return newCustomer;
}
void HotelManagementSystem::removeCustomer(int id)
{
    for (auto it = listOfCustormer.begin(); it != listOfCustormer.end(); ++it)
    {
        if ((*it)->getID() == id)
        {
            std::cout << "Removing customer: " << (*it)->getName() << " (ID: " << (*it)->getID() << ")." << std::endl;
            delete *it;                // Free the memory of the customer object
            listOfCustormer.erase(it); // Remove the pointer from the vector
            return;                    // Exit the function after finding and removing the customer
        }
    }
    std::cout << "Error: Customer with ID " << id << " not found." << std::endl;
}

void HotelManagementSystem::showCustomer()
{
    for (auto it : listOfCustormer)
    {
        it->showInfo();
    }
}

void HotelManagementSystem::bookRoom(customer *cus)
{
    std::string id;
    std::cout << "=== BOOKING ROOM FOR ";
    std::cout << cus->getName();
    std::cout << "===\n";
    std::cout << "Enter room's id\n";
    std::cin >> id;
    date checkin, checkout;
    std::cout << "Enter the checkin day\n";
    std::cin >> checkin.day >> checkin.month >> checkin.year;
    std::cout << "Enter the checkout day\n";
    std::cin >> checkout.day >> checkout.month >> checkout.year;
    cus->bookRoom(h, id, checkin, checkout);
}

void HotelManagementSystem::showRoom()
{
    h.displayAllRooms();
}

void HotelManagementSystem::removeRoom()
{
    int fl;
    std::string id;
    std::cout << "Enter floor: \n";
    std::cin >> fl;
    std::cout << "Enter id room in that floor: \n";
    std::cin >> id;
    h.removeRoom(fl, id);
    std::cout << "Remove room with" << id << "successfully\n";
}

manager &HotelManagementSystem::getManager()
{
    return m;
}

hotel &HotelManagementSystem::getHotel()
{
    return h;
}

bool HotelManagementSystem::isEmployee(int id)
{
    // Let manager check his employee list
    return m.hasEmployee(id); // You need to implement this in `manager`
}

customer *HotelManagementSystem::getCustomerById(int id)
{
    for (auto *c : listOfCustormer)
    {
        if (c->getID() == id)
            return c;
    }
    return nullptr;
}

void HotelManagementSystem::giveDiscountToCustomer(int custId, int percent)
{
    customer *c = getCustomerById(custId);
    if (c != nullptr)
    {
        c->setDiscount(percent);
        std::cout << "Discount applied.\n";
    }
    else
    {
        std::cout << "Customer not found.\n";
    }
}

customer *HotelManagementSystem::findCustomer(int id)
{
    for (auto it : listOfCustormer)
        if (id == it->getID())
        {
            return it;
        }
    return nullptr;
}

void HotelManagementSystem::saveSystemState()
{
    // Save customers
    std::ofstream outCus("customers.txt");

    if (!outCus)
        return;

    outCus << listOfCustormer.size() << "\n";

    for (auto *c : listOfCustormer)
        c->saveToFile(outCus);
    outCus.close();

    // Save employees
    std::ofstream empOut("employees.txt");
    if (!empOut)
        return;

    std::vector<IPerson *> employeeList = m.getEmployeeList();

    empOut << employeeList.size() << "\n";
    for (auto *p : employeeList)
    {
        employee *e = dynamic_cast<employee *>(p);
        if (e)
        {
            e->saveToFile(empOut);
        }
    }
    empOut.close();

    // save room
    std::ofstream hotelOut("rooms.txt");
    if (!hotelOut)
        return;

    std::vector<floor_> floors = h.getFloors();
    int totalRooms = 0;
    for (auto &f : floors)
    {
        // auto rooms = f.findAllRooms();
        totalRooms += f.getNumRooms();
    }

    hotelOut << totalRooms << '\n';

    for (floor_ &f : floors)
    {
        std::vector<room> getRoomList = f.findAllRooms();

        for (room &r : getRoomList)
        {
            r.saveToFile(hotelOut);
        }
    }

    hotelOut.close();
}

void HotelManagementSystem::updateBaseCustomerId(int n) { 
    nextCustomerId += n - 1;
}

void HotelManagementSystem::loadSystemState()
{
    std::ifstream cusIn("customers.txt");

    if (cusIn)
    {
        int n;
        cusIn >> n;
        updateBaseCustomerId(n);
        cusIn.ignore();

        for (int i = 0; i < n; ++i)
        {
            customer *c = new customer();
            c->loadFromFile(cusIn, h);
            listOfCustormer.push_back(c);
        }
    }

    cusIn.close();

    std::ifstream empIn("employees.txt");
    if (empIn)
    {
        int n;
        empIn >> n;
        empIn.ignore();

        for (int i = 0; i < n; ++i)
        {
            employee *e = new employee();
            e->loadFromFile(empIn);
            m.add(dynamic_cast<IPerson *>(e));
        }
    }
    empIn.close();

    std::ifstream roomIn("rooms.txt");
    if (!roomIn)
        return;

    int count;
    roomIn >> count;    
    roomIn.ignore();

    for (int i = 0; i < count; ++i)
    {
        room *r = new room("temp",0); // temp constructor, will be overwritten
        r->loadFromFile(roomIn);
        r->construct();
        int flr = int ((r->getID())[0] - '0') * 10 + int (r->getID()[1] - '0'); // implement logic to extract floor from ID
        h.addRoomToFloor(flr, *r);
    }

    roomIn.close();
}
