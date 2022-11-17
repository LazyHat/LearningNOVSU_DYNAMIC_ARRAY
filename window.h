#pragma once
#include <ncurses.h>
struct window
{
    WINDOW *win;

public:
    window(int start_y, int start_x, int size_y, int size_x);
    ~window();
};