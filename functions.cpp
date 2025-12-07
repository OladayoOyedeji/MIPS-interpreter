#include "functions.h"

void append_to_path(char * path, int & size, const char * file)
{
    // append dir to path
    // std::cout << "herro? [" << path[size - 2] << ']' << std::endl;
    path[size++] = '/';
    int i = 0;
    while (true)
    {
        // std::cout << '[' << path << "] " << file[i] << std::endl;
        path[size] = file[i];
        if (file[i++] == '\0') break;
        size++;
    }
    // std::cout << '[' << path << "] " << std::endl;
}

void append_to_path(std::string & path, const char * file)
{
    // append dir to path
    // std::cout << "herro? [" << path[size - 2] << ']' << std::endl;
    path.push_back('/');
    int i = 0;
    while (true)
    {
        // std::cout << '[' << path << "] " << file[i] << std::endl;
        path.push_back(file[i]);
        if (file[i++] == '\0') break;
    }
    // std::cout << '[' << path << "] " << std::endl;
}

int32_t len(const char * s)
{    int32_t i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}

bool strcmp(const std::string & s, const std::string & c)
{
    // std::cout << '[' << s << ' ' << c << ']' << std::endl;
    // std::cout << s.size() << ' ' << c.size() << std::endl;
    if (s.size() != c.size())
    {
        return false;
    }
    for (int i = 0; i < s.size(); ++i)
    {
        // std::cout << s[i] << ' ' << c[i] << std::endl;
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

void get_imm_reg(const std::string & s, std::vector< std::string > & token)
{
    int i = 0;
    for (int j = 0; j < s.size(); ++j)
    {
        if (s[j] == '(')
        {
            token.push_back(s.substr(i, j - i));
            i = j + 1;
            break;
        }
        else if (s[i] < '0' || s[i] > '9')
        {
            throw std::runtime_error("Invalid Instruction");
        }
    }
    if (token.size() == 1)
    {
        for (int j = 0; j < s.size(); ++j)
        {
            if (s[j] == ')')
            {
                token.push_back(s.substr(i, j - i));
                return;
            }
        }
    }
    throw std::runtime_error("Invalid Instruction");
}

void instruction_lexer(const std::string & s, std::vector< std::string > & token,
                       std::string & Label)
{
    int i = 0;
    int j = 0;
    while (j != s.size())
    {
        if (s[j] == '#')
            break;
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
            // std::cout << num << ' ' << s[i] << std::endl;
        }
        else
        {
            throw std::runtime_error("");
        }
    }
    return num * sign;
}


//
int get_register(const std::string & s)
{
    if (REGISTER_NOMENCLATURE.find(s) != REGISTER_NOMENCLATURE.end())
    {
        // std::cout << "here?\n" << "rt" << s << ' '
        //           << REGISTER_NOMENCLATURE[s] << std::endl;
        return REGISTER_NOMENCLATURE[s];
    }
    else if (s.size() == 2 && s[0] == '$' && s[1] >= '0' && s[1] <= '9')
    {
        // std::cout << "no here?\n" << "rt" << s << ' ' << s[1] << std::endl;;
        return (s[1] - '0');
    }
    else
    {
        // std::string error_message = "Register ";
        // error_message.push_back(s);
        // error_message.push_back("not found");
        throw std::runtime_error("Register not found");
    }
    return -1;
}

char unescape_from_string(const std::string& s) {
    if (s.empty()) return '\0'; // or throw

    char c = s[0];
    switch (c) {
        case 'n':  return '\n';
        case 't':  return '\t';
        case 'r':  return '\r';
        case 'b':  return '\b';
        case 'f':  return '\f';
        case 'v':  return '\v';
        case 'a':  return '\a';
        case '\\': return '\\';
        case '\'': return '\'';
        case '"':  return '"';
        case '?':  return '\?';
        case '0':  return '\0';
        default:   return c;
    }
}

std::string unescape(const std::string& s)
{
    std::string out;
    for (size_t i = 0; i < s.size(); i++)
    {
        if (s[i] != '\\')
        {
            out += s[i];
            continue;
        }

        // Found \
        if (i + 1 >= s.size()) break;
        char c = s[i+1];
        i++; // skip next char (handled below)

        switch (c)
        {
            case 'n': out += '\n'; break;
            case 't': out += '\t'; break;
            case 'r': out += '\r'; break;
            case 'v': out += '\v'; break;
            case 'f': out += '\f'; break;
            case 'b': out += '\b'; break;
            case 'a': out += '\a'; break;
            case '\\': out += '\\'; break;
            case '\'': out += '\''; break;
            case '"': out += '"'; break;
            case '?': out += '?'; break;

            // Octal \123
            case '0': case '1': case '2': case '3':
            case '4': case '5': case '6': case '7':
            {
                int val = c - '0';
                int count = 0;
                while (i + 1 < s.size() && count < 2 && s[i+1] >= '0' && s[i+1] <= '7') {
                    val = val * 8 + (s[++i] - '0');
                    count++;
                }
                out += static_cast<char>(val);
                break;
            }

            // Hex \xAB
            case 'x': {
                int val = 0;
                while (i + 1 < s.size() && isxdigit(s[i+1])) {
                    char h = s[++i];
                    val = val * 16 +
                          (h >= '0' && h <= '9' ? h - '0' :
                          (h >= 'a' && h <= 'f' ? h - 'a' + 10 :
                           h - 'A' + 10));
                }
                out += static_cast<char>(val);
                break;
            }

            default:
                // Unknown escape → keep original
                out += c;
                break;
        }
    }
    return out;
}

void data_lexer(const std::string & s, std::vector<std::string> & token, std::string & Label)
{
    int i = 0;
    int j = 0;
    while (j != s.size())
    {
        if (s[j] == '#')
            break;
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
            if (s[i] == '\"' || s[i] == '\'')
            {
                char c = s[i];
                //token.push_back(c);
                j = ++i;
                while (s[j] != c)
                {
                    if (s[j] == '\0')
                    {
                        throw std::runtime_error("Invalid instruction");
                    }
                    j++;
                }
                token.push_back(unescape(s.substr(i, j - i)));
                i = j + 1;
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

void print_unsigned_char(unsigned char c)
{
    if (int(c) > 31 && int(c) < 128)
    { std::cout << c; return;}
    else if (int(c)>127) {std::cout << '.'; return;}
    
    switch (c)
    {
        case '\n':
            std::cout << "\\n";
            break;
        case '\t':
            std::cout << "\\t";
            break;
        case '\0':
            std::cout << "\\0";
            break;
        case '\"':
            std::cout << "\\";
            break;
        case '\f':
            std::cout << "\\t";
            break;
        case '\r':
            std::cout << "\\r";
            break;
        default:
            std::cout << '_';
    }
    
}



// unsigned char * uint_to_hexad(int32_t i)
// {}
// unsigned char * uint_to_buff(int32_t i)
// {}
// int32_t hexad_to_uint(unsigned char buff[])
// {}
// int32_t buff_to_int(unsigned char buff[])
// {}
