/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/05/11
** Purpose:	main
************************************/

#include "stdafx.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <set>
#include <cassert>
#include <vector>

using std::vector;

void BinInsert(vector<int>& ary);
void ShellSort(int ary[], size_t len);

template<typename T>
void print_out(T beg, T end, const char* dem = " ")
{
    for (auto it = beg; it != end; ++it)
    {
        std::cout<<*it<<dem;
    }

    std::cout<<std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
    const int LEN = 25;
    int a[] = {4,5,2,1,3,6};
    int b[] = {5,4,2,6,3,1};
    vector<int> v;
    v.resize(LEN);
    //srand(time(NULL));
    std::for_each(v.begin(), v.end(), [&](int& ch)
    {
        ch = rand() % 100;
    });
    //BinInsert(v);
    ShellSort(&v[0], v.size());
    print_out(v.begin(), v.end());
    _getch();
	return 0;
}

