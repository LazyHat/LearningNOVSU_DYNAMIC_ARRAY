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

void destwin(WINDOW *w)
{
    wborder(w, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(w);
    delwin(w);
}

int main()
{
    initscr();
    WINDOW *win = newwin(10, 20, 5, 5);
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    getch();
    endwin();
}