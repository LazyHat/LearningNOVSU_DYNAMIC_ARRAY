#define _CRT_RAND_S
#include "string.cpp"
#include "dint.cpp"
#include "window.cpp"
#include <list>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>

void pause(unsigned int timeseconds)
{
    using namespace std::this_thread;
    using namespace std::chrono;
    sleep_for(seconds(timeseconds));
}

void destwin(WINDOW *w)
{
    werase(w);
    wborder(w, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(w);
    delwin(w);
}

int wchoosemenu(int ysize, int xsize, std::list<string> items)
{
    items.push_back("Exit");
    WINDOW *w = newwin(ysize, xsize, 0, 0);
    refresh();
    box(w, 0, 0);
    wrefresh(w);
    curs_set(0);
    keypad(w, true);
    int choice = 0;
    int highlight = 0;
    while (true)
    {
        int i = 0;
        for (auto &&item : items)
        {
            if (highlight == i)
            {
                wattron(w, A_REVERSE);
            }
            mvwprintw(w, i + 1, 1, "%d.%s", i + 1, item.ToArray());
            wattroff(w, A_REVERSE);
            i++;
        }
        wrefresh(w);
        choice = wgetch(w);
        if (choice == 10)
        {
            break;
        }
        else
        {
            switch (choice)
            {
            case KEY_UP:
                highlight--;
                break;
            case KEY_DOWN:
                highlight++;
                break;
            default:
                break;
            }
            if (highlight == 3)
            {
                highlight = 0;
            }
            else if (highlight == -1)
            {
                highlight = 2;
            }
        }
    }
    destwin(w);
    if (highlight == items.size() - 1)
        return -1;
    return highlight + 1;
}
int wgetmenu(int ysize, int xsize, const char *quest)
{
    WINDOW *w = newwin(ysize, xsize, 0, 0);
    refresh();
    box(w, 0, 0);
    wrefresh(w);
    int get = 0;
    mvwprintw(w, 1, 1, "%s: ", quest);
    wrefresh(w);
    // wmove(w, 2, 1);
    echo();
    wrefresh(w);
    char *str;
    wgetstr(w, str);
    noecho();
    string s(str);
    int result;
    try
    {
        result = s.ToInt();
    }
    catch (stringExeption &a)
    {
        mvwprintw(w, 2, 1, "%s", a.GetError().ToArray());
        wrefresh(w);
        getch();
    }
    destwin(w);
    return result;
}

void winarr(int xstartarrwin, std::list<string> &menuarritems, std::vector<dint> items, std::vector<WINDOW *> &winds)
{
    if (items.size() < winds.size())
    {
        for (int i = items.size(); i < winds.size(); i++)
        {
            destwin(winds[i]);
            menuarritems.pop_back();
        }
    }
    else if (items.size() > winds.size())
    {
        for (int i = winds.size(); i < items.size(); i++)
        {
            winds.push_back(newwin(4, (items[i].size < 8 ? 16 : items[i].size * 2 + 1), (int)((double)i * 4.25), xstartarrwin)); // items[i].size < 10? 10, items
            refresh();
            box(winds[i], 0, 0);
            wrefresh(winds[i]);
        }
    }
    for (int i = 0; i < items.size(); i++)
    {
        mvwprintw(winds[i], 1, 1, "Array %d Max: %d", i + 1, items[i].maxelement());
        for (int j = 0; j < items[i].size; j++)
        {
            mvwprintw(winds[i], 2, 1 + 2 * j, "%d", items[i][j]);
        }
        wrefresh(winds[i]);
    }
}

int main()
{
    noecho();
    std::vector<dint> arrays;
    std::vector<WINDOW *> windows;
    initscr();
    int xsize = 30, ysize = 15, xstartarrwin = xsize + 1;
    std::list<string> menuitems = {"Create array"};
    std::list<string> menufunctions = {"Resize"};
    std::list<string> menuarritems;
    bool flag = 1;
    while (true)
    {
        if (arrays.size() != 0)
        {
            winarr(xstartarrwin, menuarritems, arrays, windows);
        }
        int choice = wchoosemenu(ysize, xsize, menuitems);
        switch (choice)
        {
        case 1:
        {
            int result = wgetmenu(ysize, xsize, "Enter size");
            arrays.push_back(dint(result));
            menuarritems.insert(--menuarritems.end(), string("Array ") + (menuarritems.size() + 1));
            if (flag)
            {
                menuitems.insert(++menuitems.begin(), "Change array");
                flag = !flag;
            }
        }
        break;
        case 2:
        {
            int choosemenu = wchoosemenu(ysize, xsize, menuarritems);
            if (choosemenu == -1)
                break;
            int choosefunc = wchoosemenu(ysize, xsize, menufunctions);
            if (choosefunc == -1)
                break;
            switch (choosefunc)
            {
            case 1: // resize
                int newsize = wgetmenu(ysize, xsize, "Enter new size");
                arrays[choosemenu - 1].resize(newsize);
                for (int i = windows.size() - 1; i >= 0; i--)
                {
                    destwin(windows[i]);
                    windows.pop_back();
                }
                break;
            }
        }
        break;
        default:
            endwin();
            exit(0);
        }
    }
    getch();
    endwin();
}