
#include "stdafx.h"

#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include "Generator.h" 
#include "Solver.h"
#define MAX 1000000
using namespace std;

bool compare(char* a, const char* b);

int main(int argc, char** argv)
{
	if (argc != 3)   //输入格式不正确
	{
		cout << "Illegal paramater number" << endl;
		cout << "Input like this: [sudoku.exe -c n] or [sudoku.exe -s path]" << endl;
		return 1;
	}

	if (!(compare(argv[1], "-c") || compare(argv[1], "-s")))   //字母错误
	{
		cout << "The first parameter should only be -c or -s" << endl;
		cout << "-c means to generate the sudoku to file." << endl;
		cout << "-s means to solve the sudoku from the file." << endl;
		return 1;
	}

	if (compare(argv[1], "-c"))   //创造数独终盘
	{
		int sum = 0;   //sudoku的个数
		size_t len = strlen(argv[2]);
		for (int i = 0; i < len; i++)
		{
			if (!(argv[2][i] >= '0' && argv[2][i] <= '9'))   //输入的字符不合法（不是数字）
			{
				cout << "The third paramater after -c should be number that indicate the sudoku you want." << endl;
				if (argv[2][i] == '+' || argv[2][i] == '-' || argv[2][i] == '/' || argv[2][i] == '*')
				{
					cout << "Please input the number!" << endl;
				}
				return 1;
			}
			sum = 10 * sum + argv[2][i] - '0';
		}

		if (sum > MAX || sum < 1)
		{
			cout << "The number is too large,the number should be 1-1000000" << endl;
			return 1;
		}

		FILE* file;
		file = freopen("sudoku.txt", "w", stdout);   //没有文件时可以创造
		Generator generator(sum, file);    //调用Generator
		generator.generate();
	}

	if (compare(argv[1], "-s"))   //解题
	{
		FILE* ans;
		FILE* question;   //数独题目
		question = freopen(argv[2], "r", stdin);
		if (!question)
		{
			cout << "The file path is not right,please check." << endl;
			return 1;
		}
		ans = freopen("sudoku.txt", "w", stdout);
		Solver solver(question, ans);   //调用Solver
		solver.in();
	}
	return 0;
}

bool compare(char* a, const char* b)  //用于判断字符串的函数
{
	if (strlen(a) != strlen(b))
		return false;
	for (int i = 0; i < (int)strlen(a); i++)
	{
		if (a[i] != b[i])
			return false;
	}
	return true;
}