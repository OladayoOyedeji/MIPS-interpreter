#include "TextSegment.h"

void instruction_lexer(const std::string & s, std::vector< std::string > & token)
{
    int i = 0;
    int j = 0;
    while (j != s.size())
    {
        if (s[j] == ' ' || s[j] == ',')
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
