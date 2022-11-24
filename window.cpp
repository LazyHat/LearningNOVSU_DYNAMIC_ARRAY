#pragma once
#include "window.h"
#include "string.cpp"
#define POS_LEFT 0
#define POS_RIGHT 1

window::window(unsigned int ystart, unsigned int xstart, unsigned int ysize, unsigned int xsize)
{
    this->w = newwin(ysize, xsize, ystart, xstart);
    refresh();
    this->adddesign();
}
window::window(window positionfrom, bool position, unsigned int ystart, unsigned int ysize, unsigned int xsize)
{
    this->w = newwin(ysize, xsize, ystart, (position ? positionfrom.getsizex() + positionfrom.getstartx() : positionfrom.getstartx() - xsize));
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
int window::addchoosemenu(std::list<string> menuitems, std::vector<string> staffwords)
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
                return (highlight + staffwords.size() - menuitems.size() + 1) * -1;
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
    this->move(2, 1);
    int highlight = 0;
    while (true)
    {
        for (int i = 0; i < array.size(); i++)
        {
            if (i != 0)
                wprintw(this->w, " ");
            if (i == highlight)
                wattron(this->w, A_REVERSE);
            wprintw(this->w, "%d", array[i]);
            wattroff(this->w, A_REVERSE);
        }
        wrefresh(this->w);
        switch (wgetch(this->w))
        {
        case KEY_RIGHT:
            highlight++;
            break;
        case KEY_LEFT:
            highlight++;
            break;
        case KEY_UP:
            this->clear();
            return -1;
        case KEY_DOWN:
            this->clear();
            return -1;
        case 10:
            return highlight;
        }
        if (highlight < 0)
            highlight = array.size() - 1;
        else if (highlight > array.size() - 1)
            highlight = 0;
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
        return string(str).ToInt();
    }
    catch (stringExeption &a)
    {
        mvwprintw(this->w, 1, 2, "%s", a.GetError().ToArray());
    }
    this->clear();
    return 0;
}
