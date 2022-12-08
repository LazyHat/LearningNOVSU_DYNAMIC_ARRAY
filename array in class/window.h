#pragma once
#include <list>
#include "string.h"
#include <ncurses.h>
#define Y_SIZE 4
#define X_MIN_SIZE 20

class window
{
public:
    WINDOW *w;

private:
    uint8_t _color = 0;

public:
    window(unsigned int yst, unsigned int xst, unsigned int ysz, unsigned int xsz, uint8_t color)
    {
        this->w = newwin(ysz, xsz, yst, xst);
        this->_color = color;
        wrefresh(stdscr);
    }
    uint8_t color() { return _color; }
    void adddesign()
    {
        wattron(this->w, COLOR_PAIR(this->color()));
        box(this->w, 0, 0);
        wattroff(this->w, COLOR_PAIR(this->color()));
    }
    void winrefresh()
    {
        wrefresh(this->w);
    }
    void dclear()
    {
        werase(this->w);
        this->adddesign();
    }
    int printmenu(std::list<string> items)
    {
        static int highlight;
        keypad(this->w, true);
        while (true)
        {
            if (highlight < 0)
                highlight = items.size() - 1;
            else if (highlight > items.size() - 1)
                highlight = 0;
            unsigned int ni = 0;
            for (auto i = items.begin(); i != items.end(); i++, ni++)
            {
                if (ni == highlight)
                    wattron(this->w, A_REVERSE);
                mvwprintw(this->w, ni + 1, 1, "%d.%s", ni + 1, (*i).ToArray());
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
                keypad(this->w, false);
                return highlight + 1;
            }
        }
    }
};