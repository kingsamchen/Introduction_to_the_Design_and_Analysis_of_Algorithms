/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/07/23
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
#include <map>
#include <cassert>
#include <vector>
#include <random>
#include <tuple>
#include <crtdbg.h>
#include <string>
#include <unordered_map>
#include "priorityqueue.h"

using std::vector;
using std::tuple;
using std::pair;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::unordered_map;

int Test();

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
    cout<<Test();
    _getch();
	return 0;
}

