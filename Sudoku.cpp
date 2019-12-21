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


char output[200000000];          //缓存数独终局
int input[200000000];           //缓存输入数独问题
int sudoku_ques[9][9];        //待解决数独问题
int mark_row[9][9];
int mark_col[9][9];
int mark_block[9][9];
int blank_num = 0;
int blank[100][3];       //二维数组的三个元素为空白格的行，列和所属小宫格的已填入格数与所属行列已填入最大格数
int row[9], col[9], block[9];  //纪录非空白格数量




void WriteIntoFile();                                   //向文件中一次写入
void SudokuSolved(string path);                          //解数独问题
void SudokuGenerate(int Num);                           //生成终局函数
inline int  GetBlockNum(int row, int col);
void SetMark(int row, int col, int n, int mark);
void Swap(int* a, int* b);
bool DFS(int depth);
void Reset();
int GetMax(int row_num, int col_num, int block_num);



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
            string path;
            path = argv[2];
            SudokuSolved(path);
        }
        else {
            cout << "error cmd params" << endl;
            exit(1);
        }
    }
    */



    clock_t start, finish;
    string path;
    char Str[20];
    cin >> Str;
    path = Str;
    start = clock();
    //    SudokuGenerate(num);
    SudokuSolved(path);
    finish = clock();
    cout << "time = " << double((double)finish - (double)start) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}

void SudokuSolved(string path) {
    ifstream ReadFile(path);
    if (!ReadFile.is_open()) {
        printf("There is an error in opening the file!\n");
        exit(1);
    }
    int count = 0;
    while (!ReadFile.eof())
    {
        ReadFile >> input[count++];
    }
    ReadFile.close();
    int input_count = 0, output_count = 0;

    while (input[input_count])
    {
        //将数据填入，记下标记
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                sudoku_ques[i][j] = input[input_count++];

                if (!sudoku_ques[i][j]) {
                    blank[blank_num][0] = i;
                    blank[blank_num][1] = j;
                    blank_num++;
                }
                else
                {
                    SetMark(i, j, sudoku_ques[i][j], 1);
                    row[i]++;
                    col[j]++;
                    block[GetBlockNum(i, j)]++;
                }
            }
        }
        //计算空白格所在行列块的已填入数最大格数
        for (int i = 0; i < blank_num; i++) {
            int temp_row = blank[i][0], temp_col = blank[i][1];
            blank[i][2] = GetMax(row[temp_row], col[temp_col], block[GetBlockNum(temp_row, temp_col)]);
        }
        //对空白格记录的按从大到小排序
        for (int i = 0; i < blank_num; i++) {
            int m = i;
            for (int j = i; j < blank_num - 1; j++) {
                if (blank[m][2] < blank[j + 1][2]) m = j + 1;
            }
            Swap(blank[i], blank[m]);
        }

        if (DFS(0)) {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    output[output_count++] = sudoku_ques[i][j] + '0';
                    if (j == 8) {
                        output[output_count++] = '\n';
                    }
                    else
                    {
                        output[output_count++] = ' ';
                    }
                }
            }
            output[output_count++] = '\n';

        }
        Reset();
    }
    WriteIntoFile();
    return;
}



void SudokuGenerate(int Num) {
    long count = 0;
    int array[] = { 2,1,3,4,5,6,7,8,9 };    //初始数字组合顺序排列，方便之后的数字排列组合
    int order[] = { 0,1,2,3,4,5,6,7,8 };    //行数
    int trans[9];                           //交换数组
    int new_row[9][9];                      //新生成的数独矩阵                         

    do {                                                  //除了初始第一行第一列的数字，其他数字两两交换排列组合
        for (int i = 0; i < 9; i++) {
            trans[raw_template[0][i] - 49] = array[i];
        }
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                new_row[i][j] = trans[raw_template[i][j] - 49];
            }
        }
        for (int i = 0; i < 2 && Num; i++) {                //2到3行两两交换
            for (int j = 0; j < 6 && Num; j++) {            //4到6行两两交换
                for (int k = 0; k < 6 && Num; k++) {        //7到9行两两交换
                    for (int l = 0; l < 9; l++) {
                        for (int m = 0; m < 8; m++) {
                            output[count++] = new_row[order[l]][m] + '0';
                            output[count++] = ' ';
                        }
                        output[count++] = new_row[order[l]][8];
                        if (l != 8) output[count++] = '\n';
                    }
                    if (--Num) {
                        output[count++] = '\n';
                        output[count++] = '\n';
                    }
                    else {
                        return;
                    }
                    next_permutation(order + 6, order + 9);
                }
                next_permutation(order + 3, order + 6);
            }
            next_permutation(order + 1, order + 3);
        }
    } while (next_permutation(array + 1, array + 9));

    WriteIntoFile();
    return;
}

void WriteIntoFile() {
    remove("sudoku.txt");
    ofstream WriteFile("sudoku.txt");
    WriteFile << output;
    return;
}

void SetMark(int row, int col, int n, int mark)
{
    mark_row[row][n - 1] = mark;
    mark_col[col][n - 1] = mark;
    mark_block[GetBlockNum(row, col)][n - 1] = mark;
    return;
}

void Reset()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            mark_row[i][j] = mark_col[i][j] = mark_block[i][j] = sudoku_ques[i][j] = 0;
        }
        row[i] = col[i] = block[i] = 0;
    }
    blank_num = 0;
    for (int i = 0; i < 100; i++) {
        blank[i][0] = blank[i][1] = blank[i][2] = 0;
    }
    return;
}


bool DFS(int depth)
{
    if (depth == blank_num) {
        return true;
    }

    int row = blank[depth][0], col = blank[depth][1];
    for (int i = 0; i < 9; i++) {
        if (!mark_row[row][i] && !mark_col[col][i] && !mark_block[GetBlockNum(row, col)][i])
        {
            sudoku_ques[row][col] = i + 1;
            SetMark(row, col, sudoku_ques[row][col], 1);
            if (DFS(depth + 1)) return true;
            SetMark(row, col, sudoku_ques[row][col], 0);
            sudoku_ques[row][col] = 0;
        }
    }
    return false;
}

void Swap(int* a, int* b)
{
    int temp[3];
    temp[0] = a[0];
    temp[1] = a[1];
    temp[2] = a[2];
    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];
    b[0] = temp[0];
    b[1] = temp[1];
    b[2] = temp[2];
    return;
}

inline int GetBlockNum(int row, int col)
{
    return (row / 3) * 3 + (col / 3);
}

int GetMax(int row_num, int col_num, int block_num)
{
    int temp = row_num > col_num ? row_num : col_num;
    return temp > block_num ? temp : block_num;
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
