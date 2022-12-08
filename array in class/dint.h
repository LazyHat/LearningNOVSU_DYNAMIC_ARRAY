#pragma once
#include "string.h"
enum profile
{
    FMaxTMin,
    FMinTMax
};

class dint
{
    int *value = nullptr;
    size_t _size;

public:
    size_t size() const { return _size; }
    dint();
    dint(const dint &arr);
    dint(const size_t &amountOfElements);
    dint(dint &&arr);
    ~dint();
    dint &operator=(const dint &arr);
    void swap(const int index1, const int index2);
#pragma region taskf
    void del();
    dint &create(const size_t &amountOfElements); // create
    void printline();                             // print
    void print();                                 // print
    int &operator[](const int &index);            // read(index);
    int maxelement();                             // max
    dint &resize(const size_t &newsize);          // resize
    dint &sort(const profile sortprofile);        // sort 2 profiles
    dint &rand(int powerten);
#pragma endregion
};

class dintExeption
{
    string errormsg;

public:
    dintExeption(const char *errorMessage)
    {
        errormsg = errorMessage;
    }
    ~dintExeption()
    {
        errormsg = "";
    }
    string GetErrorMessage()
    {
        return errormsg;
    }
};