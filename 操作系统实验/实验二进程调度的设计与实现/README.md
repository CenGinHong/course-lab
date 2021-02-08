## 实验名称

进程调度的设计与实现

## 实验目的

1. 综合应用下列知识点设计并实现操作系统的进程调度：邻接表，布尔数组，非阻塞输入，图形用户界面 GUI，进程控制块，进程状态转换，多级反馈队列进程调度算法。
2. 加深理解操作系统进程调度的过程。
3. 加深理解多级反馈队列进程调度算法。

## 实验内容与要求

1. 采用一种熟悉的语言，如 C、PASCAL 或 C++等，编制程序，最好关键
2. 代码采用 C/C++，界面设计可采用其它自己喜欢的语言。
3. 采用多级反馈队列调度算法进行进程调度。
4. 每个进程对应一个 PCB。在 PCB 中包括进程标识符 pid、进程的状态标识 status、进程优先级 priority、进程的队列指针 next 和表示进程生命周期的数据项 life（在实际系统中不包括该项）。
5. 创建进程时即创建一个 PCB，各个进程的 pid 都是唯一的，pid 是在 1到 100 范围内的一个整数。可以创建一个下标为 1 到 100 的布尔数组，“真”表示下标对应的进程标识号是空闲的，“假”表示下标对应的进程标识号已分配给某个进程。
6. 进程状态 status 的取值为“就绪 ready”或“运行 run”，刚创建时，状态为“ready”。被进程调度程序选中后变为“run”。
7. 进程优先级 priority 是 0 到 49 范围内的一个随机整数。
8. 进程生命周期 life 是 1 到 5 范围内的一个随机整数。
9. 初始化时，创建一个邻接表，包含 50 个就绪队列，各就绪队列的进程优先级 priority 分别是 0 到 49。
10. 为了模拟用户动态提交任务的过程，要求动态创建进程。进入进程调度循环后，每次按 ctrl+f 即动态创建一个进程，然后将该 PCB 插入就绪队列中。按 ctrl+q 退出进程调度循环。
11. 在进程调度循环中，每次选择优先级最大的就绪进程来执行。将其状态从就绪变为运行，通过延时一段时间来模拟该进程执行一个时间片的过程，然后优先级减半，生命周期减一。设计图形用户界面 GUI，在窗口中显示该进程和其他所有进程的 PCB 内容。如果将该运行进程的生命周期不为 0，则重新把它变为就绪状态，插入就绪队列中；否则该进程执行完成，撤消其 PCB。以上为一次进程调度循环。
12. 在上机实现该程序之后，要求写出实验报告，其中包括实验名称、实验目的、实验内容、程序的主要流程图、实验心得和主要源程序清单等。

## 实验流程图

![image-20210208121425124](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208121425124.png)

## 实验设计

### 实验分析

1. 采用一种熟悉的语言，如 C、PASCAL 或 C++等编制程序。[1]
2. 综合使用使用邻接表、布尔数组等数据结构实现该实验。[2-3]
3. 采用多级反馈队列调度算法进行进程调度。[4]
4. 使用按键操作程创建、调度、退出进程调度。并用图形界面进行显示。

### 实现分析

1. 创建PCB类用于作为进程的控制块，包含进程状态 status，进程标识符 pid，进程优先级 priority，进程生命周期 life，进程队列指针next。
2. 进程调度类ProcessManager，包含数组pidarray[]，用邻接表实现的邻接表优先级队列指针adj,新建函数进程函数newProcess()，调度进程函数 proRun()，插入进程到适当队列函数insertPro();				
3. cGUI部分使用Qt框架中的QTableWidget 表单类创建窗口及表单来画出优先级队列，并通过重写键盘响应时间来发出程序指令

### 具体实现

##### 进程控制块PCB

