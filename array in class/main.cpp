#include "dint.h"
#include "string.h"
#include "window.h"
#include "menu.h"

uint8_t initialize()
{
    initscr();
    noecho();
    curs_set(0);
    if (!has_colors())
    {
        exit(1);
    }
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    return 0;
}
// анимация выхода окон из главного окна
int main()
{
    initialize();
    window mw(0, 0, 15, 20, 0);
    mw.adddesign();
    mw.winrefresh();
    while (true)
    {
        int k = mw.printmenu({"first", "second", "third"});
        wprintw(mw.w, "%d", k);
        wrefresh(mw.w);
        if (k == 1)
            break;
    }
    endwin();
    return 0;
}