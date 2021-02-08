## 实验名称

模拟操作系统的页面置换

## 实验目的

1. 掌握操作系统的页面置换过程，加深理解页式虚拟存储器的实现原理。
2. 掌握用随机数生成满足一定条件的指令地址流的方法。
3. 掌握页面置换的模拟方法。

## 实验内容与要求

1.  采用一种熟悉的语言，如 C、PASCAL 或 C++等，编制程序，最好关键代码采用 C/C++，界面设计可采用其它自己喜欢的语言。

   模拟操作系统采用 OPT、FIFO 和 LRU 算法进行页面置换的过程。

   设程序中地址范围为 0 到 32767，采用随机数生成 256 个指令地址，满足 50%的地址是顺序执行，25%向前跳，25%向后跳。为满足上述条件，可采取下列方法：设d0=10000，第n个指令地址为dn，第n+1 个指令地址为dn+1，n的取值范围为 0 到 255。每次生成一个 1 到 1024 范围内的随机数a，如果a落在 1 到 512 范围内，则dn+1=dn+1。如果a落在 513 到 768范围内，则设置dn+1为 1 到dn范围内一个随机数。如果a落在 769 到 1024范围内，则设置dn+1为dn到 32767 范围内一个随机数。

   例如：srand();初始化一个随机函数。

   a[0]＝10*rand()/32767*255+1;a[1]=10*rand()/32767*a[0]…语句可用来产生 a[0]与 a[1]中的随机数。 

   或采用以下方式：

   - 通过随机数产生一个指令序列，共 320 条指令。指令的地址按下述原则生成： 

   A：50%的指令是顺序执行的 

   B：25%的指令是均匀分布在前地址部分 

   C：25%的指令是均匀分布在后地址部分 

   具体的实施方法是： 

   A：在[0，319]的指令地址之间随机选取一起点 m 

   B：顺序执行一条指令，即执行地址为 m+1 的指令 

   C：在前地址[0,m+1]中随机选取一条指令并执行，该指令的地址为 m' 

   D：顺序执行一条指令，其地址为 m'+1 

   E：在后地址[m'+2，319]中随机选取一条指令并执行 

   F：重复步骤 A-E，直到 320 次指令 

   - 将指令序列变换为页地址流 

   设：页面大小为 1K； 

   用户内存容量 4 页到 32 页； 

   用户虚存容量为 32K。 

   在用户虚存中，按每 K 存放 10 条指令排列虚存地址，即 320 条指令在虚存中的

   存放方式为： 

   第 0 条-第 9 条指令为第 0 页（对应虚存地址为[0，9]） 

   第 10 条-第 19 条指令为第 1 页（对应虚存地址为[10，19]） 

   ……………………………… 

   第 310 条-第 319 条指令为第 31 页（对应虚存地址为[310，319]） 

   按以上方式，用户指令可组成 32 页。 

   页面大小的取值范围为 1K，2K，4K，8K，16K。按照页面大小将指令地址转化为页号。对于相邻相同的页号，合并为一个。

   分配给程序的内存块数取值范围为 1 块，2 块，直到程序的页面数。

   分别采用 OPT、FIFO 和 LRU 算法对页号序列进行调度，计算出对应的缺页中断率。

   打印出页面大小、分配给程序的内存块数、算法名、对应的缺页中断率。

   分析页面大小和分配给程序的内存块数对缺页中断率的影响。分析不同的页面置换算法的调度性能。

   在上机实现该程序之后，要求写出实验报告，其中包括实验名称、实验目的、实验内容、程序的主要流程图、实验心得和主要源程序清单等。

## 实验流程图

以下是页面置换算法的流程图

opt算法：

![image-20210208122402469](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208122402469.png)

FIFO算法：

![image-20210208122413333](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208122413333.png)

LRU算法：

![image-20210208122421948](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208122421948.png)

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

##### PageReplace.h

```
#pragma once
#include <iostream>
#include <string>
#include <time.h>
#define MAXNUM 320
using namespace std;
class PageReplace
{
private:
	int page_count;				//页面数量
	int page_size;				//页面大小
	int page_max;				//最大页面地址流
	int mem_count;				//内存块数量
	bool ischange;				//指令集是否转换为页面流标志
	int instructionset[MAXNUM];	//指令集/页面地址流
	int *mem;					//内存空间
public:
	PageReplace();
	~PageReplace();
	void setMem_sum();			//设置内存块大小
	void setPage_size();		//设置页面大小
	void generateSet();			//通过随机数产生一个指令序列,
	void changeToPage();		//将指令序列变换为页地址流并合并相邻页地址流,返回最大页面号并返回最大值
	bool pageExist(int page);	//该页是否已经在主存
	int findMax(int array[]);	//返回数组最大值的下标，相同则返回第一个下标
	int findMin(int array[]);	//返回数组最小值的下标，相同则返回第一个下标
	void output(string name, double loss_percent);	//显示调度算法信息
	void output();				//显示指令序列或页面地址流
	int find(int array[], int target);	//在数组中寻找值并返回下标
	double OPT();
	double FIFO();
	double LRU();
	void showMenu();
	void run();
};
```



#####  PageReplace.cpp

```
#include "pch.h"
#include "PageReplace.h"


void PageReplace::generateSet()
{
	srand((unsigned int)time(0));	//重置随机种子
	for (int i = 0; i < MAXNUM;) {
		instructionset[i] = rand() % 320;	//地址为m的指令
		i++;
		instructionset[i] = instructionset[i - 1] + 1;		//地址为m+1的指令
		i++;
		instructionset[i] = rand() % instructionset[i - 1];		//地址为[0，m+1]的指令m'
		i++;
		instructionset[i] = instructionset[i - 1] + 1;			//地址为m'+1的指令
		i++;
		instructionset[i] = instructionset[i - 1] + 1 + rand() % (MAXNUM - 1 - instructionset[i - 1]);	//[m'+2，319]中随机选取一条指令
		i++;
	}
	ischange = false;
}

void PageReplace::changeToPage()
{
	//转换为页面流
	for (int i = 0; i < MAXNUM; i++) {
		instructionset[i] /= (page_size * 10);
	}

	//合并页面地址流
	for (int i = 0; i < MAXNUM - 1 && instructionset[i] != -1;) {
		if (instructionset[i] == instructionset[i + 1]) {//发现相邻页号
			for (int j = i; j < MAXNUM-1; j++) {
				instructionset[j] = instructionset[j + 1];	//页号前移
			}
			instructionset[MAXNUM - 1] = -1;	//剩余空间填入-1
		}
		else {
			i++;
		}
	}
	ischange = true;	//已经转成页面地址流，更改标志

	//记录合并后页面地址流数量,最大页面地址流
	page_count = 0,page_max=instructionset[0];
	for (int i = 0; i < MAXNUM&&instructionset[i]!=-1; i++) {
		page_count++;
		if (instructionset[i]>page_max) {
			page_max = instructionset[i];
		}
	}
}

bool PageReplace::pageExist(int page)
{
	for (int i = 0; i < mem_count; i++) {
		if (mem[i] == page) {
			return true;	//该页在主存中
		}
	}
	return false;			//该页不在主存中
}

int PageReplace::findMax(int array[])
{
	int max = array[0], res = 0;
	for (int i = 0; i < sizeof(array)/sizeof(int); i++) {
		if (array[i] > max) {
			max = array[i];
			res = i;
		}
	}
	return res;
}

int PageReplace::findMin(int array[])
{
	int min = array[0], res = 0;
	for (int i = 0; i < sizeof(array) / sizeof(int); i++) {
		if (array[i] < min) {
			min = array[i];
			res = i;
		}
	}
	return res;
}

void PageReplace::output(string algorithm_name, double loss_percent)
{
	cout << "内存块数：" << mem_count<<endl;
	cout << "算法名：" << algorithm_name << endl;
	cout << "缺页中断率：" << loss_percent<< endl;
}

void PageReplace::output()
{
	for (int i = 0; i < MAXNUM&&instructionset[i]!=-1; i++) {
		if (i % 15 == 0) {		//每15个换行显示
			cout << endl;
		}
		cout << instructionset[i] << "\t";
	}
}

int PageReplace::find(int array[], int target)
{
	int res = -1;
	for (int i = 0; i < sizeof(array) / sizeof(int); i++) {
		if (array[i] == target) {
			res = i;
			break;
		}
	}
	return res;
}

PageReplace::PageReplace()
{
	for (int i = 0; i < MAXNUM; i++) {
		instructionset[i] = -1;
	}
	page_count = 0;
	page_size = 0;
	page_max = 0;
	mem_count = 0;
}


PageReplace::~PageReplace()
{
}

void PageReplace::setMem_sum()
{
	cout << "请输入内存块大小（1-"<<page_max+1<<"）：";
	cin >> mem_count;
	while (page_max < 1 || mem_count > page_max+1) {
		cout << "内存块大小输入有误，请重新输入（1-" << page_max+1 << "）：";
		cin >> mem_count;
	}
}

void PageReplace::setPage_size()
{
	cout << "请输入页面大小（取值为1，2，4，8，16）：";
	cin >> page_size;
	while (page_size != 1 && page_size != 2 && page_size != 4 && page_size != 8 && page_size != 16) {
		cout << "输入页面大小有误，请重新输入（取值为1，2，4，8，16）：";
		cin >> page_size;
	}
}

double PageReplace::OPT()
{
	setMem_sum();
	mem = new int[mem_count];					//主存空间
	int page_miss = 0;						//缺页次数
	int *opt = new int[mem_count];			//记录最近内存块的使用情况

	for (int i = 0; i < mem_count; i++) {		//主存置空
		mem[i] = -1;
	}

	int k = 0;									//记录空内存指针
	for (int i = 0; i < page_count; i++) {		//装填进程
		if (mem[mem_count-1]!=-1) {					//主存已满
			if (!pageExist(instructionset[i])) {					//发生缺页中断
				page_miss++;

				for (int i = 0; i < mem_count; i++) {						//记录数组初始化
					opt[i] = INT_MAX;
				}

				for (int j = 0; j < mem_count; j++) {						//记录内存中的最近访问序列
					for (int k = i+1; k < page_count; k++) {
						if (instructionset[k] == mem[j]) {
							opt[j] = k;	
							break;
						}
					}
				}

				mem[findMax(mem)] = instructionset[i];
			}
		}
		else {	//内存未满
			if (!pageExist(instructionset[i])) {
				mem[k++] = instructionset[i];
			}
		}
	}
	double loss_percent = (double)page_miss / page_count;
	return loss_percent;
}

double PageReplace::FIFO()
{
	setMem_sum();
	mem = new int[mem_count];
	int cur = 0,page_miss=0,mem_empty = 0;					//替换内存指针,缺页次数，空内存指针

	for (int i = 0; i < mem_count; i++) {
		mem[i] = -1;
	}

	for (int i = 0; i < page_count;i++) {
		if (mem[mem_count]!=-1) {						//主存已满
			if (!pageExist(instructionset[i])){			//发生缺页中断
				page_miss++;
				mem[cur]=instructionset[i];
				cur = (cur+1) % mem_count;
			}
		}
		else {												//内存未满
			if (!pageExist(instructionset[i])) {			//内存没有则装填
				mem[mem_empty++] = instructionset[i];
			}
		}
	}
	double loss_percent = double(page_miss) / page_count;		//计算缺页中断率
	return loss_percent;
}

double PageReplace::LRU()
{
	int page_miss = 0,mem_empty=0;	//缺页中断次数，空内存指针
	setMem_sum();
	mem = new int[mem_count];	
	int *lru = new int[mem_count];	//辅助计数数组

	for (int i = 0; i < mem_count; i++) {
		mem[i] = -1;
		lru[i] = 0;
	}

	for (int i = 0; i < page_count; i++) {
		if (mem[mem_count - 1] != -1) {					//主存已满
			if (!pageExist(instructionset[i])) {		//发生缺页中断
				page_miss++;

				mem[findMin(lru)] = instructionset[i];	//替换最久没有使用的

				for (int i = 0; i < mem_count; i++) {	//辅助数组清空
					lru[i] = 0;
				}
			}
			else {
				lru[find(mem, instructionset[i])]++;	//更新辅助数组
			}
		}
		else {											//主存未满
			if (!pageExist(instructionset[i])) {		//主存没有该页
				mem[mem_empty] = instructionset[i];
				lru[mem_empty]++;
				mem_empty++;
			}
			else {										//主存包含该页
				lru[find(mem, instructionset[i])]++;	//更新辅助数组
			}
		}
	}

	double loss_percent = double(page_miss) / page_count;
	return loss_percent;
}

void PageReplace::showMenu()
{
	cout <<endl<< "*****************MENU*****************" << endl;
	cout << "1.生成指令序列" << endl;
	cout << "2.生成并合并页地址流" << endl;
	cout << "3.OPT算法对页号序列进行调度" << endl;
	cout << "4.FIFO算法对页号序列进行调度" << endl;
	cout << "5.LRU算法对页号序列进行调度" << endl;
	cout << "6.退出" << endl;
	cout <<"*****************MENU*****************" << endl;
}

void PageReplace::run()
{
	int choice;
	while (true)
	{
		showMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			generateSet();
			cout << "生成指令序列如下" << endl;
			output();
			break;
		case 2:
			if (instructionset[0]==-1||ischange) {
				cout << "未生成新的指令序列" << endl;
				break;
			}
			setPage_size();
			changeToPage();
			cout << "变换页地址流如下" << endl;
			output();
			break;
		case 3:
			if (!ischange) {
				cout << "未生成新的页地址流" << endl;
				break;
			}
			output("OPT", OPT());
			break;
		case 4:
			if (!ischange) {
				cout << "未生成新的页地址流" << endl;
				break;
			}
			output("FIFO", FIFO());
			break;
		case 5:
			if (!ischange) {
				cout << "未生成新的页地址流" << endl;
				break;
			}
			output("LRU", LRU());
			break;
		case 6:
			exit(0);
		default:
			cout << "输入有误，请重新输入！" << endl;
			break;
		}
	}
}
```



## 实验心得

​    本次操作系统系统实验让我能够把理论知识通过动手实践完成，既加深了对页面置换算法的理论认识，又加强了上机动手编程能力，复习了相关的数据结构知识，有了很大收获

实验中遇到的问题：

​       在本实验中遇到的问题因为书上没有具体的实现代码，需要到网上去查阅资料，所以又很多细节没有注意到，常常报错，出现问题时甚至要逐步跟踪的方法才能找到问题根源。

## 参考文献

1. 朱振元.《数据结构》.2003.清华大学出版社.
2. 《数据结构实验指导书》，2008，华南师范大学计算机学院自用教材
3. 翁惠玉.俞勇.《C++ 程序设计思想与方法（第3版）慕课版》2017.人民邮电出版社.
4. 汤子瀛.《计算机操作系统》.2003.西安电子科技大学出版社