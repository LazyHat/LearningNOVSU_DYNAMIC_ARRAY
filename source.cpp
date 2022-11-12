#define _CRT_RAND_S
#include "string.cpp"
#include "dint.cpp"
//#include <curses.h>

int main()
{
    // initscr();
    try
    {
        dint k(6);
        k.del();
        return 0;
    }
    catch (dintExeption &a)
    {
        a.GetErrorMessage().PrintL();
    }
    return 0;
    // endwin();
}