#define _CRT_RAND_S
#include "string.cpp"
#include "dint.cpp"
#include <ncurses.h>
#include <ctime>
#include <thread>
#include <chrono>

void pause(unsigned int timems)
{
    using namespace std::this_thread;
    using namespace std::chrono;
    sleep_for(seconds(timems));
}

int main()
{
    dint k;
    k.create(0);
    k.resize(5);
    k.printline();
    k.create(0);
}