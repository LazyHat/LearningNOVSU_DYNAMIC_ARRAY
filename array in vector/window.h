#pragma once
#include "string.h"
#include <ncurses.h>
#include <vector>
#include <list>
#define WORD_EXIT "Exit"
#define WORD_BACK "Back"
#define WORD_BACKTM "Back to menu"
#define INT_BACK -1
#define INT_BACKTM -2

class window
{
public:
    WINDOW *w;

public:
    window(unsigned int ystart, unsigned int xstart, unsigned int ysize, unsigned int xsize);
    window(window positionfrom, unsigned int ystart, unsigned int ysize, unsigned int xsize);
    window(window posfrom, unsigned int xsize);
    void destwin();
    void winrefresh(dint array, int pos);
    void winrefresh();
    void winresizey(unsigned int ysize);
    int getstarty() { return w->_begx; }
    int getstartx() { return w->_begy; }
    int getsizey() { return w->_maxy + 1; }
    int getsizex() { return w->_maxx + 1; }
    void print(const int num);
    void print(string str);
    void move(int y, int x);
    void mvprint(int y, int x, string str);
    void clear();
    void adddesign();
    int addchsmenu(std::list<string> menuitems, std::vector<string> staffwords);
    int addselect(dint array);
    int addgetmenu(string callsentence);
};