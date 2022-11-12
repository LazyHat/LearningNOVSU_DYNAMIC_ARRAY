#pragma once
#include "string.h"

#pragma region PROTOTYPES
int StrSize(const char *str);
#pragma endregion
#pragma region CONSTRUCTORS AND DESTRUCTORS
string::string()
{
    s = new char[1];
    s[0] = '\0';
}
string::string(const char *str)
{
    if (str == nullptr)
        throw stringExeption("Exep: string(const char *str): str is nullptr");
    int length = StrSize(str);
    s = new char[length + 1];
    for (int i = 0; i < length; i++)
    {
        s[i] = str[i];
    }
    s[length] = '\0';
}
string::string(const string &obj)
{
    int length = StrSize(obj.s);
    s = new char[length];
    for (int i = 0; i < length; i++)
    {
        s[i] = obj.s[i];
    }
    s[length] = '\0';
}
string::string(string &&obj)
{
    this->s = obj.s;
    obj.s = nullptr;
}
string::~string()
{
    delete[] s;
}
#pragma endregion
#pragma region FUNCTIONS
#pragma region OPERATORS
std::ostream &operator<<(std::ostream &out, const string &obj)
{
    out << obj.s;
    return out;
}
std::istream &operator>>(std::istream &in, string &obj)
{
    // in >> obj.s;
    return in;
}
string &string::operator=(string &&obj)
{
    this->s = obj.s;
    obj.s = nullptr;
    return *this;
}
string &string::operator=(const string &obj)
{
    int length = StrSize(obj.s);
    this->s = new char(length + 1); // + '\0'
    for (int i = 0; i < length; i++)
    {
        this->s[i] = obj.s[i];
    }
    this->s[length] = '\0';

    return *this;
}
string string::operator+(const string &obj)
{
    string sumobj;
    int length1 = this->Size();
    int length2 = StrSize(obj.s);
    sumobj.s = new char[length1 + length2 + 1]; // Plus '\0'
    for (int i = 0; i < length1; i++)
    {
        sumobj.s[i] = s[i];
    }
    for (int i = 0; i < length2; i++)
    {
        sumobj.s[i + length1] = obj.s[i];
    }
    sumobj.s[length1 + length2] = '\0';
    return sumobj;
}
string string::operator+(const char *str)
{
    string sumobj;
    int length1 = this->Size();
    int length2 = StrSize(str);
    sumobj.s = new char[length1 + length2 + 1]; // Plus '\0'
    for (int i = 0; i < length1; i++)
    {
        sumobj.s[i] = s[i];
    }
    for (int i = 0; i < length2; i++)
    {
        sumobj.s[i + length1] = str[i];
    }
    sumobj.s[length1 + length2] = '\0';
    return sumobj;
}
string string::operator+(const int &num)
{
    return *this + ToString(num);
}
string &string::operator+=(const string &obj)
{
    *this = *this + obj;
    return *this;
}
char &string::operator[](const int &index)
{
    if (abs(index) > this->Size())
        throw stringExeption("Exep: operator[const int &index]: index out of range.");
    if (index >= 0)
        return this->s[index];
    else
    {
        return this->s[this->Size() + index];
    }
}
int string::operator[](const char &index)
{
    for (int i = 0; i < this->Size(); i++)
        if (this->s[i] == index)
            return i;
    throw stringExeption("Exep: operator[const char &index]: index out of line.");
}
bool string::operator==(const string &obj)
{
    if (int len = this->Size() == StrSize(obj.s))
    {
        for (int i = 0; i < len; i++)
        {
            if (this->s[i] != obj.s[i])
                return false;
        }
        return true;
    }
    else
        return false;
}
#pragma endregion
int string::Size()
{
    return StrSize(s);
}
void string::Print()
{
    std::cout << *this;
}
void string::PrintL()
{
    std::cout << *this << "\n";
}
bool string::Contains(const char &symbol)
{
    for (int i = 0; i < this->Size(); i++)
    {
        if (this->s[i] == symbol)
            return true;
    }
    return false;
}
bool string::Contains(const string &obj)
{
    if (this->Size() < StrSize(obj.s))
        return false;
    else
    {
        for (int i = 0; i < this->Size(); i++)
        {
            bool stopflag = false;
            if (this->s[i] == obj.s[0])
            {
                for (int j = i; j < i + StrSize(obj.s); j++)
                {
                    if (this->s[j] != obj.s[j])
                    {
                        stopflag = true;
                        break;
                    }
                }
                if (!stopflag)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
string ToString(const int &num)
{
    char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char symbols[] = {'-'};
    string strnum;
    int length = 0;
    for (int i = num; i != 0; i /= 10)
        length++;
    int bnum = num;
    if (num < 0)
    {
        length++;
        strnum.s = new char[length + 1];
        strnum.s[length] = '\0';
        strnum.s[0] = symbols[0];
        bnum = abs(bnum);
        for (int i = length - 1; i >= 1; i--)
        {
            strnum.s[i] = numbers[bnum % 10];
            bnum /= 10;
        }
    }
    else
    {
        strnum.s = new char[length + 1];
        strnum.s[length] = '\0';
        for (int i = length - 1; i >= 0; i--)
        {
            strnum.s[i] = numbers[bnum % 10];
            bnum /= 10;
        }
    }
    return strnum;
}
char *string::ToArray() const
{
    return this->s;
}
int StrSize(const char *str)
{
    int length = 0;
    while (str[length] != '\0')
        length++;
    return length;
}
void SetCPConsole(int cp)
{
    SetConsoleCP(cp);
    SetConsoleOutputCP(cp);
}
#pragma region FILE_FSTREAM
string GetStrLine(std::ifstream &file)
{
    return string("GetStrLine()");
}
#pragma endregion
#pragma endregion