#define _CRT_RAND_S
#include "string.cpp"
#include "dint.cpp"
//#include <ncurses.h>
#include <ctime>
#include <thread>
#include <chrono>

void pause(unsigned int timems)
{
    using namespace std::this_thread;
    using namespace std::chrono;
    sleep_for(seconds(timems));
}

void Menu()
{
    string k("fgsdgd");
    string s("gdfgdfg");
    int g = 34;
    int u = 435;
    // PrintF("");
    std::cout << "Hello World" << endl;
}

int main()
{
    Menu();
    // initscr();
    // Menu();
    // endwin();
}