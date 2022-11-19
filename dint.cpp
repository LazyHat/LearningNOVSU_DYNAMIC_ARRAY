#pragma once
#include <stdio.h>
#include "dint.h"
#include <stdlib.h>
#include <ctime>

int power(int value, int powerof)
{
    if (powerof < 0)
        return -1;
    else if (powerof == 0)
        return 1;
    else if (powerof == 1)
        return value;
    else
        return value * power(value, powerof - 1);
}

dint::dint()
{
    this->value = nullptr;
    this->size = 0;
}
dint::dint(const int &amountOfElements)
{
    this->value = (int *)calloc(amountOfElements, sizeof(int));
    this->size = amountOfElements;
}
dint::dint(const dint &arr)
{
    this->value = (int *)malloc(arr.size * sizeof(int));
    for (int i = 0; i < arr.size; i++)
    {
        this->value[i] = arr.value[i];
    }
    this->size = arr.size;
}
dint::dint(dint &&arr)
{
    this->value = arr.value;
    this->size = arr.size;
    arr.value = nullptr;
    arr.size = 0;
}
dint::~dint()
{
    delete[] this->value;
    this->size = 0;
}
#pragma region task
void dint::del()
{
    delete[] this->value;
    this->value = nullptr;
    this->size = 0;
}
dint &dint::create(const int &amountOfElements)
{
    if (nullptr != this->value)
    {
        delete[] this->value;
    }
    if (0 == amountOfElements)
    {
        this->value = nullptr;
        this->size = 0;
        return *this;
    }
    this->value = (int *)calloc(amountOfElements, sizeof(int));
    if (nullptr == this->value)
    {
        (string("not allocate ") + amountOfElements).PrintL();
    }
    this->size = amountOfElements;
    return *this;
}
void dint::printline()
{
    if (0 == this->size || nullptr == this->value)
    {
        throw dintExeption("dint::printline(): value is nullptr or size equal NULL");
        exit(-1);
    }
    std::cout << this->value[0];
    for (int i = 1; i < this->size; i++)
    {
        std::cout << " " << this->value[i];
    }
    std::cout << std::endl;
}
void dint::print()
{
    if (0 == this->size || nullptr == this->value)
    {
        throw dintExeption("dint::print(): value is nullptr or size equal NULL");
        exit(-1);
    }
    std::cout << this->value[0];
    for (int i = 1; i < this->size; i++)
    {
        std::cout << " " << this->value[i];
    }
}
int &dint::operator[](const int &index)
{
    if (this->size - 1 < index)
    {
        throw dintExeption("dint::operator[] out of bounds exeption");
    }
    return this->value[index];
}
dint &dint::operator=(const dint &arr)
{
    if (nullptr != this->value)
    {
        delete[] this->value;
    }
    this->value = (int *)malloc(arr.size * sizeof(int));
    for (int i = 0; i < arr.size; i++)
    {
        this->value[i] = arr.value[i];
    }
    this->size = arr.size;
    return *this;
}
int dint::maxelement()
{
    int max = -INT32_MAX;
    for (int i = 0; i < this->size; i++)
    {
        max = (max > this->value[i]) ? max : this->value[i];
    }
    return max;
}
dint &dint::resize(const int &newamount)
{
    if (nullptr == this->value)
    {
        this->create(newamount);
        return *this;
    }
    else
    {
        if (newamount == this->size)
        {
            return *this;
        }
        else if (newamount > this->size)
        {
            dint temp(*this);
            delete[] this->value;
            this->value = (int *)calloc(newamount, sizeof(int));
            this->size = newamount;
            for (int i = 0; i < temp.size; i++)
            {
                this->value[i] = temp.value[i];
            }
            return *this;
        }
        else
        {
            dint temp(*this);
            delete[] this->value;
            this->value = (int *)malloc(newamount * sizeof(int));
            this->size = newamount;
            for (int i = 0; i < this->size; i++)
            {
                this->value[i] = temp.value[i];
            }
            return *this;
        }
    }
}
void dint::swap(const int index1, const int index2)
{
    int temp = this->value[index1];
    this->value[index1] = this->value[index2];
    this->value[index2] = temp;
}
dint &dint::sort(const profile sortprofile)
{
    switch (sortprofile)
    {
    case 0:
        for (int i = 0; i < this->size; i++)
        {
            if (0 == i && this->value[i + 1] > this->value[i])
            {
                swap(i, i + 1);
            }
            else if (i == this->size - 1)
            {
                continue;
            }
            else if (this->value[i + 1] > this->value[i])
            {
                this->swap(i, i + 1);
                i -= 2;
            }
        }
        break;
    case 1:
        for (int i = 0; i < this->size; i++)
        {
            if (0 == i && this->value[i + 1] < this->value[i])
            {
                swap(i, i + 1);
            }
            else if (i == this->size - 1)
            {
                continue;
            }
            else if (this->value[i + 1] < this->value[i])
            {
                this->swap(i, i + 1);
                i -= 2;
            }
        }
        break;
    }
    return *this;
}
dint &dint::rand(int powerten)
{
    srand(time(NULL));
    for (int i = 0; i < this->size; i++)
    {
        this->value[i] = std::rand() % power(10, powerten);
    }
    return *this;
}
#pragma endregion