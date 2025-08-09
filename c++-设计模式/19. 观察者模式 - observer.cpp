#include <iostream>
#include "NewsAgency-19.h"
#include "Observer-19.h"
using namespace std;

#if 0
int main()
{
    // 发布者
    NewsAgency* news1 = new Morgans;
    NewsAgency* news2 = new Gossip;
    // 观察者(订阅者)
    Dragon* dragon = new Dragon(news1, "蒙奇·D·龙");
    Shanks* shanks = new Shanks(news1, "香克斯");
    Bartolomeo* barto = new Bartolomeo(news2, "巴托洛米奥");
    // 由发布者推送消息
    news1->notify("蒙奇·D·路飞成为新世界的新的四皇之一, 赏金30亿贝里!!!");
    cout << "=====================" << endl;
    news2->notify("女帝汉库克想要嫁给路飞, 给路飞生猴子, 哈哈哈...");

    delete news1;
    delete news2;
    delete dragon;
    delete shanks;
    delete barto;

    return 0;
}
#endif