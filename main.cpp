/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/03/17
** Purpose:	main
************************************/

#include "stdafx.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>

void PartitionElements(const int* src, size_t len);
void BottomUpMergeSort(int* ary, int* aux, int len);

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
    const int LEN = 20;
    int a[LEN];
    srand(time(NULL));
    std::for_each(a, a+LEN, [=](int& n)
    {
        n = rand() % 100;
    });
    int b[_countof(a)];
    BottomUpMergeSort(a, b, _countof(a));
    print_out(a, a+_countof(a));
    _getch();
	return 0;
}

