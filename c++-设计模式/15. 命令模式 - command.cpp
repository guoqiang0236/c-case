#include <iostream>
#include <map>
#include <list>
using namespace std;

// 厨师 -> 命令的执行者, 收不到命令是不会工作的
class CookerZeff
{
public:
    void makeDSX()
    {
        cout << "开始烹饪地三鲜...";
    }
    void makeYXRS()
    {
        cout << "开始烹饪鱼香肉丝...";
    }
    void makeGBJD()
    {
        cout << "开始烹饪宫保鸡丁...";
    }
    void makeHSPG()
    {
        cout << "开始烹饪红烧排骨...";
    }
};

// 命令
class AbstractCommand
{
public:
    AbstractCommand(CookerZeff* zeff) :m_cooker(zeff) {}
    virtual void excute() = 0;
    virtual string name() = 0;
    virtual ~AbstractCommand() {}
protected:
    CookerZeff* m_cooker = nullptr;
};

class DSXCommand : public AbstractCommand
{
public:
    using AbstractCommand::AbstractCommand;
    void excute() override
    {
        m_cooker->makeDSX();
    }
    string name() override
    {
        return "地三鲜";
    }
};

class GBJDCommand : public AbstractCommand
{
public:
    using AbstractCommand::AbstractCommand;
    void excute() override
    {
        m_cooker->makeGBJD();
    }
    string name() override
    {
        return "宫保鸡丁";
    }
};

class YXRSCommand : public AbstractCommand
{
public:
    using AbstractCommand::AbstractCommand;
    void excute() override
    {
        m_cooker->makeYXRS();
    }
    string name() override
    {
        return "鱼香肉丝";
    }
};

class HSPGCommand : public AbstractCommand
{
public:
    using AbstractCommand::AbstractCommand;
    void excute() override
    {
        m_cooker->makeHSPG();
    }
    string name() override
    {
        return "红烧排骨";
    }
};

// 服务员
class WaiterLuffy
{
public:
    // 下单
    void setOrder(int index, AbstractCommand* command)
    {
        cout << index << "号桌点了" << command->name() << endl;
        if (command->name() == "鱼香肉丝")
        {
            cout << "没有鱼了, 做不了鱼香肉丝, 点个别的菜吧..." << endl;
            return;
        }
        if (m_cmdList.find(index) == m_cmdList.end())
        {
            list<AbstractCommand*> mylist{ command };
            m_cmdList.insert(make_pair(index, mylist));
        }
        else
        {
            m_cmdList[index].push_back(command);
        }
    }
    // 撤销订单
    void cancelOrder(int index, AbstractCommand* command)
    {
        if (m_cmdList.find(index) != m_cmdList.end())
        {
            m_cmdList[index].remove(command);
            cout << index << "号桌, 撤销了" << command->name() << endl;
        }
    }
    // 结账
    void checkOut(int index)
    {
        cout << "第[" << index << "]号桌的顾客点的菜是: 【";
        for (const auto& item : m_cmdList[index])
        {
            cout << item->name();
            if (item != m_cmdList[index].back())
            {
                cout << ",";
            }
        }
        cout << "】" << endl;
    }
    // 发送通知 -> 要求厨师执行某些命令
    void notify(int index)
    {
        for (const auto& item : m_cmdList[index])
        {
            item->excute();
            cout << index << "号桌" << endl;
        }
    }
private:
    map<int, list<AbstractCommand*>> m_cmdList;
};

#if 0
int main()
{
    CookerZeff* zeff = new CookerZeff;
    WaiterLuffy* luffy = new WaiterLuffy;

    YXRSCommand* yxrs = new YXRSCommand(zeff);
    DSXCommand* dsx = new DSXCommand(zeff);
    GBJDCommand* gbjd = new GBJDCommand(zeff);
    HSPGCommand* hspg = new HSPGCommand(zeff);

    cout << "顾客开始点餐" << endl;
    luffy->setOrder(1, yxrs);
    luffy->setOrder(1, dsx);
    luffy->setOrder(1, gbjd);
    luffy->setOrder(1, hspg);

    luffy->setOrder(2, hspg);
    luffy->setOrder(2, dsx);
    luffy->setOrder(2, gbjd);

    cout << "撤销订单=============" << endl;
    luffy->cancelOrder(1, dsx);
    cout << "开始下单 ++++++++++++++++" << endl;
    luffy->notify(1);
    luffy->notify(2);
    cout << "结账*******************" << endl;
    luffy->checkOut(1);
    luffy->checkOut(2);

    delete luffy;
    delete zeff;
    delete yxrs;
    delete dsx;
    delete gbjd;
    delete hspg;

    return 0;
}
#endif