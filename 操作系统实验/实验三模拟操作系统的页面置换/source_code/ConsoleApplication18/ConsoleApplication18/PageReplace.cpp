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
		if (mem[mem_count-1]!=-1) {						//主存已满
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


