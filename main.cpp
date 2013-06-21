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
#include <tuple>

using std::vector;
using std::tuple;
using std::pair;

bool IsElementUnique(int ary[], size_t len);
int ComputeMode(int ary[], size_t len);
void Intersection(vector<int>& a, vector<int>& b, vector<int>& commonEle);
tuple<bool,pair<int,int>> FindSumMatch(int ary[], size_t len, int val);

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
    int a[] = {4,7,1,2,9,13,5};

    auto ret = FindSumMatch(a, _countof(a), 7);

    std::cout<<std::get<0>(ret)<<"\t("<<std::get<1>(ret).first<<","<<std::get<1>(ret).second<<")";

    _getch();
	return 0;
}

