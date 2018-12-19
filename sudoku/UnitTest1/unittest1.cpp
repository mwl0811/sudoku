#include "stdafx.h"
#include "CppUnitTest.h"
#include"../sudoku/Generator.h"
#include"../sudoku/Solver.h"
#include"../sudoku/sudoku.cpp"
#include<cassert>
#include<cstring>
#include<set>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_Sudoku
{
	TEST_CLASS(UnitTest1)
	{
	public:
		int argc;
		char **cargv, **sargv;

		UnitTest1()
		{
			argc = 3;
			cargv = new char*[3];
			sargv = new char*[3];   //命令由三部分组成

			cargv[0] = new char[100];
			sargv[0] = new char[100];
			strcpy_s(cargv[0], 100, "sudoku.exe");
			strcpy_s(sargv[0], 100, "sudoku.exe");

			cargv[1] = new char[100];
			sargv[1] = new char[100];
			strcpy_s(cargv[1], 100, "-c");
			strcpy_s(sargv[1], 100, "-s");

			cargv[2] = new char[100];
			sargv[2] = new char[100];
			strcpy_s(cargv[2], 100, "100");
			strcpy_s(sargv[2], 100, "solver.txt");
		}

		TEST_METHOD(TestMethod1)
		{
			int sudoku_number = 1000000;
			FILE* file;
			freopen_s(&file, "sudoku_temp.txt", "w", stdout);
			assert(file != NULL);
			Generator sudoku_generator(sudoku_number, file);
			sudoku_generator.generate();
			fclose(stdout);

			freopen_s(&file, "sudoku_temp.txt", "r", stdin);
			assert(file != NULL);
			string s1;
			bool end = false;
			set<string> container;

			while (true)
			{
				int temp;
				for (int i = 0; i < 9; i++) 
				{
					for (int j = 0; j < 9; j++)
					{
						if (fscanf_s(file, "%d", &temp) == EOF)
						{
							end = true;
							break;
						}
						s1.push_back(temp + '0');
					}
					if (end) break;
				}
				if (end) break;
				container.insert(s1);
				s1.clear();
			}
			fclose(stdin);
			assert(container.size() != sudoku_number);
		}

		TEST_METHOD(TestMethod2)
		{
			
		}


	};
}