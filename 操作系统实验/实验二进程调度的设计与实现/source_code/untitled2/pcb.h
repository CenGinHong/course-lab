#pragma once
#include<iostream>
using namespace std;

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
