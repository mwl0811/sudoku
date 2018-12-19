#include "stdafx.h"
#include "CppUnitTest.h"
#include "../sudoku/Generator.h"
#include "../sudoku/Solver.h"
#include "../sudoku/sudoku.cpp"
#include <windows.h>
#include <cassert>
#include <cstring>
#include <set>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_Sudoku
{
	TEST_CLASS(UnitTest1)
	{
	public:
		int argc;
		char **argv;

		UnitTest1()
		{
			argv = new char*[3];

			argv[0] = new char[100];
			strcpy_s(argv[0], 100, "sudoku.exe");

			argv[1] = new char[100];
			strcpy_s(argv[1], 100, "-c");

			argv[2] = new char[100];
			strcpy_s(argv[2], 100, "100");
		}

		TEST_METHOD(TestMethod1)   //输入格式不正确的时候
		{
			argc = 1;
			Check check1(argc, argv);
			int result = check1.checkinput();
			assert(result == 1);
		}

		TEST_METHOD(TestMethod2)   //输入的不是-c或者-s的时候
		{
			argc = 3;

			argv = new char*[3];
			argv[0] = new char[100];
			strcpy_s(argv[0], 100, "sudoku.exe");
			argv[1] = new char[100];
			strcpy_s(argv[1], 100, "-k");
			argv[2] = new char[100];
			strcpy_s(argv[2], 100, "100");

			Check check2(argc, argv);
			int result = check2.checkinput();
			assert(result == 2);
		}

		TEST_METHOD(TestMethod3)   //输入不是数字的时候
		{
			argc = 3;

			argv = new char*[3];
			argv[0] = new char[100];
			strcpy_s(argv[0], 100, "sudoku.exe");
			argv[1] = new char[100];
			strcpy_s(argv[1], 100, "-c");
			argv[2] = new char[100];
			strcpy_s(argv[2], 100, "abc");

			Check check3(argc, argv);
			int result = check3.checkinput();
			assert(result == 3);
		}

		TEST_METHOD(TestMethod4)   //输入的数字过大
		{
			argc = 3;

			argv = new char*[3];
			argv[0] = new char[100];
			strcpy_s(argv[0], 100, "sudoku.exe");
			argv[1] = new char[100];
			strcpy_s(argv[1], 100, "-c");
			argv[2] = new char[100];
			strcpy_s(argv[2], 100, "1000009");

			Check check4(argc, argv);
			int result = check4.checkinput();
			assert(result == 4);
		}

		TEST_METHOD(TestMethod5)   //输入生成数独终盘命令正确
		{
			argc = 3;

			argv = new char*[3];
			argv[0] = new char[100];
			strcpy_s(argv[0], 100, "sudoku.exe");
			argv[1] = new char[100];
			strcpy_s(argv[1], 100, "-c");
			argv[2] = new char[100];
			strcpy_s(argv[2], 100, "10000");

			Check check5(argc, argv);
			int result = check5.checkinput();
			assert(result == 5);
		}

		TEST_METHOD(TestMethod6)   //解数独题的路径错误
		{
			argc = 3;

			argv = new char*[3];
			argv[0] = new char[100];
			strcpy_s(argv[0], 100, "sudoku.exe");
			argv[1] = new char[100];
			strcpy_s(argv[1], 100, "-s");
			argv[2] = new char[100];
			strcpy_s(argv[2], 100, "100");

			Check check6(argc, argv);
			int result = check6.checkinput();
			assert(result == 6);
		}

		TEST_METHOD(TestMethod7)   //解数独题的路径正确
		{
			argc = 3;

			argv = new char*[3];
			argv[0] = new char[100];
			strcpy_s(argv[0], 100, "sudoku.exe");
			argv[1] = new char[100];
			strcpy_s(argv[1], 100, "-s");
			argv[2] = new char[100];
			strcpy_s(argv[2], 100, "solver.txt");

			Check check7(argc, argv);
			int result = check7.checkinput();
			assert(result == 7);
		}

		TEST_METHOD(TestMethod8)   //输入算式
		{
			argc = 3;

			argv = new char*[3];
			argv[0] = new char[100];
			strcpy_s(argv[0], 100, "sudoku.exe");
			argv[1] = new char[100];
			strcpy_s(argv[1], 100, "-c");
			argv[2] = new char[100];
			strcpy_s(argv[2], 100, "10/5");

			Check check8(argc, argv);
			int result = check8.checkinput();
			assert(result == 8);
		}

		TEST_METHOD(TestMethod9)
		{
			argc = 3;

			argv = new char*[3];
			argv[0] = new char[100];
			strcpy_s(argv[0], 100, "sudoku.exe");
			argv[1] = new char[100];
			strcpy_s(argv[1], 100, "-s");
			argv[2] = new char[100];
			strcpy_s(argv[2], 100, "solver.txt");

			Check check7(argc, argv);
			assert(check7.flag == 0);
		}

		TEST_METHOD(TestMethod10)   //证明Generator没有生成重复的矩阵
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
	};
}