#pragma once
#ifndef __SOLVER_H__
#define __SOLVER_H__

#pragma warning(disable : 4996)

#include <map>
#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;

class Solver{
public:
	int sudoku[9][9];
	FILE* question;
	FILE* file_write;
	
	Solver(FILE* path,FILE* ans)
	{
		question = path;
		file_write = ans;
		memset(sudoku,0,sizeof(sudoku));
	}

	void in()
	{
		while (true)
		{
			if (fscanf_s(question, "%d", &sudoku[0][0]) == EOF)  //读完了
			{
				break;
			}

			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (i == 0 && j == 0) continue;   
					fscanf_s(question,"%d",&sudoku[i][j]);
				}
			}
			
			if (dfs(0))
			{
				Out();    //解决之后输出
			}
		}
	}

private:
	void Out()
	{
		int pointer = 0;
		char num[165];
		memset(num, 0, sizeof(num));

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				num[pointer] = sudoku[i][j] + '0';
				pointer++;
				if (j != 8) 
				{
					num[pointer] = ' ';
					pointer++;
				}
			}
			num[pointer] = '\n';
			pointer++;
		}
		num[pointer] = '\n';
		fputs(num, file_write);
	}

	bool dfs(int tot)   //dfs搜索方法
	{             
		if (tot > 80)
		{
			return true;
		}
		
		int line = tot / 9;
		int col = tot % 9;

		if (sudoku[line][col] > 0)
		{
		    return dfs(tot + 1);
		}

		for(int i = 1;i <= 9;i++)
		{
			sudoku[line][col] = i;
			if (check(line, col, i))
			{
				if (dfs(tot + 1)) 
				{
					return true;
				}
			}
			sudoku[line][col] = 0;
		}
		
		return false;
	}

	bool check(int line, int col,int num)
	{
		for (int i = 0; i < 9; i++)
		{
			if ((col != i) && sudoku[line][i] == num) 
			{
				return false;
			}
		}

		for (int i = 0; i < 9; i++)
		{
			if ((i != line) && sudoku[i][col] == num)
			{
				return false;
			}
		}

		int base_line = line / 3 * 3;
		int base_col = col / 3 * 3;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if ((line != base_line + i) && (col != base_col + j) && sudoku[base_line + i][base_col + j] == num)
				{
					return false;
				}
			}
		}
		return true;
	}
};

#endif