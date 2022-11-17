#define _CRT_RAND_S
#include "string.cpp"
#include "dint.cpp"
#include "window.cpp"
#include <ctime>
#include <thread>
#include <chrono>

void pause(unsigned int timeseconds)
{
    using namespace std::this_thread;
    using namespace std::chrono;
    sleep_for(seconds(timeseconds));
}

int main()
{
    initscr();
    window win(5, 5, 5, 5);
    win.~window();
    endwin();
}