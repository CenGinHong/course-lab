#include "pch.h"
#include "PageReplace.h"


void PageReplace::generateSet()
{
	srand((unsigned int)time(0));	//�����������
	for (int i = 0; i < MAXNUM;) {
		instructionset[i] = rand() % 320;	//��ַΪm��ָ��
		i++;
		instructionset[i] = instructionset[i - 1] + 1;		//��ַΪm+1��ָ��
		i++;
		instructionset[i] = rand() % instructionset[i - 1];		//��ַΪ[0��m+1]��ָ��m'
		i++;
		instructionset[i] = instructionset[i - 1] + 1;			//��ַΪm'+1��ָ��
		i++;
		instructionset[i] = instructionset[i - 1] + 1 + rand() % (MAXNUM - 1 - instructionset[i - 1]);	//[m'+2��319]�����ѡȡһ��ָ��
		i++;
	}
	ischange = false;
}

void PageReplace::changeToPage()
{
	//ת��Ϊҳ����
	for (int i = 0; i < MAXNUM; i++) {
		instructionset[i] /= (page_size * 10);
	}

	//�ϲ�ҳ���ַ��
	for (int i = 0; i < MAXNUM - 1 && instructionset[i] != -1;) {
		if (instructionset[i] == instructionset[i + 1]) {//��������ҳ��
			for (int j = i; j < MAXNUM-1; j++) {
				instructionset[j] = instructionset[j + 1];	//ҳ��ǰ��
			}
			instructionset[MAXNUM - 1] = -1;	//ʣ��ռ�����-1
		}
		else {
			i++;
		}
	}
	ischange = true;	//�Ѿ�ת��ҳ���ַ�������ı�־

	//��¼�ϲ���ҳ���ַ������,���ҳ���ַ��
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
			return true;	//��ҳ��������
		}
	}
	return false;			//��ҳ����������
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
	cout << "�ڴ������" << mem_count<<endl;
	cout << "�㷨����" << algorithm_name << endl;
	cout << "ȱҳ�ж��ʣ�" << loss_percent<< endl;
}

void PageReplace::output()
{
	for (int i = 0; i < MAXNUM&&instructionset[i]!=-1; i++) {
		if (i % 15 == 0) {		//ÿ15��������ʾ
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
	cout << "�������ڴ���С��1-"<<page_max+1<<"����";
	cin >> mem_count;
	while (page_max < 1 || mem_count > page_max+1) {
		cout << "�ڴ���С�����������������루1-" << page_max+1 << "����";
		cin >> mem_count;
	}
}

void PageReplace::setPage_size()
{
	cout << "������ҳ���С��ȡֵΪ1��2��4��8��16����";
	cin >> page_size;
	while (page_size != 1 && page_size != 2 && page_size != 4 && page_size != 8 && page_size != 16) {
		cout << "����ҳ���С�������������루ȡֵΪ1��2��4��8��16����";
		cin >> page_size;
	}
}

double PageReplace::OPT()
{
	setMem_sum();
	mem = new int[mem_count];					//����ռ�
	int page_miss = 0;						//ȱҳ����
	int *opt = new int[mem_count];			//��¼����ڴ���ʹ�����

	for (int i = 0; i < mem_count; i++) {		//�����ÿ�
		mem[i] = -1;
	}

	int k = 0;									//��¼���ڴ�ָ��
	for (int i = 0; i < page_count; i++) {		//װ�����
		if (mem[mem_count-1]!=-1) {					//��������
			if (!pageExist(instructionset[i])) {					//����ȱҳ�ж�
				page_miss++;

				for (int i = 0; i < mem_count; i++) {						//��¼�����ʼ��
					opt[i] = INT_MAX;
				}

				for (int j = 0; j < mem_count; j++) {						//��¼�ڴ��е������������
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
		else {	//�ڴ�δ��
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
	int cur = 0,page_miss=0,mem_empty = 0;					//�滻�ڴ�ָ��,ȱҳ���������ڴ�ָ��

	for (int i = 0; i < mem_count; i++) {
		mem[i] = -1;
	}

	for (int i = 0; i < page_count;i++) {
		if (mem[mem_count-1]!=-1) {						//��������
			if (!pageExist(instructionset[i])){			//����ȱҳ�ж�
				page_miss++;
				mem[cur]=instructionset[i];
				cur = (cur+1) % mem_count;
			}
		}
		else {												//�ڴ�δ��
			if (!pageExist(instructionset[i])) {			//�ڴ�û����װ��
				mem[mem_empty++] = instructionset[i];
			}
		}
	}
	double loss_percent = double(page_miss) / page_count;		//����ȱҳ�ж���
	return loss_percent;
}

double PageReplace::LRU()
{
	int page_miss = 0,mem_empty=0;	//ȱҳ�жϴ��������ڴ�ָ��
	setMem_sum();
	mem = new int[mem_count];	
	int *lru = new int[mem_count];	//������������

	for (int i = 0; i < mem_count; i++) {
		mem[i] = -1;
		lru[i] = 0;
	}

	for (int i = 0; i < page_count; i++) {
		if (mem[mem_count - 1] != -1) {					//��������
			if (!pageExist(instructionset[i])) {		//����ȱҳ�ж�
				page_miss++;

				mem[findMin(lru)] = instructionset[i];	//�滻���û��ʹ�õ�

				for (int i = 0; i < mem_count; i++) {	//�����������
					lru[i] = 0;
				}
			}
			else {
				lru[find(mem, instructionset[i])]++;	//���¸�������
			}
		}
		else {											//����δ��
			if (!pageExist(instructionset[i])) {		//����û�и�ҳ
				mem[mem_empty] = instructionset[i];
				lru[mem_empty]++;
				mem_empty++;
			}
			else {										//���������ҳ
				lru[find(mem, instructionset[i])]++;	//���¸�������
			}
		}
	}

	double loss_percent = double(page_miss) / page_count;
	return loss_percent;
}

void PageReplace::showMenu()
{
	cout <<endl<< "*****************MENU*****************" << endl;
	cout << "1.����ָ������" << endl;
	cout << "2.���ɲ��ϲ�ҳ��ַ��" << endl;
	cout << "3.OPT�㷨��ҳ�����н��е���" << endl;
	cout << "4.FIFO�㷨��ҳ�����н��е���" << endl;
	cout << "5.LRU�㷨��ҳ�����н��е���" << endl;
	cout << "6.�˳�" << endl;
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
			cout << "����ָ����������" << endl;
			output();
			break;
		case 2:
			if (instructionset[0]==-1||ischange) {
				cout << "δ�����µ�ָ������" << endl;
				break;
			}
			setPage_size();
			changeToPage();
			cout << "�任ҳ��ַ������" << endl;
			output();
			break;
		case 3:
			if (!ischange) {
				cout << "δ�����µ�ҳ��ַ��" << endl;
				break;
			}
			output("OPT", OPT());
			break;
		case 4:
			if (!ischange) {
				cout << "δ�����µ�ҳ��ַ��" << endl;
				break;
			}
			output("FIFO", FIFO());
			break;
		case 5:
			if (!ischange) {
				cout << "δ�����µ�ҳ��ַ��" << endl;
				break;
			}
			output("LRU", LRU());
			break;
		case 6:
			exit(0);
		default:
			cout << "�����������������룡" << endl;
			break;
		}
	}
}