```
struct PCB
{
	int pid;		//1-100的整数
	string status;	//“就绪 ready”或“运行 run”，
	int  priority;	//是 0 到 49 范围内的一个随机整数
	PCB* next;		//进程的队列指针 next
	int life;		//1 到 5 范围内的一个随机整数
	void run() {
		_sleep(1000);//延时模拟执行
	}
};
```

#####  进程调度类

```
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
```



##### 主要功能函数源代码

```
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
```

##### GUI部分

###### MainWindow.h

```
#ifndef MAINWINDOW_H

\#define MAINWINDOW_H

 

\#include <QMainWindow>

\#include "threadmanager.h"

\#include <QTableWidget>

\#include <QKeyEvent>

 

namespace ***\*Ui\**** {

class ***\*MainWindow\****;

}

 

class ***\*MainWindow\**** : public QMainWindow

{

  Q_OBJECT

 

public:

  explicit ***\*MainWindow\****(QWidget *parent = nullptr);

  void ***\*update\****() const;   //更新表单内容

  ~***\**MainWindow\**\***();

 

private:

  Ui::MainWindow *ui;

  QTableWidget *qtablewidget;

  ThreadManager *threadmanager;

 

protected:

  void ***\**keyPressEvent\**\***(QKeyEvent *event);  //键盘事件响应

};

 

\#endif // MAINWINDOW_H

 

 

\#include "mainwindow.h"

\#include "ui_mainwindow.h"

 

 

MainWindow::***\*MainWindow\****(QWidget *parent) :

  QMainWindow(parent),

  ui(new Ui::MainWindow)

{

  ui->setupUi(this);

  qtablewidget=new QTableWidget(50,10,this);  //创建gui表单

  qtablewidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

  setCentralWidget(qtablewidget);       //使表单适应窗口

  threadmanager=new ThreadManager();     //初始化类

  qtablewidget->resizeRowsToContents();

  this->grabKeyboard();

  resize(1050,800);

}
```

 

 

 

 

 

##### MainWindow.cpp

```
MainWindow::~***\**MainWindow\**\***()

{

  delete ui;

}

 

void MainWindow::***\*update\****()const

{

  qtablewidget->clearContents();//清空原表格

  PCB *cur=new PCB();

 

  //根据队列绘制表格

  for(int i=0;i<50;i++){

​    int col=0;

​    cur=threadmanager->adj[i].next;

​    while(cur!=nullptr){

​      qtablewidget->setItem(i,col++,new QTableWidgetItem(QString::number(cur->pid)));

​      cur=cur->next;

​    }

  }

}

 

 

void MainWindow::***\**keyPressEvent\**\***(QKeyEvent *event)

{

  if((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_F)){

    if(threadmanager->newThread()){

      update();

    }

  }else if((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_A)){

    threadmanager->runThread();

    update();

  }else if((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_Q)){

    exit(0);

  }

}
```

#### 程序截图

![image-20210208121838121](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208121838121.png)

![image-20210208121841356](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208121841356.png)

## 实验心得

多级反馈队列进程调度算法是操作系统中进程调度中进程调度中较为关键的知识点，通过实验能让我进一步熟练使用C++编程语言与复习了数据结构的知识，同时对操作系统的关于多级反馈队列知识了解地更加透彻。

 实验中遇到的问题：

1. 使用QT开发图形界面时，因为对qt类的不熟悉查阅了挺多的教程。
2. 在本实验中遇到的问题因为书上没有具体的实现代码，需要到网上去查阅资料，所以又很多细节没有注意到，常常报错，出现问题时甚至要逐步跟踪的方法才能找到问题根源。

## 参考文献

1. 朱振元.《数据结构》.2003.清华大学出版社.
2. 《数据结构实验指导书》，2008，华南师范大学计算机学院自用教材
3. 翁惠玉.俞勇.《C++ 程序设计思想与方法（第3版）慕课版》2017.人民邮电出版社.
4. 汤子瀛.《计算机操作系统》.2003.西安电子科技大学出版社