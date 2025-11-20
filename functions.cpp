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


void print_bin(int x, int len)
{
    for (int i = len - 1; i >= 0; --i)
    {
        std::cout << ((x >> i) & 1);
    }
    std::cout << std::dec << ' ' << x; 
}

void instruction_lexer(const std::string & s, std::vector< std::string > & token,
                       std::string & Label)
{
    int i = 0;
    int j = 0;
    while (j != s.size())
    {
        if (s[j] == ':' && Label == "")
        {
            Label = s.substr(i, j - i);

            if (Label == "")
            {
                throw std::runtime_error("Syntax Error");
            }
            i = j + 1;
        }
        else if (s[j] == ' ' || s[j] == ',' || s[j] == '\t')
        {
            if (j - i == 0)
            {
                i++;
            }
            else
            {
                token.push_back(s.substr(i, j - i));
                i = j+1;
            }
        }
        j++;
    }
    if (j - i == 0)
    {
        i++;
    }
    else
    {
        token.push_back(s.substr(i, j - i));
        i = j+1;
    }
}

int get_numeric(const std::string & s)
{
    int sign = 1;
    int num = 0;
    int size = s.size();
    int i = 0;
    if (s[i] == '-')
    {
        sign = -1;
        i++;
    }
    for (; i < size; ++i)
    {
        if (s[i] <= '9' && s[i] >= '0')
        {
            num += (s[i] - '0') * pow(10, size - i - 1);
            std::cout << num << ' ' << s[i] << std::endl;
        }
        else
        {
            std::cout << "what the hell?\n";
            return -99999;
        }
    }
    return num * sign;
}

// unsigned char * uint_to_hexad(int32_t i)
// {}
// unsigned char * uint_to_buff(int32_t i)
// {}
// int32_t hexad_to_uint(unsigned char buff[])
// {}
// int32_t buff_to_int(unsigned char buff[])
// {}
