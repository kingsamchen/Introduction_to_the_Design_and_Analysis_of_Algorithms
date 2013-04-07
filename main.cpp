/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/04/07
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
    int a[] = {4,5,2,1,3,6};
    int b[] = {5,4,2,6,3,1};
    //srand(time(NULL));
    //std::for_each(a, a+LEN, [&](int& ch)
    //{
    //    ch = rand() % 100;
    //});
    //
    //std::sort(a, a + LEN);
    _getch();
	return 0;
}

