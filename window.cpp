#pragma once
#include "window.h"

window::window(unsigned int ystart, unsigned int xstart, unsigned int ysize, unsigned int xsize)
{
    w = newwin(ysize, xsize, ystart, xstart);
    refresh();
    box(w, 0, 0);
    wrefresh(w);
}
window::~window()
{
    werase(this->w);
    wborder(this->w, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(this->w);
    delwin(this->w);
}
int window::printchoosemenu(std::list<string> menuitems, std::vector<string> staffwords)
{
    for (auto &&item : staffwords)
    {
        menuitems.push_back(item);
    }
}