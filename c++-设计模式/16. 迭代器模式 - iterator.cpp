#include <iostream>
#include <vector>
#include "MyList-16.h"
#include "Iterator-16.h"
using namespace std;

#if 0
int main()
{
    vector<string> nameList{
    "烬", "奎因", "杰克", "福兹·弗", "X·德雷克",
    "黑色玛利亚", "笹木", "润媞", "佩吉万",
    "一美", "二牙", "三鬼", "四鬼", "五鬼",
    "六鬼", "七鬼", "八茶", "九忍","十鬼"
    };
    MyList ls;
    for (int i = 0; i < nameList.size(); ++i)
    {
        ls.pushFront(nameList.at(i));
    }
    // 正向遍历
    Iterator* it = ls.getIterator(false);
    cout << "凯多正向检阅队伍..." << endl;
    for (auto begin = it->first(); !it->isDone(); it->next())
    {
        cout << "   " << it->current()->name << "say: 为老大服务!!! " << endl;
    }
    delete it;
    cout << "===================" << endl;
    // 逆向遍历
    it = ls.getIterator();
    cout << "凯多正向检阅队伍..." << endl;
    for (auto begin = it->first(); !it->isDone(); it->next())
    {
        cout << "   " << it->current()->name << "say: 为老大服务!!! " << endl;
    }
    cout << "===================" << endl;

    delete it;

    return 0;
}
#endif