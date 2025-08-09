#include <iostream>
using namespace std;

#if 0
class Person
{
public:
    void meeting(string name) 
    {
        cout << "遇见了" << name << endl;
    }
    void getMarried() 
    {
        cout << "哈哈, 成亲了, 么么哒!" << endl;
    }
};

class NiuLang : public Person
{
public:
    void searchNiu() 
    {
        cout << "牛郎去找牛了..." << endl;
    }
    string getNiu() 
    {
        return m_niu;
    }
    string getName()
    {
        return "二牛";
    }
private:
    string m_niu;
};

class ZhiNv : public Person
{
public:
    void searchFangChe()
    {
        cout << "织女去找纺车了..." << endl;
    }
    string getFangChe()
    {
        return m_fangChe;
    }
    string getName()
    {
        return "巧儿";
    }
private:
    string m_fangChe;
};

class HongNiang
{
public:
    HongNiang(NiuLang* niuLang, ZhiNv* zhiNv) : 
        m_niuLang(niuLang), m_zhiNv(zhiNv) {}
    void doSomething()
    {
        cout << "牵牛到河边" << m_niuLang->getNiu() << endl;
        cout << "纺车装牛车上" << m_zhiNv->getFangChe() << endl;
    }
    void seekHelp()
    {
        m_niuLang->searchNiu();
        m_zhiNv->searchFangChe();
    }
private:
    NiuLang* m_niuLang = nullptr;
    ZhiNv* m_zhiNv = nullptr;
};

int main()
{
    NiuLang* niuLang = new NiuLang;
    ZhiNv* zhiNv = new ZhiNv;
    HongNiang* hongNiang = new HongNiang(niuLang, zhiNv);
    hongNiang->doSomething();
    hongNiang->seekHelp();
    niuLang->meeting(zhiNv->getName());
    zhiNv->meeting(niuLang->getName());
    niuLang->getMarried();
    zhiNv->getMarried();

    return 0;
}
#endif