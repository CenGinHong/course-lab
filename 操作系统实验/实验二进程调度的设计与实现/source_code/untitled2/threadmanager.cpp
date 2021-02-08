#include "threadmanager.h"


ThreadManager::ThreadManager()
{
    adj = new PCB[MAXPRIORITY];	//创建50个就绪队列，即长度为50的邻接表
    for (int i = 0; i < MAXPRIORITY; i++) {
        adj[i].next = nullptr;	//第一个为附加头节点，置空
    }
    pidarray=new bool[MAXPID+1];    //初始化标识符数组
    for(int i=0;i<MAXPID;i++){
        pidarray[i]=true;
    }
    QTime time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000); //重置随机数种子
}


ThreadManager::~ThreadManager()
{
    for (int i = 0; i < MAXPRIORITY; i++) { //删除邻接表内容
        PCB* cur = adj[i].next;
        while (cur != nullptr) {
            adj[i].next = cur->next;
            delete cur;
            cur = adj[i].next;
        }
    }

    delete adj; //删除邻接表
}

bool ThreadManager::newThread()
{
    for (int i = 1; i < MAXPID; i++) {
        if (pidarray[i]) {
            PCB* cur = new PCB();
            cur->pid = i;	//插入进程号
            pidarray[i] = false;	//该进程号亦被占用
            cur->priority = qrand() % 50;	//生成0-49的优先级
            cur->life = qrand() % 5 + 1;	//生成0-5的生命周期
            cur->status = "ready";
            insThread(cur);	//插入对应优先级的就绪队列
            return true;
        }
    }
    return false;	//pid已用完
}

void ThreadManager::runThread()
{
    PCB* cur = nullptr;
    for (int i = MAXPRIORITY-1; i >= 0; i--) {
        if (adj[i].next != nullptr) {
            cur = adj[i].next;
            cur->status = "run";	//更改状态为执行
            cur->run();				//延时模拟执行
            adj[i].next = cur->next;	//脱离队列，重新插入
            cur->priority /= 2;		//优先级减半
            cur->life--;			//生命周期减一
            if (cur->life > 0) {
                cur->status = "ready";
                insThread(cur);		//重新插入新就绪队列
            }
            else {
                pidarray[cur->pid] = true;	//归还pid
                delete cur;
            }
            break;
        }
    }
}

void ThreadManager::insThread(PCB * newPro)
{
    PCB* cur = &(adj[newPro->priority]);	//定位到对应就绪队列的附加头节点处
    while (cur->next != nullptr) {
        cur = cur->next;	//定位到队列末尾
    }
    cur->next = newPro;	//插入到队列尾部
    newPro->next = nullptr;
}
