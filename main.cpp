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
void GenPermuJTrotter(int ary[], size_t len);
void GenPowerSets(const int ary[], size_t len);

template<typename T>
void print_out(T beg, T end, const char* dem = " ")
{
    for (auto it = beg; it != end; ++it)
    {
        std::cout<<*it<<dem;
    }

    std::cout<<std::endl;
}

int _tmain()
{
    const int LEN = 25;
    int a[] = {1,2,3,4};
    GenPowerSets(a, 4);
    _getch();
	return 0;
}

