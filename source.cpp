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

int wchoosemenu(std::list<string> items)
{
    WINDOW *w = newwin(10, 20, 0, 0);
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
    return highlight + 1;
}
int wgetmenu(string quest)
{
    WINDOW *w = newwin(10, 20, 0, 0);
    refresh();
    box(w, 0, 0);
    wrefresh(w);
    int get = 0;
    mvwprintw(w, 1, 1, "%s", quest.ToArray());
    wrefresh(w);
    move(2, 1);
    char *str;
    wgetstr(w, str);
    string s(str);
    int result;
    try
    {
        result = s.ToInt();
    }
    catch (stringExeption &a)
    {
        mvwprintw(w, 2, 1, "%s", a.GetError().ToArray());
    }
    destwin(w);
    return result;
}

int main()
{
    std::vector<dint> arrays;
    initscr();
    int choice = wchoosemenu({"Create array"});
    if (choice == 1)
    {
        int result = wgetmenu("Enter size");
        arrays.push_back(dint(result));
    }
    printw("%d", choice);
    getch();
    endwin();
}