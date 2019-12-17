// Sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <fstream>
#include <istream>

using namespace std;

//(7 + 3)%9 + 1 = 2 ,初始模板左上第一个数字为2
string raw_template[9] = {
    "234567891",
    "891234567",
    "567891234",
    "123456789",
    "456789123",
    "789123456",
    "912345678",
    "345678912",
    "678912345"
};

void SudokuSolved(char* path);
void SudokuGenerate(int Num);


int main(int argc, char* argv[]) {
    /*
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
    */

    clock_t start, finish;
    int num;
    cin >> num;
    start = clock();
    remove("sudoku.txt");
    SudokuGenerate(num);
    finish = clock();
    cout << "time = " << double(finish - start) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}

void SudokuSolved(char* path) {

    return;
}

void SudokuGenerate(int Num) {
    ofstream context;
    context.open("sudoku.txt", ios::app);
    int array[] = { 2,1,3,4,5,6,7,8,9 };
    int order[] = { 0,1,2,3,4,5,6,7,8 };
    int trans[9];
    int new_row[9][9];
    int temp_point = 0;

    do {
        for (int i = 0; i < 9; i++) {
            trans[raw_template[0][i] - 49] = array[i];
        }
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                new_row[i][j] = trans[raw_template[i][j] - 49];
            }
        }
        for (int i = 0; i < 2 && Num; i++) {
            for (int j = 0; j < 6 && Num; j++) {
                for (int k = 0; k < 6 && Num; k++) {
                    for (int l = 0; l < 9; l++) {
                        for (int m = 0; m < 8; m++) {
                            context << new_row[order[l]][m] << ' ';
                        }
                        context << new_row[order[l]][8];
                        if (l != 8) context << '\n';
                    }
                    if (--Num) {
                        context << '\n' << '\n';
                    }
                    else {
                        context.close();
                        return;
                    }
                    next_permutation(order + 6, order + 9);
                }
                next_permutation(order + 3, order + 6);
            }
            next_permutation(order + 1, order + 3);
        }
    } while (next_permutation(array + 1, array + 9));
    context.close();
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
