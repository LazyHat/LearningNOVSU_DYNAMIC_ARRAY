#pragma once
// LIBRARY FOR CPP PROJECTS
#include <iostream>
#include <fstream>

class string
{
private:
    char *s;

public:
    string();
    string(const char *str);
    string(const char &str);
    string(const string &obj);
    string(string &&obj);
    ~string();
    int Size() const;
    void Print() const;
    void PrintL() const;
    bool Contains(const char &symbol);
    bool Contains(const string &obj);
    friend std::ostream &operator<<(std::ostream &out, const string &obj);
    friend std::istream &operator>>(std::istream &in, string &obj);
    friend string ToString(const int &num);
    char *ToArray() const;
    string &operator=(string &&obj);
    string &operator=(const string &obj);
    string operator+(const string &obj);
    string operator+(const char *str);
    string operator+(const int &num);
    string &operator+=(const string &obj);
    char &operator[](const int &index);
    int operator[](const char &index);
    bool operator==(const string &obj);
};

class stringExeption
{
    string error;

public:
    stringExeption(const char *errormessage)
    {
        error = string(errormessage);
    }
    ~stringExeption()
    {
        error = "";
    }
    string GetError() const
    {
        return error;
    }
};