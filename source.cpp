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
    for (int i = 0; i < items.size(); i++)
    {
        winds.push_back(window(mainwindow, POS_RIGHT, (int)((double)i * 4.25), 4, (sizearrsymbols(items[i]) < 17 ? 17 : sizearrsymbols(items[i]))));
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
    window mw(0, 0, 10, 25);
    std::vector<dint> arrs;
    std::vector<window> ws;
    std::list<string> menuitems = {"Create array"};
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
                        ws[chmenu].winresize((sizearrsymbols(arrs[chmenu]) < 17 ? 17 : sizearrsymbols(arrs[chmenu])));
                        ws[chmenu].winrefresh(arrs[chmenu], chmenu);
                    }
                    break;
                    case 1: // read
                    {
                        while (true)
                        {
                            int choosearrindex = ws[chmenu].addselect(arrs[chmenu]);
                            if (choosearrindex == INT_BACK)
                            {
                                winarr(mw, menuarritems, arrs, ws);
                                break;
                            }
                            int newval = mw.addgetmenu("Enter new value");
                            arrs[chmenu][choosearrindex] = newval;
                            ws[chmenu].winresize((sizearrsymbols(arrs[chmenu]) < 17 ? 17 : sizearrsymbols(arrs[chmenu])));
                            ws[chmenu].winrefresh(arrs[chmenu], chmenu);
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
                        ws[chmenu].winresize((sizearrsymbols(arrs[chmenu]) < 17 ? 17 : sizearrsymbols(arrs[chmenu])));
                        ws[chmenu].winrefresh(arrs[chmenu], chmenu);
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
