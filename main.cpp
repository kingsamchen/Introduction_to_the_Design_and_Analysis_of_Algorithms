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

bool IsElementUnique(int ary[], size_t len);
int ComputeMode(int ary[], size_t len);

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
    int a[] = {4,7,13,2,8,3,9,6,13,10,10};
    std::cout<<ComputeMode(a, _countof(a));
    _getch();
	return 0;
}

