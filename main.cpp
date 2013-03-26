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
    char a[LEN];
    char b[LEN];
    std::set<int> s;
    srand(time(NULL));
    std::for_each(a, a+LEN, [&](char& ch)
    {
        do 
        {
            int n = rand() % 26;
            if (s.find(n) == s.end())
            {
                ch = 'a' + n;
                s.insert(n);
                break;
            }
        } while (true);

    });
    
    std::transform(a, a + LEN, b, std::toupper);
    std::random_shuffle(b, b + LEN);

    std::cout<<"before match"<<std::endl;
    print_out(a, a+_countof(a));
    print_out(b, b + _countof(b));

    MatchNutsAndBolts(a, b, 0, LEN - 1);
     
    std::cout<<"after match"<<std::endl;
    print_out(a, a+_countof(a));
    print_out(b, b + _countof(b));
    _getch();
	return 0;
}

