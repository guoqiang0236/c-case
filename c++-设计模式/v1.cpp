#include <iostream>
#include <string>
using namespace std;

#if 0
class NiuLang
{
public:
    void searchNiu();
    void meeting(string name);
    void getMarried(string name);
    string getNiu();
    string getName();
private:
    string m_niu;
};

class ZhiNv
{
public:
    void searchFangChe();
    void meeting(string name);
    void getMarried(string name);
    string getFangChe();
    string getName();
private:
    string m_fangChe;
};

class HongNiang
{
public:
    void doSomething(string niu, string fangChe);
    void seekHelp(string name);     // 求助: 找牛郎借牛, 找织女借纺车
};

/*
故事梗概:
    很久很久就以前, 天上的织女思凡下界, 看上了在河边放牛的牛郎。
    柳树精看穿了织女的心思，于是向成全他们。
    柳树精偷偷牵走了牛郎的牛，将其栓在河边吃草。
    柳树精偷偷偷走了织女的纺车，将其放到了牛郎的牛车上
    牛郎去找牛。。。
    织女去找纺车。。。
    牛郎和织女见面，一见钟情！
    牛郎和织女结婚了！
*/
int main()
{
    ////////////////// 面向过程 //////////////////
    qianNiu("HongNiang", "XiaoHeBian");
    zhuangChe("HongNiang", "FangChe");
    searchNiu("NiuLang");
    searchFangChe("ZhiNv");
    meet("NiuLang", "ZhiNv");
    getMarried("NiuLang", "ZhiNv");

    ////////////////// 面向对象 //////////////////
    NiuLang* niuLang = new NiuLang;
    ZhiNv* zhiNv = new ZhiNv;
    HongNiang* hongNiang = new HongNiang;
    string niu = niuLang->getNiu();
    string fangChe = zhiNv->getFangChe();
    hongNiang->doSomething(niu, fangChe);
    hongNiang->seekHelp(niuLang->getName());
    hongNiang->seekHelp(zhiNv->getName());
    niuLang->searchNiu();
    zhiNv->searchFangChe();
    niuLang->meeting(zhiNv->getName());
    zhiNv->meeting(niuLang->getName());
    niuLang->getMarried(zhiNv->getName());
    zhiNv->getMarried(niuLang->getName());
    return 0;
}
#endif
