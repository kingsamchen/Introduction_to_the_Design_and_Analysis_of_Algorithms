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
#include <cassert>
#include <vector>
#include <random>
#include <tuple>
#include <crtdbg.h>

using std::vector;
using std::tuple;
using std::pair;

bool IsElementUnique(int ary[], size_t len);
int ComputeMode(int ary[], size_t len);
void Intersection(vector<int>& a, vector<int>& b, vector<int>& commonEle);
tuple<bool,pair<int,int>> FindSumMatch(int ary[], size_t len, int val);
struct Node;
void VisitTree(const Node* root);
Node* ConstructAVLTree(const int ary[], size_t len);
void DestroyAVLTree(Node*& root);

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
    int a[] = {5,6,8,3,2,4,7};
    Node* root = ConstructAVLTree(a, _countof(a));
    VisitTree(root);
    DestroyAVLTree(root);
    assert(root == nullptr);
    _CrtDumpMemoryLeaks();
    _getch();
	return 0;
}

