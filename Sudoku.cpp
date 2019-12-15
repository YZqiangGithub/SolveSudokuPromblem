// Sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

void SudokuSolved(char* path);
void SudokuGenerate(long Num);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "there are some worng in cmd params" << endl;
        exit(1);
    }
    else {
        if (strcmp(argv[1], "-c") == 0) {
            long num = 0;
            int len = strlen(argv[2]);
            for (int i = 0; i < len; i++) { 
                if ((argv[2][i] <= '9' && argv[2][i] >= '0') || (argv[2][i] == '-' && i == 0)) {
                    if (argv[2][i] <= '9' && argv[2][i] >= '0') {
                        num *= 10;
                        num += argv[2][i] - '0';
                    }
                }
                else {
                    printf("error in number of solution, the num format error\n");
                    exit(1);
                }
            }
            if (argv[2][0] == '-') {
                num *= -1;
            }
            if (num > 0 && num <= 1e6) {
                SudokuGenerate(num);
            }
			else {
				cout << "error in number of solution, num should bigger than 0 and smaller than 1e6" << endl;
			}
        }
        else if (!strcmp(argv[1], "-s")) {
            SudokuSolved(argv[2]);
        }
        else {
            cout << "error cmd params" << endl;
            exit(1);
        }
    }

    return 0;
}

void SudokuSolved(char* path) {
    
    return;
}

void SudokuGenerate(long Num) {
    
    return;
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
