// Sort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;

typedef int T;

template<class T>
void BubbleSort(T a[],int n) {
	//冒泡排序
	bool exchange=true;
	for (int i = 0; i < n&&exchange; i++) {
		exchange = false;
		for (int j = 0; j < n - i - 1; j++) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
				exchange = true;
			}
		}
		cout << "第" << i + 1 << "趟排序" <<endl;
		for (int i = 0; i < n; i++) {
			cout << a[i] << "  ";
		}
		cout << endl;
	}
}

void InsertSort(T a[],int n) {
	//插入排序
	int k;
	for (int i = 0; i < n; i++) {
		k = i;
		for (int j = i; j < n; j++) {
			if (a[j] < a[k]) {
				k = j;//标记最小的元素
			}
		}
		if (k != i) {
			swap(a[k], a[i]);
		}
		cout << "第" << i + 1 << "趟排序" << endl;
		for (int i = 0; i < n; i++) {
			cout << a[i] << "  ";
		}
		cout << endl;
	}
}


int partition(int a[], int low, int high) {
	//划分函数
	cout << endl;
	int pivotpos = low;
	int pivot = a[low];
	for (int i = low + 1; i <= high; i++) {
		if (a[i] < pivot) {
			pivotpos++;
			if (pivotpos != i) {
				swap(a[pivotpos], a[i]);
			}
		}
	}
	a[low] = a[pivotpos];
	a[pivotpos] = pivot;
	cout << "本趟排序：" <<endl;
	for (int i = 0; i < 10; i++) {
		cout << a[i] << "  ";
	}
	return pivotpos;
}
void QuickSort(int a[],int left,int right) {
	//快排主函数
	if (left < right) {
		int pivotpos = partition(a,left, right);
		QuickSort(a, left, pivotpos - 1);
		QuickSort(a, pivotpos+1, right);
	}
}


int main()
{
	cout << "请输入数字：" << endl;
	int num1[10],num2[10],num3[10];
	//三个排序算法算法分别对三个相同数组进行排序
	for (int i = 0; i < 10; i++) {
		cin >> num1[i];
	}
	for (int i = 0; i < 10; i++) {
		num2[i] = num1[i];
		num3[i] = num1[i];
	}
	cout << "冒泡排序：" << endl;
	BubbleSort(num1,10);
	cout << "插入排序：" << endl;
	InsertSort(num2, 10);
	cout << "快速排序：" << endl;
	QuickSort(num3, 0, 9);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
