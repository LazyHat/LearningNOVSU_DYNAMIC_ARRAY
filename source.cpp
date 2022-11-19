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

int sizearrsymbols(dint arr)
{
    int size = 0;
    for (int i = 0; i < arr.size; i++)
    {
        int item = arr[i];
        do
        {
            item /= 10;
            size++;
        } while (item != 0);
    }
    return size;
}
int sizeintsymbols(int k)
{
    int size;
    do
    {
        k /= 10;
        size++;
    } while (k != 0);
    return size;
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
            if (highlight == items.size())
            {
                highlight = 0;
            }
            else if (highlight == -1)
            {
                highlight = items.size() - 1;
            }
        }
    }
    destwin(w);
    if (highlight == items.size() - 1)
        return -1;
    return highlight;
}
int wgetmenu(int ysize, int xsize, const char *quest)
{
    WINDOW *w = newwin(ysize, xsize, 0, 0);
    refresh();
    box(w, 0, 0);
    int get = 0;
    mvwprintw(w, 1, 1, "%s: ", quest);
    echo();
    wrefresh(w);
    char str[11];
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
    for (int i = items.size(); i < winds.size(); i++)
    {
        destwin(winds[i]);
    }
    winds.clear();
    for (int i = winds.size(); i < items.size(); i++)
    {
        winds.push_back(newwin(4, (items[i].size + 1 + sizearrsymbols(items[i]) < 16 ? 16 : items[i].size + 1 + sizearrsymbols(items[i])), (int)((double)i * 4.25), xstartarrwin));
        refresh();
        box(winds[i], 0, 0);
        wrefresh(winds[i]);
    }
    for (int i = 0; i < items.size(); i++)
    {
        mvwprintw(winds[i], 1, 1, "Array %d Max: %d", i + 1, items[i].maxelement());
        wmove(winds[i], 2, 1);
        for (int j = 0; j < items[i].size; j++)
        {
            if (j != 0)
                wprintw(winds[i], " ");
            wprintw(winds[i], "%d", items[i][j]);
        }
        wrefresh(winds[i]);
    }
}

void menuarritemschanged(std::list<string> &items, std::vector<dint> arrs)
{
    items.clear();
    for (int i = 0; i < arrs.size(); i++)
    {
        items.push_back(string("Array ") + (i + 1));
    }
}

int wselectitem(int ysize, int xsize, WINDOW *arrwind, dint array)
{
    static int highlight = 0;
    WINDOW *win = newwin(ysize, xsize, 0, 0);
    refresh();
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "Select value: ");
    wrefresh(win);
    keypad(arrwind, true);
    while (true)
    {
        wmove(arrwind, 2, 1);
        for (int i = 0; i < array.size; i++)
        {
            if (i != 0)
                wprintw(arrwind, " ");
            if (highlight == i)
                wattron(arrwind, A_REVERSE);
            wprintw(arrwind, "%d", array[i]);
            wattroff(arrwind, A_REVERSE);
        }
        wrefresh(arrwind);
        int choosevalue = wgetch(arrwind);
        if (choosevalue == 10)
            break;
        switch (choosevalue)
        {
        case KEY_LEFT:
            highlight--;
            break;
        case KEY_RIGHT:
            highlight++;
            break;
        case KEY_UP:
            destwin(win);
            return -1;
        case KEY_DOWN:
            destwin(win);
            return -1;
        default:
            break;
        }
        if (highlight == array.size)
            highlight = 0;
        else if (highlight == -1)
            highlight = array.size - 1;
    }
    destwin(win);
    return highlight;
}

int main()
{
    noecho();
    std::vector<dint> arrays;
    std::vector<WINDOW *> windows;
    initscr();
    int xsize = 30, ysize = 15, xstartarrwin = xsize + 1;
    std::list<string> menuitems = {"Create array"};
    std::list<string> menufunctions = {"Resize", "Change value", "Sort", "Randomize", "Delete"};
    std::list<string> menuarritems;
    bool flag = 1;
    while (true)
    {
        if (arrays.size() != 0)
        {
            menuarritemschanged(menuarritems, arrays);
            winarr(xstartarrwin, menuarritems, arrays, windows);
        }
        int choice = wchoosemenu(ysize, xsize, menuitems);
        switch (choice)
        {
        case 0:
        {
            int result = wgetmenu(ysize, xsize, "Enter size");
            arrays.push_back(dint(result));
            if (flag)
            {
                menuitems.insert(++menuitems.begin(), "Change array");
                flag = !flag;
            }
        }
        break;
        case 1:
        {
            int choosemenu = wchoosemenu(ysize, xsize, menuarritems);
            if (choosemenu == -1)
                break;
            int choosefunc = wchoosemenu(ysize, xsize, menufunctions);
            if (choosefunc == -1)
                break;
            switch (choosefunc)
            {
            case 0: // resize
            {
                int newsize = wgetmenu(ysize, xsize, "Enter new size");
                arrays[choosemenu].resize(newsize);
            }
            break;
            case 1: // read
            {
                int highlight = 0;
                while (true)
                {
                    int choosearrindex = wselectitem(ysize, xsize, windows[choosemenu], arrays[choosemenu]);
                    if (choosearrindex == -1)
                    {
                        break;
                    }
                    int newval = wgetmenu(ysize, xsize, "Enter new value");
                    arrays[choosemenu][choosearrindex] = newval;
                    winarr(xstartarrwin, menuarritems, arrays, windows);
                }
            }
            break;
            case 2:
            {
                int chooseprofile = wchoosemenu(ysize, xsize, {"From max to min", "From min to max"});
                arrays[choosemenu].sort((profile)chooseprofile);
            }
            break;  // sort
            case 3: // reandomize
            {
                int powerten = wgetmenu(ysize, xsize, "How big values you want(enter power of 10)");
            }
            break;
            case 4:
                break; // delete
            default:
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