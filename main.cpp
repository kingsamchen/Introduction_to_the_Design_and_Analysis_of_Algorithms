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
#include <cctype>
#include <set>

void PartitionElements(const int* src, size_t len);
void BottomUpMergeSort(int* ary, int* aux, int len);
void PartRealNum(int* ary, int len);
void ArrangeDutchFlag(char* ary, int len);
void MatchNutsAndBolts(char* nuts, char* bolts, int low, int high);
std::pair<unsigned,unsigned> BinSearchRange(const int* ary, int L, int U, int count);
int BinSearch(const int* ary, int ele, int count);

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
    const int LEN = 10;
    int a[LEN] = {1,3,4,5,8,12,14,32,43,89};
    //srand(time(NULL));
    //std::for_each(a, a+LEN, [&](int& ch)
    //{
    //    ch = rand() % 100;
    //});
    //
    //std::sort(a, a + LEN);

    int p = BinSearch(a, 33, LEN);
    print_out(a, a + LEN);
    std::cout<<p;
        
    _getch();
	return 0;
}

