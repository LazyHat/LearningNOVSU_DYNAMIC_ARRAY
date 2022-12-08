#pragma once
//#include "string.cpp"

enum profile
{
    FMaxTMin,
    FMinTMax
};

class dint
{
    int *value = nullptr;
    unsigned int _size;

public:
    unsigned int size() const { return _size; }
    dint();
    dint(const dint &arr);
    dint(const int &amountOfElements);
    dint(dint &&arr);
    ~dint();
    dint &operator=(const dint &arr);
    void swap(const int index1, const int index2);
#pragma region taskf
    void del();
    dint &create(const int &amountOfElements); // create
    void printline();                          // print
    void print();                              // print
    int &operator[](const int &index);         // read(index);
    int maxelement();                          // max
    dint &resize(const int &newamount);        // resize
    dint &sort(const profile sortprofile);     // sort 2 profiles
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