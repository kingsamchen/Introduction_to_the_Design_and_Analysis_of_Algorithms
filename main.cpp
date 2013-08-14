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

using std::vector;
using std::tuple;
using std::pair;
using std::cout;
using std::endl;
using std::map;

void XorSwap(int& x, int& y);
void SortSequnce(vector<int>& src);
void SortSequenceInPlace(vector<int>& src);
inline void SetAssign(int val, int* src, size_t len, size_t idx,
                      int* iniEleSeq, int* eleIniSeq);
inline bool IsInitialized(const int* src, size_t len, size_t idx,
                          const int* iniEleSeq, const int* eleIniSeq);
struct Node;
void OrderPreProcess(const Node* root,
                     map<int,int>& preordSeq,
                     map<int,int>& postordSeq);
bool IsAncestry(const Node* node1, const Node* node2,
                const map<int,int>& preordSeq, const map<int,int>& postordSeq);
Node* ConstructAVLTree(const int ary[], size_t len);
void DestroyAVLTree(Node*& root);

template<typename T>
void print_out(T beg, T end, const char* dem = " ")
{
    for (auto it = beg; it != end; ++it)
    {
        std::cout<<it<<dem;
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
    int ary[] = {6,4,2,5,8,7,9};

    _getch();
	return 0;
}

