#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <list>

// ========== 配置常量 ==========
#define SYNC_BUFFER_NUM 6           // 环形缓冲区大小
#define MAX_FRAMES 20               // 总共处理的帧数

// ========== 简化的数据结构 ==========
struct FrameData {
    int frame_num;                  // 帧号
    char data[256];                 // 模拟数据

    FrameData() : frame_num(-1) {
        memset(data, 0, sizeof(data));
    }

    FrameData(int num) : frame_num(num) {
        sprintf_s(data, "Frame %d data", num);
    }
};

// ========== 简化的线程管理类 ==========
class SimpleThreads {
public:
    // 三个信号量
    HANDLE m_SEM_Recv;              // 接收线程可用缓冲区
    HANDLE m_SEM_Preproc;           // 预处理线程任务队列
    HANDLE m_SEM_Compute;           // 计算线程任务队列

    // 三个线程的帧号
    volatile int m_nPingnumRecv;
    volatile int m_nPingnumPreproc;
    volatile int m_nPingnumCompute;

    // 环形缓冲区 (存储6个帧数据指针)
    FrameData* pFrameBuffer[SYNC_BUFFER_NUM];

    // 实际数据存储列表 (模拟pdatalist)
    std::list<FrameData> dataList;

    // 线程句柄
    HANDLE hThreadRecv;
    HANDLE hThreadPreproc;
    HANDLE hThreadCompute;

    // 终止信号
    HANDLE hEventStop;

    SimpleThreads() {
        // 初始化信号量
        m_SEM_Recv = CreateSemaphore(NULL, SYNC_BUFFER_NUM, SYNC_BUFFER_NUM, NULL);
        m_SEM_Preproc = CreateSemaphore(NULL, 0, SYNC_BUFFER_NUM, NULL);
        m_SEM_Compute = CreateSemaphore(NULL, 0, SYNC_BUFFER_NUM, NULL);

        // 初始化帧号
        m_nPingnumRecv = 0;
        m_nPingnumPreproc = 0;
        m_nPingnumCompute = 0;

        // 初始化缓冲区
        for (int i = 0; i < SYNC_BUFFER_NUM; i++) {
            pFrameBuffer[i] = nullptr;
        }

        // 创建终止事件
        hEventStop = CreateEvent(NULL, TRUE, FALSE, NULL);
    }

    ~SimpleThreads() {
        CloseHandle(m_SEM_Recv);
        CloseHandle(m_SEM_Preproc);
        CloseHandle(m_SEM_Compute);
        CloseHandle(hEventStop);
    }

    void Start();
    void Stop();

    static UINT WINAPI ThreadRecv(LPVOID param);
    static UINT WINAPI ThreadPreproc(LPVOID param);
    static UINT WINAPI ThreadCompute(LPVOID param);
};

// ========== 线程1: 接收线程 ==========
UINT WINAPI SimpleThreads::ThreadRecv(LPVOID param) {
    SimpleThreads* pThis = (SimpleThreads*)param;

    printf("[ThreadRecv] 启动\n");

    while (pThis->m_nPingnumRecv < MAX_FRAMES) {
        // 检查终止信号
        if (WaitForSingleObject(pThis->hEventStop, 0) == WAIT_OBJECT_0)
            break;

        // ========== 等待缓冲区可用 ==========
        printf("[ThreadRecv] 等待 m_SEM_Recv (当前帧号=%d)...\n", pThis->m_nPingnumRecv);
        WaitForSingleObject(pThis->m_SEM_Recv, INFINITE);

        int ping_num = pThis->m_nPingnumRecv;
        int ping_num_sync = ping_num % SYNC_BUFFER_NUM;

        printf("[ThreadRecv] 接收帧 %d (缓冲区索引=%d)\n", ping_num, ping_num_sync);

        // ========== 模拟接收数据 ==========
        Sleep(50);  // 模拟硬件延迟

        // 添加到数据列表
        pThis->dataList.push_back(FrameData(ping_num));

        // 更新缓冲区指针 (指向列表最后一个元素)
        auto it = pThis->dataList.end();
        --it;
        pThis->pFrameBuffer[ping_num_sync] = &(*it);

        printf("[ThreadRecv] 帧 %d 接收完成,通知 ThreadPreproc\n", ping_num);

        // ========== 通知预处理线程 ==========
        ReleaseSemaphore(pThis->m_SEM_Preproc, 1, NULL);

        // ========== 帧号自增 ==========
        pThis->m_nPingnumRecv++;
    }

    printf("[ThreadRecv] 退出\n");
    return 0;
}

