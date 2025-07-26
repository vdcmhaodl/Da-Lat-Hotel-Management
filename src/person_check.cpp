#include "person.h"

bool checkchar(const char a)
{
    return ((a >= 'a' && a <= 'z') ||
            (a >= 'A' && a <= 'Z') ||
            (a >= '0' && a <= '9'));
}