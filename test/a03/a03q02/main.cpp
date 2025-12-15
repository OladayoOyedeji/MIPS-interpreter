#include <iostream>
#include <cmath>
#include <limits>

const int MAX_BUF = 1024;

void get_instruction(char s[], char in[][1024])
{
    int i = 0;
    // trailing zeros
    while (s[i] == ' ' || s[i] == '\t')
    {
        i++;
    }
    
    int j = 0;
    int k = 0;

    // get instruction
    while (s[i] != ' ' && s[i] != '\t')
    {
        in[j][k++] = s[i++];
    }
    in[j][k] = '\0';
    j++;
    k = 0;
    while (s[i] == ' ' || s[i] == '\t')
    {
        i++;
    }
    
    while (s[i] != '\0')
    {
        if (s[i] == ',')
        {
            in[j][k] = '\0';
            j++;
            k = 0;
            i++;
        }
        if (s[i] != ' ' && s[i] != '\t')
            in[j][k++] = s[i];
        i++;
    }
}

int str_int(char c[])
{
    int size = 0;
    while (c[size] != '\0')
    {
        size++;
    }

    int number = 0;
    for (int i = 0; i < size; ++i)
    {
        number += pow(10, size - i - 1) * (c[i] - '0');
    }
    return number;
    
}

bool same(const char x[], const char s[])
{
    int i = 0;
    while(s[i] != '\0' && x[i] != '\0')
    {
        if (s[i] != x[i++]) return false;
    }

    return (s[i] == x[i]);
}

int main()
{
    int s0 = 0, s1 = 0, s2 = 0;
    
    char input[1024];
    
    while (1)
    {   
        // read string from keyboard and put into input array of characters
        char s[MAX_BUF];
        std::cout << ">>> ";
        std::cin.getline(s, MAX_BUF);
        if (std::cin.eof()) break;
        if (std::cin.fail() || std::cin.bad())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n');
        }
        std::cout << '[' << s << "]\n";
        
        // if input is "" break the while loop
        if (s == "") break;
        
        // perform computation here
        char instruction[4][1024];
        get_instruction(s, instruction);

        std::cout << instruction[0] << " instr: " << instruction[1] << " instr: " << instruction[2] << std::endl;
        int * reg = NULL;
        
        if (same(instruction[1], "$s0"))
            reg = &s0;
        else if (same(instruction[1], "$s1"))
            reg = &s1;
        else
            reg = &s2;

        std::cout << instruction[0] << ':' << "li " << (instruction[0] == "li") << std::endl;
        if (same(instruction[0], "li"))
        {
            int i = str_int(instruction[2]);
            std::cout << i << std::endl;
            *reg = i;
        }
        else 
        {
            int * reg1 = NULL;
            if (same(instruction[2], "$s0"))
                reg1 = &s0;
            else if (same(instruction[2], "$s1"))
                reg1 = &s1;
            else
                reg1 = &s2;

            int * reg2 = NULL;
            if (same(instruction[3], "$s0"))
                reg2 = &s0;
            else if (same(instruction[3], "$s1"))
                reg2 = &s1;
            else
                reg2 = &s2;

            if (same(instruction[0], "add"))
            {
                std::cout << "bro\n";
                *reg = *reg1 + *reg2;
            }
            else
            {
                *reg = *reg1 - *reg2;
            }
        }
        
        std::cout << "$s0: " << s0 << std::endl;
        std::cout << "$s1: " << s1 << std::endl;
        std::cout << "$s2: " << s2 << std::endl;
    }
    std::cout << "END";
    return 0;
}
