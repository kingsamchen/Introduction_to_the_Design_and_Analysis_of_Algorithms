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
#include <random>

using std::vector;

void BinInsert(vector<int>& ary);
void ShellSort(int ary[], size_t len);
void GenPermuJTrotter(int ary[], size_t len);
void GenPowerSets(const int ary[], size_t len);
void BitString(size_t n, vector<unsigned int>& bin);
void GenCombination(vector<unsigned int>& combin, size_t first, size_t last, size_t k);
int RPMMul(int n, int m);
int LogFloor(unsigned int n);
int KthSmallestEleIter(int ary[], size_t len, int k);

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
    //const int LEN = 25;
    //std::random_device rd;
    //for (int i = 0; i < 5; ++i)
    //{
    //    unsigned int k = rd() % 100;
    //    std::cout<<"k="<<k<<" logfloor:"<<LogFloor(k)<<std::endl;
    //}
    int a[] = {4,7,2,8,3,9,6,13,10};
    for (int i = 1; i <= _countof(a); ++i)
    {
        std::cout<<KthSmallestEleIter(a, _countof(a), i)<<std::endl;    
    }
    _getch();
	return 0;
}

