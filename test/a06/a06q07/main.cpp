#include <iostream>

int snprintf(char * buffer, int count, const char * format, char ** argument)
{
    int j = 0;
    int k = 0
    for(int i = 0; i < size; ++i)
    {
        if (format[i] == '%')
        {
            char * z = "";
            if (format[i+1] == 'd')
            {
                itoa(z, argument[j]);
            }
            if (format[i+1] == 'c')
            {
                z[0] = argument[j][0];
                z[1] = '\0';
            }
            if (format[i+1] == 's')
            {
                z = argument[j];
            }
            insert_str(buffer, z);
            i++;
        }
        else
            *buffer = format[i]; buffer += 1;
        
    }
}

int main()
{
    return 0;
}

// side stuff
// insert_
