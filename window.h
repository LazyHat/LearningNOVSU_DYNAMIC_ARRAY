#pragma once
#include "string.h"
#include <ncurses.h>
#include <vector>
#include <list>
#define ExitW "Exit"
#define BackW "Back"
#define BacktmW "Back to menu"
class window
{
public:
    WINDOW *w;

public:
    window(unsigned int ystart, unsigned int xstart, unsigned int ysize, unsigned int xsize);
    window(window positionfrom, bool position, unsigned int ystart, unsigned int ysize, unsigned int xsize);
    ~window();
    int getstarty() { return w->_begx; }
    int getstartx() { return w->_begy; }
    int getsizey() { return w->_maxy + 1; }
    int getsizex() { return w->_maxx + 1; }
    void clear();
    void adddesign();
    int addchoosemenu(std::list<string> menuitems, std::vector<string> staffwords);
    int addgetmenu(string callsentence);
};