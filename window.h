#pragma once
#include "string.h"
#include <ncurses.h>
#include <vector>
#include <list>
#define WORD_EXIT "Exit"
#define WORD_BACK "Back"
#define WORD_BACKTM "Back to menu"
class window
{
public:
    WINDOW *w;

public:
    window(unsigned int ystart, unsigned int xstart, unsigned int ysize, unsigned int xsize);
    window(window positionfrom, bool position, unsigned int ystart, unsigned int ysize, unsigned int xsize);
    void destwin();
    int getstarty() { return w->_begx; }
    int getstartx() { return w->_begy; }
    int getsizey() { return w->_maxy + 1; }
    int getsizex() { return w->_maxx + 1; }
    void print(string str);
    void move(int y, int x);
    void mvprint(int y, int x, string str);
    void clear();
    void adddesign();
    int addchoosemenu(std::list<string> menuitems, std::vector<string> staffwords);
    int addselect(dint array);
    int addgetmenu(string callsentence);
};