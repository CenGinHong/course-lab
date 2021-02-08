#pragma once
#include "pcb.h"
#include <QTime>
#define MAXPRIORITY 50	//优先级取值0-49
#define MAXPID 100		//进程号取值1-100
class ThreadManager
{
private:
    bool *pidarray;             //记录pid的使用情况
    PCB *adj;					//邻接表的头节点
public:
    ThreadManager();
    ~ThreadManager();
    bool newThread();			//新建进程
    void runThread();				//进行一次进程调度
    void insThread(PCB* cur);	//插入进程到对应就绪队列
    friend class MainWindow;
};
