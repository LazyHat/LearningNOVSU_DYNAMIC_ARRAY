#pragma once
#include "window.h"
#include "string.cpp"
#include "dint.h"
window::window(unsigned int ystart, unsigned int xstart, unsigned int ysize, unsigned int xsize)
{
    this->w = newwin(ysize, xsize, ystart, xstart);
    refresh();
    this->adddesign();
}
window::window(window positionfrom, unsigned int ystart, unsigned int ysize, unsigned int xsize)
{
    this->w = newwin(ysize, xsize, ystart, positionfrom.getsizex() + positionfrom.getstartx());
    refresh();
    this->adddesign();
}
window::window(window posfrom, unsigned int xsize)
{
    this->w = newwin(posfrom.w->_maxy + 1, xsize, posfrom.w->_begy, posfrom.w->_begx + posfrom.w->_maxx + 1);
    refresh();
    this->adddesign();
}
void window::destwin()
{
    werase(this->w);
    wborder(this->w, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(this->w);
    delwin(this->w);
    refresh();
}
void window::winrefresh(dint array, int pos)
{
    this->clear();
    this->adddesign();
    this->mvprint(1, 1, string("Array ") + (pos + 1) + string(" Max: ") + array.maxelement());
    this->move(2, 1);
    for (int j = 0; j < array.size(); j++)
    {
        if (j != 0)
            this->print(" ");
        this->print(array[j]);
    }
}
void window::print(const int num)
{
    wprintw(this->w, "%d", num);
    wrefresh(this->w);
}
void window::print(string str)
{
    wprintw(this->w, "%s", str.ToArray());
    wrefresh(this->w);
}
void window::mvprint(int y, int x, string str)
{
    mvwprintw(this->w, y, x, "%s", str.ToArray());
    wrefresh(this->w);
}
void window::move(int y, int x)
{
    wmove(this->w, y, x);
}
void window::clear()
{
    werase(this->w);
    this->adddesign();
}
void window::adddesign()
{
    box(this->w, 0, 0);
    wrefresh(this->w);
}
int window::addchsmenu(std::list<string> menuitems, std::vector<string> staffwords)
{
    for (auto &&item : staffwords)
    {
        menuitems.push_back(item);
    }
    auto iter = menuitems.begin();
    int highlight = 0;
    keypad(this->w, true);
    while (true)
    {
        iter = menuitems.begin();
        for (int i = 0, string; i < menuitems.size(); i++)
        {
            if (highlight == i)
                wattron(this->w, A_REVERSE);
            mvwprintw(this->w, 1 + i, 1, "%d. %s", i + 1, (*iter).ToArray());
            iter++;
            wattroff(this->w, A_REVERSE);
        }
        wrefresh(this->w);
        switch (wgetch(this->w))
        {
        case KEY_UP:
            highlight--;
            break;
        case KEY_DOWN:
            highlight++;
            break;
        case 10:
            if (highlight >= menuitems.size() - staffwords.size())
            {
                if (staffwords[highlight - menuitems.size() + staffwords.size()] == WORD_EXIT)
                {
                    endwin();
                    exit(0);
                }
                this->clear();
                if (staffwords[highlight - menuitems.size() + staffwords.size()] == WORD_BACK)
                {
                    return INT_BACK;
                }
                else if (staffwords[highlight - menuitems.size() + staffwords.size()] == WORD_BACKTM)
                {
                    return INT_BACKTM;
                }
            }
            else
            {
                this->clear();
                return highlight;
            }
            break;
        default:
            break;
        }
        if (highlight < 0)
            highlight = menuitems.size() - 1;
        else if (highlight > menuitems.size() - 1)
            highlight = 0;
    }
}
int window::addselect(dint array)
{
    keypad(this->w, true);
    static int selecthighlight = 0;
    while (true)
    {
        this->move(2, 1);
        for (int i = 0; i < array.size(); i++)
        {
            if (i != 0)
                wprintw(this->w, " ");
            if (i == selecthighlight)
                wattron(this->w, A_REVERSE);
            wprintw(this->w, "%d", array[i]);
            wattroff(this->w, A_REVERSE);
        }
        wrefresh(this->w);
        switch (wgetch(this->w))
        {
        case KEY_RIGHT:
            selecthighlight++;
            break;
        case KEY_LEFT:
            selecthighlight--;
            break;
        case KEY_UP:
            this->clear();
            return INT_BACK;
        case KEY_DOWN:
            this->clear();
            return INT_BACK;
        case 10:
            return selecthighlight;
        }
        if (selecthighlight < 0)
            selecthighlight = array.size() - 1;
        else if (selecthighlight > array.size() - 1)
            selecthighlight = 0;
    }
}
int window::addgetmenu(string callsentence)
{
    mvwprintw(this->w, 1, 1, "%s: ", callsentence.ToArray());
    wrefresh(this->w);
    echo();
    char str[10];
    wgetstr(this->w, str);
    try
    {
        this->clear();
        noecho();
        return string(str).ToInt();
    }
    catch (stringExeption &a)
    {
        mvwprintw(this->w, 1, 2, "%s", a.GetError().ToArray());
        wrefresh(this->w);
    }
    this->clear();
    noecho();
    return 0;
}
