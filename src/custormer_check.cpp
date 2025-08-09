#include "customer.h"

/* bool customer::checkBookingHistory(std::string roomID)
{
    for (auto &Room : booking_history)
    {
        if (Room.getID() == roomID)
        {
            return true;
        }
    }
    return false;
}*/
 
/*
bool customer::checkBookingQueue(std::string roomID)
{
    for (auto &Room : booking_queue)
    {
        if (Room.getID() == roomID)
        {
            return true;
        }
    }
    return false;
}*/

// int customer::calculateNightStays()
// {
//     if (checkout.year < checkin.year ||
//         (checkout.year == checkin.year && checkout.month < checkin.month) ||
//         (checkout.year == checkin.year && checkout.month == checkin.month && checkout.day < checkin.day))
//     {
//         return 0; // Invalid date range
//     }

//     int nights = 0;
//     while (checkin.year < checkout.year ||
//            (checkin.year == checkout.year && checkin.month < checkout.month) ||
//            (checkin.year == checkout.year && checkin.month == checkout.month && checkin.day < checkout.day))
//     {
//         nights++;
//         if (++checkin.day > 30)
//         {
//             checkin.day = 1;
//             if (++checkin.month > 12)
//             {
//                 checkin.month = 1;
//                 checkin.year++;
//             }
//         }
//     }
//     return nights;
// }