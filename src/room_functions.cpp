#include "room.h"

int compareDate(const date& a, const date& b)
{
    if(a.year == b.year)
    {
        if(a.month == b.month)
        {
            if(a.day == b.day) return 0;
            if(a.day < b.day) return -1;
            return 1;
        }
        if(a.month < b.month) return -1;
        return 1;
    }
    if(a.year < b.year) return -1;
    return 1;
}

bool room::book(std::string guest_name, date checkin_date, date checkout_date)
{
    if(booking_queue.empty() || compareDate(booking_queue[booking_queue.size() - 1].Date, checkin_date) == -1)
    {
        date_satus temp{checkin_date, in, guest_name};
        booking_queue.push_back(temp);
        temp.Date = checkout_date;
        temp.Status = out;
        booking_queue.push_back(temp);
        return 1;
    }
    if(compareDate(checkout_date, booking_queue[0].Date) == -1)
    {
        date_satus temp{checkout_date, out, guest_name};
        booking_queue.insert(booking_queue.begin() + 1, temp);
        temp.Date = checkin_date;
        temp.Status = in;
        booking_queue.insert(booking_queue.begin() + 1, temp);
        return 1;
    }
    int n = booking_queue.size();
    int indx = 1;
    for(int i = 1; i < n - 2; i += 2)
    {
        if(compareDate(booking_queue[i].Date, checkin_date) == -1 && (i + 1 == n || compareDate(checkout_date, booking_queue[i + 1].Date) == -1))
        { 
            date_satus temp{checkout_date, out, guest_name};
            booking_queue.insert(booking_queue.begin() + i + 1, temp);
            temp.Date = checkin_date;
            temp.Status = in;
            booking_queue.insert(booking_queue.begin() + i + 1, temp);
            return 1;
        }
    }
    return 0;
}

bool room::cancel(std::string guest_name)
{
    int n = booking_queue.size();
    for(int i = 0; i < n; i += 2)
        if(booking_queue[i].guest == guest_name)
        {
            booking_queue.erase(booking_queue.begin() + i, booking_queue.begin() + i + 1);
            return 1;
        }
    return 1;
}

void room::checkIn(date checkin, std::string cur_guest)
{
    this->current_guest = cur_guest;
    this->isOccupied = 1;


    date_satus temp;
    temp.Date = checkin;
    temp.Status = in;
    temp.guest = cur_guest;
    this->book_history.push_back(temp);
}

void room::checkOut(date checkout)
{
    this->isOccupied = 0;

    date_satus temp;
    temp.Date = checkout;
    temp.Status = out;
    temp.guest = this->current_guest;
    this->book_history.push_back(temp);
    this->Service.clear();
    this->current_guest = "";
}

bool room::isAvailable() { return !(this->isOccupied); }

void room::addService(std::string name, double cost)
{
    service temp;
    temp.name = name;
    temp.cost = cost;
    this->Service.push_back(temp);
}

double room::calculateStayCost()
{
    int cost = 0;
    for(int i = 0; i < this->Service.size(); i++)
        cost += this->Service[i].cost;
    return cost;
}

void room::displayInfo()
{
    std::cout << "Room number: " << this->ID << '\n';
    std::cout << "Room type: " << this->typeName << '\n';
    std::cout << "Price: " << this->pricePerNight << '\n';
    std::cout << "Room status: " << ((this->isAvailable()) ? "Available" : "Not available") << '\n';
}

void room::updatePrice(double price) { this->pricePerNight = price; }

std::string room::getID() { return this->ID; }

double room::checkPrice() { return this->pricePerNight; }

int main()
{
    room temp("02411", 200000);
    temp.checkIn({26, 7, 2025}, "HaoVo");
    temp.checkOut({28, 7, 2025});
    temp.displayInfo();
    return 0;
}