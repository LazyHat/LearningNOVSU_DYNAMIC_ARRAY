#pragma once
#include "window.h"
#include "string.cpp"

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
                if (staffwords[highlight - menuitems.size() + staffwords.size()] == ExitW)
                {
                    endwin();
                    exit(0);
                }
                return (highlight + staffwords.size() - menuitems.size() + 1) * -1;
            }
            else
            {
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
int window::addgetmenu(string callsentence)
{
    mvwprintw(this->w, 1, 1, "%s: ", callsentence.ToArray());
    wrefresh(this->w);
    echo();
    char str[10];
    mvwgetstr(this->w, 1, 2, str);
    try
    {
        return string(str).ToInt();
    }
    catch (stringExeption &a)
    {
        mvwprintw(this->w, 1, 2, "%s", a.GetError().ToArray());
    }
    return 0;
}
