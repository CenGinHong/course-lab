// ConsoleApplication15.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include"BinTree.h"

int main()
{
	BinaryTree<char> tree(' ');
	int choice;
	while (true) {
		tree.showMenu();
		cin >> choice;
		cin.get();//消除回车残留缓冲区的影响
		switch (choice)
		{
		case 1: {
			if (tree.isEmpty()) {
				cout << "开始建树" << endl;
				tree.createTree();
				cout <<endl<< "建树完成" << endl;
			}
			else {
				cout << "树已经存在" << endl;
			}
			break;
		}
		case 2: {
			if (tree.isEmpty()) {
				cout << "树为空" << endl;
			}
			else {
				cout << "树的前序输出为" << endl;
				tree.preOrder();
				cout << endl;
			}
			break;
		}
		case 3: {
			if (tree.isEmpty()) {
				cout << "树为空" << endl;
			}
			else {
				cout << "树的非递归前序输出为" << endl;
				tree.preOrder1();
				cout << endl;
			}
			break;
		}
		case 4: {
			if (tree.isEmpty()) {
				cout << "树为空" << endl;
			}
			else {
				cout << "树的中序输出为" << endl;
				tree.inOrder();
				cout << endl;
			}
			break;
		}
		case 5: {
			if (tree.isEmpty()) {
				cout << "树为空" << endl;
				cout << endl;
			}
			else {
				cout << "树的非递归中序输出为" << endl;
				tree.inOrder();
				cout << endl;
			}
			break;
		}
		case 6: {
			if (tree.isEmpty()) {
				cout << "树为空" << endl;
				cout << endl;
			}
			else {
				cout << "树的递归后序输出为" << endl;
				tree.preOrder();
				cout << endl;
			}
			break;
		}
		case 7: {
			cout << "树的非递归递归后序输出为" << endl;
			tree.preOrder();
			cout << endl;
			break;
		}
		case 8: {
			if (tree.isEmpty()) {
				cout << "树为空" << endl;
			}
			else {
				cout << "树的高度为" << tree.getHeight() << endl;
			}
			break;
		}
		case 9: {
			if (tree.isEmpty()) {
				cout << "树为空" << endl;
			}
			else {
				cout << "树的叶子节点总数为" << tree.getleaf() << endl;
			}
			break;
		}
		case 10: {
			if (tree.isEmpty()) {
				cout << "树为空" << endl;
			}
			else {
				cout << "树的广义表输出为：" << endl;
				tree.output();
				cout << endl;
			}
			break;
		}
		case 11: {
			exit(0);
		}
		default:
			break;
		}
		cout << endl;
		system("pause");
	}

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
