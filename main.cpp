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
#include <cassert>

void PartitionElements(const int* src, size_t len);
void BottomUpMergeSort(int* ary, int* aux, int len);
void PartRealNum(int* ary, int len);
void ArrangeDutchFlag(char* ary, int len);
void MatchNutsAndBolts(char* nuts, char* bolts, int low, int high);
std::pair<unsigned,unsigned> BinSearchRange(const int* ary, int L, int U, int count);
int BinSearch(const int* ary, int ele, int count);
struct TreeNode;
TreeNode* ConstructBinTree(const int* iodrSeq, const int* podrSeq, int il, int ir, int pl, int pr);
void DestroyTree(TreeNode*& root);
void PreOrderVisit(const TreeNode* root);

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
    TreeNode* p = ConstructBinTree(a, b, 0, 5, 0, 5);
    PreOrderVisit(p);
    DestroyTree(p);
    assert(p == NULL);
    _getch();
	return 0;
}

