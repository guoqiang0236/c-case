#include <iostream>
using namespace std;

#if 0
class Person
{
public:
    void meeting(Person* person)
    {
        // 相互见面
        if (m_person == nullptr)
        {
            m_person = person;
            person->meeting(this);
        }
    }
    void getMarried()
    {
        if (m_flag)
        {
            m_flag = false;
            marry();
            m_person->getMarried();
        }
    }
    virtual string getName() = 0;
    virtual void search() = 0;
    virtual string getCaiChan() = 0;
    virtual void marry() = 0;
protected:
    Person* m_person = nullptr;
    bool m_flag = true;
};

class NiuLang : public Person
{
public:
    void search() override
    {
        cout << "我的牛丢了, 我去找牛..." << endl;
    }
    string getCaiChan() override
    {
        return m_niu;
    }
    string getName() override
    {
        return "二牛";
    }
    void marry() override
    {
        cout << "我要娶织女了，没想到还能娶到这么漂亮的媳妇儿。。。" << endl;
    }
private:
    string m_niu = "五彩神牛";
};

class ZhiNv : public Person
{
public:
    void search() override
    {
        cout << "我的纺车丢了, 我去找纺车..." << endl;
    }
    string getCaiChan() override
    {
        return m_fangChe;
    }
    string getName() override
    {
        return "巧儿";
    }
    void marry() override
    {
        cout << "从天上跑下来结了个婚, 不知道什么时候被带回去。。。" << endl;
    }

private:
    string m_fangChe = "七彩虹纺车";
};

class HongNiang
{
public:
    HongNiang(Person* niuLang, Person* zhiNv) :
        m_niuLang(niuLang), m_zhiNv(zhiNv) {}
    void doSomething()
    {
        cout << "牵牛到河边" << m_niuLang->getCaiChan() << endl;
        cout << "纺车装牛车上" << m_zhiNv->getCaiChan() << endl;
    }
    void seekHelp()
    {
        m_niuLang->search();
        m_zhiNv->search();
    }
private:
    Person* m_niuLang;
    Person* m_zhiNv;
};

int main()
{
    NiuLang* niuLang = new NiuLang;
    ZhiNv* zhiNv = new ZhiNv;
    HongNiang* hongNiang = new HongNiang(niuLang, zhiNv);
    hongNiang->doSomething();
    hongNiang->seekHelp();
    niuLang->meeting(zhiNv);
    niuLang->getMarried();

    return 0;
}
#endif