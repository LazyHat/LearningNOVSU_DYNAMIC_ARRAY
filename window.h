#pragma once
#include <ncurses.h>
#include <vector>
#include <list>
#define ExitW "Exit"
#define BackW "Back"
#define BacktmW "Back to menu"
class window
{
    WINDOW *w;

public:
    window(unsigned int ystart, unsigned int xstart, unsigned int ysize, unsigned int xsize);
    ~window();
    int getsizey() { return w->_maxy + 1; }
    int getsizex() { return w->_maxx + 1; }
    int printchoosemenu(std::list<string> menuitems, std::vector<string> staffwords);
};