#include "window.h"

window::window(int start_y, int start_x, int size_y, int size_x)
{
    this->win = newwin(size_y, size_x, start_y, start_x);
}
window::~window()
{
    if (this->win != nullptr)
    {
        wborder(this->win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        wrefresh(this->win);
        delwin(this->win);
        this->win = nullptr;
    }
}