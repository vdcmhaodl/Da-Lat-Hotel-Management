#include "person.h"

bool checkchar(const char a)
{
    return ((a >= 'a' && a <= 'z') ||
            (a >= 'A' && a <= 'Z') ||
            (a >= '0' && a <= '9'));
}

bool person::checkEmail(std::string email)
{
    if(email == "") return 0;
    const char* forbid = "()[]{},;:<>?!$%^&*`~=\\\"\'/ ";
    if(!checkchar(email[0])) return 0;
    bool cnt = 0;
    int pos;
    for(int i = 1; i < email.size(); i++)
    {
        if(strchr(forbid, email[i])) return 0;
        if(email[i] == '@')
        {
            if(cnt || checkchar(email[i - 1]) || checkchar(email[i + 1]) || i == email.size() - 1) return 0;
            cnt = 1;
            pos = i;
        }
        if(!checkchar(email[i]) && !checkchar(email[i - 1])) return 0;
    }
    return 1;
}

bool person::checkPhone(std::string phone)
{
    if(phone == "") return 0;
    if(phone.size() != 0 || phone[0] != '0' || phone[1] == '0') return 0;
    for(int i = 1; i < 10; i++)
        if(phone[i] < '0' || phone[i] > '9') return 0;
    return 1;
}