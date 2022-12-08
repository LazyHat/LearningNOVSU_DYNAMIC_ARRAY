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
    return arr.size() + size + 1;
}

void winarr(window mainwindow, std::list<string> &menuarritems, std::vector<dint> items, std::vector<window> &winds)
{
    for (int i = 0; i < winds.size(); i++)
    {
        winds[i].destwin();
    }
    winds.clear();
    int countw = (mainwindow.w->_maxy + 1) / 4;
    int itemssize = items.size();
    for (int i = 0; i <= itemssize / countw; i++)
    {
        for (int j = 0; j < items.size() - countw * i && j < countw; j++)
        {
            if (i == 0)
            {
                winds.push_back(window(mainwindow, j * 4, 4, (sizearrsymbols(items[j]) < 17 ? 17 : sizearrsymbols(items[j]))));
            }
            else
            {
                winds.push_back(window(winds[j + (i - 1) * countw], (sizearrsymbols(items[j + i * countw]) < 17 ? 17 : sizearrsymbols(items[j + i * countw]))));
            }
        }
    }
    for (int i = 0; i < items.size(); i++)
    {
        winds[i].winrefresh(items[i], i);
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

int main()
{
    initscr();
    noecho();
    curs_set(0);
    window mw(0, 0, 20, 26);
    std::vector<dint> arrs;
    std::vector<window> ws;
    std::list<string> menuitems = {"Create array", "Change size of grid"};
    std::list<string> menufunctions = {"Resize", "Change values", "Sort", "Randomize", "Delete"};
    std::list<string> menuarritems;
    bool flag = true;
    while (true)
    {
        if (!flag && arrs.size() == 0)
        {
            menuitems.pop_back();
            flag = true;
        }
        switch (mw.addchsmenu(menuitems, {WORD_EXIT}))
        {
        case 0:
        {
            arrs.push_back(dint(mw.addgetmenu("Enter size")));
            winarr(mw, menuarritems, arrs, ws);
            menuarritemschanged(menuarritems, arrs);
            if (flag)
            {
                menuitems.push_back("Change array");
                flag = false;
            }
        }
        break;
        case 1:
        {
            int newsize = mw.addgetmenu("Set size(Default - 20)");
            mw.winresizey(newsize);
            winarr(mw, menuarritems, arrs, ws);
        }
        break;
        case 2:
        {
            bool stop = true;
            while (stop)
            {
                int chmenu = mw.addchsmenu(menuarritems, {WORD_BACK, WORD_EXIT});
                if (chmenu == INT_BACK)
                    break;
                while (stop)
                {
                    int chfunc = mw.addchsmenu(menufunctions, {WORD_BACK, WORD_BACKTM, WORD_EXIT});
                    if (chfunc == INT_BACK)
                    {
                        break;
                    }
                    else if (chfunc == INT_BACKTM)
                    {
                        stop = false;
                        break;
                    }
                    switch (chfunc)
                    {
                    case 0: // resize
                    {
                        int newsize = mw.addgetmenu("Enter new size");
                        arrs[chmenu].resize(newsize);
                        winarr(mw, menuarritems, arrs, ws);
                    }
                    break;
                    case 1: // read
                    {
                        while (true)
                        {
                            mw.mvprint(1, 1, "Select element");
                            mw.mvprint(2, 1, "RIGHT/LEFT - select");
                            mw.mvprint(3, 1, "UP/DOWN - BACK");
                            mw.winrefresh();
                            int choosearrindex = ws[chmenu].addselect(arrs[chmenu]);
                            mw.clear();
                            if (choosearrindex == INT_BACK)
                            {
                                winarr(mw, menuarritems, arrs, ws);
                                break;
                            }
                            int newval = mw.addgetmenu("Enter new value");
                            arrs[chmenu][choosearrindex] = newval;
                            winarr(mw, menuarritems, arrs, ws);
                        }
                    }
                    break;
                    case 2: // sort
                    {
                        int chooseprofile = mw.addchsmenu({"From max to min", "From min to max"}, {WORD_BACK, WORD_BACKTM, WORD_EXIT});
                        if (chooseprofile == -1)
                            break;
                        arrs[chmenu].sort((profile)chooseprofile);
                        ws[chmenu].winrefresh(arrs[chmenu], chmenu);
                    }
                    break;
                    case 3: // reandomize
                    {
                        int powerten = mw.addgetmenu("How big values you want(enter power of 10)");
                        arrs[chmenu].rand(powerten);
                        winarr(mw, menuarritems, arrs, ws);
                    }
                    break;
                    case 4: // delete
                    {
                        std::vector<dint>::iterator iter = arrs.begin();
                        std::advance(iter, chmenu);
                        arrs[chmenu].del();
                        arrs.erase(iter);
                        winarr(mw, menuarritems, arrs, ws);
                        menuarritemschanged(menuarritems, arrs);
                        stop = false;
                    }
                    break;
                    default:
                        stop = false;
                        break;
                    }
                }
            }
        }
        break;
        }
    }
    getch();
    endwin();
}
