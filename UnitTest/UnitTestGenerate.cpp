// UnitTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <istream>
#include <time.h>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int matrix[9][9];
    int total = 1;
    string path;
    cout << "input the test file path: ";
    getline(cin, path);
    ifstream File(path);
    if (!File.is_open()) {
        cout << "error in path inputed" << endl;
        exit(1);
    }
    while (!File.eof()) {
        int is_error = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                File >> matrix[i][j];
            }
        }
        for (int i = 0; i < 9; i++) {
        int whether_repeat[9] = { 0 };
            for (int j = 0; j < 9; j++) {
                if (!whether_repeat[matrix[i][j] - 1]) {
                    whether_repeat[matrix[i][j] - 1 ] = 1;
                }
                else {
                    cout << "ERROR in row" << endl;
                    is_error = 1;
                    break;
                }
            }
            if (is_error) {
                break;
            }
        }
        if (is_error) continue;
        
        for (int j = 0; j < 9; j++) {
            int whether_repeat[9] = { 0 };
            for (int i = 0; i < 9; i++) {
                if (!whether_repeat[matrix[i][j] - 1]) {
                    whether_repeat[matrix[i][j] - 1] = 1;
                }
                else {
                    cout << "ERROE in column" << endl;
                    is_error = 1;
                    break;
                }
            }
            if (is_error) {
                break;
            }
        }
        if (is_error) continue;

        for (int i = 1; i < 8; i += 3) {
            for (int j = 1; j < 8; j += 3) {
                int whether_repeat[9] = { 0 };
                if (!whether_repeat[matrix[i - 1][j - 1] - 1]) {
                    whether_repeat[matrix[i - 1][j - 1] - 1] = 1;
                }
                else
                {
                    is_error = 1;
                }
                if (!whether_repeat[matrix[i - 1][j] - 1]) {
                    whether_repeat[matrix[i - 1][j] - 1] = 1;
                }
                else
                {
                    is_error = 1;
                }
                if (!whether_repeat[matrix[i - 1][j + 1] - 1]) {
                    whether_repeat[matrix[i - 1][j + 1] - 1] = 1;
                }
                else
                {
                    is_error = 1;
                }
                if (!whether_repeat[matrix[i][j - 1] - 1]) {
                    whether_repeat[matrix[i][j - 1] - 1] = 1;
                }
                else
                {
                    is_error = 1;
                }
                if (!whether_repeat[matrix[i][j] - 1]) {
                    whether_repeat[matrix[i][j] - 1] = 1;
                }
                else
                {
                    is_error = 1;
                }
                if (!whether_repeat[matrix[i][j + 1] - 1]) {
                    whether_repeat[matrix[i][j + 1] - 1] = 1;
                }
                else
                {
                    is_error = 1;
                }
                if (!whether_repeat[matrix[i + 1][j - 1] - 1]) {
                    whether_repeat[matrix[i + 1][j - 1] - 1] = 1;
                }
                else
                {
                    is_error = 1;
                }
                if (!whether_repeat[matrix[i + 1][j] - 1]) {
                    whether_repeat[matrix[i + 1][j] - 1] = 1;
                }
                else
                {
                    is_error = 1;
                }
                if (!whether_repeat[matrix[i + 1][j + 1] - 1]) {
                    whether_repeat[matrix[i + 1][j + 1] - 1] = 1;
                }
                else
                {
                    is_error = 1;
                }
                if (is_error) break;
            }
            if (is_error) break;
        }

        if (is_error) {
            total = 0;
            cout << "ERROR in block" << endl;
            return 0;
        }
    }
    if (!total) {
        cout << "Wrong answer found" << endl;
    }
    else cout << "Correct answer" << endl;

    return 0;
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
