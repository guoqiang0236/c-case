/*
 * 设计模式学习——适配器模式（Adapter Pattern）
 * -------------------------------------------------
 * 适配器模式是一种结构型设计模式，主要用于解决接口不兼容的问题。
 * 它通过引入一个适配器类，将一个类的接口转换成客户端期望的另一个接口，使原本由于接口不匹配而无法一起工作的类能够协同工作。
 * 适配器模式分为类适配器和对象适配器两种实现方式。
 * 本示例分别演示了这两种方式：
 * 1. 类适配器（OutletAdapter）：通过多重继承实现接口转换。
 * 2. 对象适配器（OutletObjAdapter）：通过组合方式实现接口转换。
 */

#include <iostream>
using namespace std;

// 三插座接口，提供三插功能
class ThreePauseOutlet
{
public:
    void doThreePause() {
        cout << "ThreePauseOutlet::doThreePause()" << endl;
    }
};

// 两插座抽象接口，定义统一插入方法
class TwoPauseOutlet
{
public:
    virtual void doPlug() = 0;
};

// 类适配器：通过多重继承实现接口适配
class OutletAdapter : public TwoPauseOutlet, public ThreePauseOutlet
{
    void doPlug() override {
        doCovertor();      // 转换器逻辑
        doThreePause();    // 调用三插座功能
    }

    void doCovertor() {
        std::cout << "我们正在将三插头转换成两插头" << std::endl;
    }
};

// 对象适配器：通过组合方式实现接口适配
class OutletObjAdapter : public TwoPauseOutlet
{
public:
    // 构造函数，传入三插座对象
    OutletObjAdapter(ThreePauseOutlet* obj) :m_pOutlet(obj)
    {

    }

    void doPlug() override {
        doCovertor();           // 转换器逻辑
        m_pOutlet->doThreePause(); // 调用三插座功能
    }
private:
    void doCovertor() {
        std::cout << "我们正在将三插头转换成两插头" << std::endl;
    }
    ThreePauseOutlet* m_pOutlet; // 持有三插座对象指针
};

int main() {
    // 使用类适配器
    TwoPauseOutlet* testoutlet = new OutletAdapter();
    testoutlet->doPlug();

    // 使用对象适配器
    OutletObjAdapter* testoutletobj = new OutletObjAdapter(new ThreePauseOutlet());
    testoutletobj->doPlug();
    system("pause");
    return 0;
}