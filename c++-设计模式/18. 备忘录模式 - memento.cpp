#include <iostream>
#include <map>
#include <vector>
using namespace std;

// 数据类
class History
{
public:
    History(string msg) : m_msg(msg) {}
    string getHistory()
    {
        return m_msg;
    }
private:
    string m_msg;
};

// 事件的亲历者 - 脚盆鸡
class JiaoPenJi
{
public:
    // 脚盆鸡做的事情
    void setState(string msg)
    {
        m_msg = msg;
    }
    // 记录历史 - 封装数据
    History* saveHistory()
    {
        return new History(m_msg);
    }
    // 得到历史信息 -> 不负责加载历史信息, 具体的加载动作是有记录者对象完成的
    void getStateFromHistory(History* history)
    {
        m_msg = history->getHistory();
    }
    string getState()
    {
        return m_msg;
    }
    // 被打
    void beiDaddyDa()
    {
        cout << "脚盆鸡被兔子狠狠地揍了又揍, 终于承认了它们之前不承认的这些罪行: " << endl;
    }
private:
    string m_msg;
};

// 事件(数据)的记录者
class Recorder
{
public:
    void addHistory(int index, History* history)
    {
        m_history.insert(make_pair(index, history));
    }
    History* getHistory(int index)
    {
        if (m_history.find(index) != m_history.end())
        {
            return m_history[index];
        }
        return nullptr;
    }
private:
    map<int, History*> m_history;
};

#if 0
int main()
{
    vector<string> msg{
        "不承认偷了中国的中医!!!",
        "不承认发动了侵华战争!!!",
        "不承认南京大屠杀!!!!",
        "不承认琉球群岛和钓鱼岛是中国的领土!!!",
        "不承认731部队的细菌和人体试验!!!",
        "不承认对我国妇女做出畜生行为!!!",
        "不承认从中国掠夺的数以亿计的资源和数以万计的文物!!!",
        "我干的龌龊事儿罄竹难书, 就是不承认......"
    };
    JiaoPenJi* jiaopen = new JiaoPenJi;
    Recorder* recorder = new Recorder;
    for (int i = 0; i < msg.size(); ++i)
    {
        jiaopen->setState(msg.at(i));
        recorder->addHistory(i, jiaopen->saveHistory());
    }
    jiaopen->beiDaddyDa();
    for (int i = 0; i < msg.size(); ++i)
    {
        jiaopen->getStateFromHistory(recorder->getHistory(i));
        cout << "   --  " << jiaopen->getState() << endl;
    }
    return 0;
}
#endif