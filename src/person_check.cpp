#include "person.h"

bool checkchar(const char a)
{
    return ((a >= 'a' && a <= 'z') ||
            (a >= 'A' && a <= 'Z') ||
            (a >= '0' && a <= '9'));
}

bool person::checkEmail()
{
    const char* forbid = "()[]{},;:<>?!$%^&*`~=\\\"\'/ ";
    if(!checkchar(this->email[0])) return 0;
    bool cnt = 0;
    int pos;
    for(int i = 1; i < this->email.size(); i++)
    {
        if(strchr(forbid, this->email[i])) return 0;
        if(this->email[i] == '@')
        {
            if(cnt || checkchar(this->email[i - 1]) || checkchar(this->email[i + 1]) || i == this->email.size() - 1) return 0;
            cnt = 1;
            pos = i;
        }
        if(!checkchar(this->email[i]) && !checkchar(this->email[i - 1])) return 0;
    }
    return 1;
}

bool person::checkPhone()
{
    if(this->phone[0] != '0' || this->phone.size() != 10 || this->phone[1] == '0') return 0;
    for(int i = 1; i < 10; i++)
        if(this->phone[i] < '0' || this->phone[i] > '9') return 0;
    return 1;
}