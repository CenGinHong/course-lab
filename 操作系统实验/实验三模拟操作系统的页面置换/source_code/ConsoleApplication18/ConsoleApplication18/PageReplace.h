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
