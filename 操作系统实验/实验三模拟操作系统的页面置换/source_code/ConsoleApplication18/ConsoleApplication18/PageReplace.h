#pragma once
#include <iostream>
#include <string>
#include <time.h>
#define MAXNUM 320
using namespace std;
class PageReplace
{
private:
	int page_count;				//ҳ������
	int page_size;				//ҳ���С
	int page_max;				//���ҳ���ַ��
	int mem_count;				//�ڴ������
	bool ischange;				//ָ��Ƿ�ת��Ϊҳ������־
	int instructionset[MAXNUM];	//ָ�/ҳ���ַ��
	int *mem;					//�ڴ�ռ�
public:
	PageReplace();
	~PageReplace();
	void setMem_sum();			//�����ڴ���С
	void setPage_size();		//����ҳ���С
	void generateSet();			//ͨ�����������һ��ָ������,
	void changeToPage();		//��ָ�����б任Ϊҳ��ַ�����ϲ�����ҳ��ַ��,�������ҳ��Ų��������ֵ
	bool pageExist(int page);	//��ҳ�Ƿ��Ѿ�������
	int findMax(int array[]);	//�����������ֵ���±꣬��ͬ�򷵻ص�һ���±�
	int findMin(int array[]);	//����������Сֵ���±꣬��ͬ�򷵻ص�һ���±�
	void output(string name, double loss_percent);	//��ʾ�����㷨��Ϣ
	void output();				//��ʾָ�����л�ҳ���ַ��
	int find(int array[], int target);	//��������Ѱ��ֵ�������±�
	double OPT();
	double FIFO();
	double LRU();
	void showMenu();
	void run();
};
