#include "functions.h"

int32_t len(const char * s)
{
    int32_t i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}

bool strcmp(const std::string & s, const std::string & c)
{
    std::cout << '[' << s << ' ' << c << ']' << std::endl;
    std::cout << s.size() << ' ' << c.size() << std::endl;
    if (s.size() != c.size())
    {
        return false;
    }
    for (int i = 0; i < s.size(); ++i)
    {
        std::cout << s[i] << ' ' << c[i] << std::endl;
        if (s[i] != c[i])
            return false;
    }
    return true;
}

// unsigned char * uint_to_hexad(int32_t i)
// {}
// unsigned char * uint_to_buff(int32_t i)
// {}
// int32_t hexad_to_uint(unsigned char buff[])
// {}
// int32_t buff_to_int(unsigned char buff[])
// {}