// ========== 线程2: 预处理线程 ==========
UINT WINAPI SimpleThreads::ThreadPreproc(LPVOID param) {
    SimpleThreads* pThis = (SimpleThreads*)param;

    printf("[ThreadPreproc] 启动\n");

    while (pThis->m_nPingnumPreproc < MAX_FRAMES) {
        // 检查终止信号
        if (WaitForSingleObject(pThis->hEventStop, 0) == WAIT_OBJECT_0)
            break;

        // ========== 等待接收线程通知 ==========
        printf("[ThreadPreproc] 等待 m_SEM_Preproc (当前帧号=%d)...\n", pThis->m_nPingnumPreproc);
        WaitForSingleObject(pThis->m_SEM_Preproc, INFINITE);

        int ping_num = pThis->m_nPingnumPreproc;
        int ping_num_sync = ping_num % SYNC_BUFFER_NUM;

        printf("[ThreadPreproc] 预处理帧 %d (缓冲区索引=%d)\n", ping_num, ping_num_sync);

        // ========== 模拟预处理 ==========
        Sleep(30);  // 模拟预处理耗时

        FrameData* pFrame = pThis->pFrameBuffer[ping_num_sync];
        if (pFrame) {
            printf("[ThreadPreproc] 帧 %d 数据: %s\n", ping_num, pFrame->data);
        }

        printf("[ThreadPreproc] 帧 %d 预处理完成,通知 ThreadCompute\n", ping_num);

        // ========== 通知计算线程 ==========
        ReleaseSemaphore(pThis->m_SEM_Compute, 1, NULL);

        // ========== 帧号自增 ==========
        pThis->m_nPingnumPreproc++;
    }

    printf("[ThreadPreproc] 退出\n");
    return 0;
}

// ========== 线程3: 计算线程 ==========
UINT WINAPI SimpleThreads::ThreadCompute(LPVOID param) {
    SimpleThreads* pThis = (SimpleThreads*)param;

    printf("[ThreadCompute] 启动\n");

    while (pThis->m_nPingnumCompute < MAX_FRAMES) {
        // 检查终止信号
        if (WaitForSingleObject(pThis->hEventStop, 0) == WAIT_OBJECT_0)
            break;

        // ========== 等待预处理线程通知 ==========
        printf("[ThreadCompute] 等待 m_SEM_Compute (当前帧号=%d)...\n", pThis->m_nPingnumCompute);
        WaitForSingleObject(pThis->m_SEM_Compute, INFINITE);

        int ping_num = pThis->m_nPingnumCompute;
        int ping_num_sync = ping_num % SYNC_BUFFER_NUM;

        printf("[ThreadCompute] 计算帧 %d (缓冲区索引=%d)\n", ping_num, ping_num_sync);

        // ========== 模拟计算 ==========
        Sleep(40);  // 模拟计算耗时

        FrameData* pFrame = pThis->pFrameBuffer[ping_num_sync];
        if (pFrame) {
            printf("[ThreadCompute] 帧 %d 计算完成,结果: %s (处理完成)\n",
                ping_num, pFrame->data);
        }

        // ========== 释放缓冲区给接收线程 ==========
        printf("[ThreadCompute] 释放缓冲区索引 %d,通知 ThreadRecv\n", ping_num_sync);
        ReleaseSemaphore(pThis->m_SEM_Recv, 1, NULL);

        // ========== 帧号自增 ==========
        pThis->m_nPingnumCompute++;
    }

    printf("[ThreadCompute] 退出\n");
    return 0;
}

// ========== 启动线程 ==========
void SimpleThreads::Start() {
    printf("========== 启动三个线程 ==========\n");
    printf("环形缓冲区大小: %d\n", SYNC_BUFFER_NUM);
    printf("总处理帧数: %d\n\n", MAX_FRAMES);

    // 创建三个线程
    hThreadRecv = (HANDLE)_beginthreadex(NULL, 0, ThreadRecv, this, 0, NULL);
    hThreadPreproc = (HANDLE)_beginthreadex(NULL, 0, ThreadPreproc, this, 0, NULL);
    hThreadCompute = (HANDLE)_beginthreadex(NULL, 0, ThreadCompute, this, 0, NULL);
}

// ========== 停止线程 ==========
void SimpleThreads::Stop() {
    printf("\n========== 停止线程 ==========\n");

    // 设置终止信号
    SetEvent(hEventStop);

    // 释放信号量,让线程可以退出
    ReleaseSemaphore(m_SEM_Preproc, 1, NULL);
    ReleaseSemaphore(m_SEM_Compute, 1, NULL);
    ReleaseSemaphore(m_SEM_Recv, 1, NULL);

    // 等待线程退出
    HANDLE handles[3] = { hThreadRecv, hThreadPreproc, hThreadCompute };
    WaitForMultipleObjects(3, handles, TRUE, INFINITE);

    CloseHandle(hThreadRecv);
    CloseHandle(hThreadPreproc);
    CloseHandle(hThreadCompute);

    printf("所有线程已退出\n");
    printf("数据列表大小: %d\n", (int)dataList.size());
}

// ========== 主函数 ==========
int main() {
    printf("====================================\n");
    printf("  简化版三线程同步示例\n");
    printf("  演示环形缓冲区和信号量机制\n");
    printf("====================================\n\n");

    SimpleThreads threads;

    // 启动线程
    threads.Start();

    // 等待所有帧处理完成
    while (threads.m_nPingnumCompute < MAX_FRAMES) {
        Sleep(100);

        // 打印进度
        printf("\n[进度] Recv=%d, Preproc=%d, Compute=%d\n",
            threads.m_nPingnumRecv,
            threads.m_nPingnumPreproc,
            threads.m_nPingnumCompute);
    }

    // 停止线程
    threads.Stop();

    printf("\n====================================\n");
    printf("  演示完成!\n");
    printf("====================================\n");

    system("pause");
    return 0;
}