#include "string.cpp"
#include "dint.cpp"
#include "window.cpp"
#include <list>
#include <vector>
#include <ctime>
#include <iterator>

int sizearrsymbols(dint arr)
{
    int size = 0;
    for (int i = 0; i < arr.size(); i++)
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

void winarr(window mainwindow, std::list<string> &menuarritems, std::vector<dint> items, std::vector<window> &winds)
{
    for (int i = 0; i < winds.size(); i++)
    {
        winds[i].destwin();
    }
    winds.clear();
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].size() + 1 + sizearrsymbols(items[i]) < 16)
            winds.push_back(window(mainwindow, POS_RIGHT, (int)((double)i * 4.25), 4, 16));
        else
            winds.push_back(window(mainwindow, POS_RIGHT, (int)((double)i * 4.25), 4, items[i].size() + 1 + sizearrsymbols(items[i])));
    }
    for (int i = 0; i < items.size(); i++)
    {
        winds[i].mvprint(1, 1, string("Array " + (i + 1)) + string(" Max: " + items[i].maxelement()));
        winds[i].move(2, 1);
        for (int j = 0; j < items[i].size(); j++)
        {
            if (j != 0)
                winds[i].print(" ");
            winds[i].print(ToString(items[i][j]));
        }
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
        for (int i = 0; i < array.size(); i++)
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
        if (highlight == array.size())
            highlight = 0;
        else if (highlight == -1)
            highlight = array.size() - 1;
    }
    destwin(win);
    return highlight;
}

int main()
{
    initscr();
    noecho();
    curs_set(0);
    window mw(0, 0, 10, 20);
    std::vector<dint> arrs;
    std::vector<window> ws;
    std::list<string> menuitems = {"Create array"};
    std::list<string> menufunctions = {"Resize", "Change values", "Sort", "Randomize", "Delete"};
    std::list<string> menuarritems;
    bool flag = true;
    while (true)
    {
        switch (mw.addchoosemenu(menuitems, {WORD_EXIT}))
        {
        case 0:
        {
            arrs.push_back(dint(mw.addgetmenu("Enter size")));
            winarr(mw, menuarritems, arrs, ws);
            if (flag)
            {
                menuitems.push_back("Change array");
                flag = false;
            }
        }
        break;
        case 1:
        {
        }
        break;
        }
        getch();
        endwin();
        //         switch (choice)
        //         {
        //         case 0:
        //         {
        //             int result = wgetmenu(ysize, xsize, "Enter size");
        //             arrays.push_back(dint(result));
        //             winarr(xstartarrwin, menuarritems, arrays, windows);
        //             if (!flag)
        //             {
        //                 menuitems.insert(++menuitems.begin(), "Change array");
        //                 flag = true;
        //             }
        //         }
        //         break;
        //         case 1:
        //         {
        //             bool stop = true;
        //             while (stop)
        //             {
        //                 int choosemenu = wchoosemenu(ysize, xsize, menuarritems, false);
        //                 if (choosemenu == -1 || choosemenu == -2)
        //                     break;
        //                 while (stop)
        //                 {
        //                     int choosefunc = wchoosemenu(ysize, xsize, menufunctions, true);
        //                     if (choosefunc == -1)
        //                         break;
        //                     if (choosefunc == -2)
        //                     {
        //                         stop = false;
        //                         break;
        //                     }
        //                     switch (choosefunc)
        //                     {
        //                     case 0: // resize
        //                     {
        //                         int newsize = wgetmenu(ysize, xsize, "Enter new size");
        //                         arrays[choosemenu].resize(newsize);
        //                         winarr(xstartarrwin, menuarritems, arrays, windows);
        //                     }
        //                     break;
        //                     case 1: // read
        //                     {
        //                         int highlight = 0;
        //                         while (true)
        //                         {
        //                             int choosearrindex = wselectitem(ysize, xsize, windows[choosemenu], arrays[choosemenu]);
        //                             if (choosearrindex == -1)
        //                             {
        //                                 break;
        //                             }
        //                             int newval = wgetmenu(ysize, xsize, "Enter new value");
        //                             arrays[choosemenu][choosearrindex] = newval;
        //                             winarr(xstartarrwin, menuarritems, arrays, windows);
        //                         }
        //                     }
        //                     break;
        //                     case 2: // sort
        //                     {
        //                         int chooseprofile = wchoosemenu(ysize, xsize, {"From max to min", "From min to max"}, false);
        //                         if (chooseprofile == -1)
        //                             break;
        //                         arrays[choosemenu].sort((profile)chooseprofile);
        //                         winarr(xstartarrwin, menuarritems, arrays, windows);
        //                     }
        //                     break;
        //                     case 3: // reandomize
        //                     {
        //                         int powerten = wgetmenu(ysize, xsize, "How big values you want(enter power of 10)");
        //                         arrays[choosemenu].rand(powerten);
        //                         winarr(xstartarrwin, menuarritems, arrays, windows);
        //                     }
        //                     break;
        //                     case 4: // delete
        //                     {
        //                         std::vector<dint>::iterator iter = arrays.begin();
        //                         std::advance(iter, choosemenu);
        //                         arrays[choosemenu].del();
        //                         arrays.erase(iter);
        //                         std::vector<WINDOW *>::iterator iterw = windows.begin();
        //                         if (arrays.size() == 0)
        //                         {
        //                             winarr(xstartarrwin, menuarritems, arrays, windows);
        //                             menuitems.pop_back();
        //                             flag = false;
        //                         }
        //                         stop = false;
        //                     }
        //                     break;
        //                     default:
        //                         stop = false;
        //                         break;
        //                     }
        //                 }
        //             }
        //         }
        //         }
        //     }
    }
}
