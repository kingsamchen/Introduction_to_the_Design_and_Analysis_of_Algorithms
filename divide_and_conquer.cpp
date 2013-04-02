/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/04/02
** Purpose:	Chapter 4: Divide-and-Conquer Algorithms
************************************/

#include <algorithm>
#include <xutility>
#include <cassert>
#include <cctype>
#include <iostream>

int FindLargeElePos(const int* ary, int l, int r)
{
    if (l == r)
    {
        return l;
    } 
    else
    {
        int mid = l + ((r - l) >> 1);
        int lL = FindLargeElePos(ary, l, mid);
        int rL = FindLargeElePos(ary, mid + 1, r);

        return ary[lL] < ary[rL] ? rL : lL;
    }
}


// T(n)=2T(n/2)+4
// actually, the comparison times can be reduced to only 3
typedef std::pair<int, int> MaxMinPair;
using std::make_pair;

MaxMinPair FindLargestSmallestPair(const int* ary, int l, int r)
{
    if (l == r)
    {
        return make_pair<int, int>(ary[l], ary[l]);
    }
    else if (1 == r - l)
    {
        return make_pair<int, int>(std::max(ary[l],ary[r]), std::min(ary[l], ary[r]));
    } 
    else
    {
        int mid = l + ((r - l) >> 1);
        MaxMinPair lPair = FindLargestSmallestPair(ary, l, mid);
        MaxMinPair rPair = FindLargestSmallestPair(ary, mid + 1, r);

        MaxMinPair finalPair;
        
        finalPair.first = std::max(lPair.first, rPair.first);
        finalPair.second = std::min(lPair.second, rPair.second);

        return finalPair;
    }
}


// less than 3n/2 times of comparisons
MaxMinPair FindLargestSmallestPair(const int* ary, size_t len)
{
    int tmpMax, tmpMin;
    unsigned int begPos = 0U;
    if (len & 1)
    {
        tmpMin = tmpMax = ary[0];
        begPos = 1U;
    } 
    else
    {
        tmpMax = std::max(ary[0], ary[1]);
        tmpMin = std::min(ary[0], ary[1]);
        begPos = 2U;
    }

    for (unsigned int i = begPos; i < len; i += 2)
    {
        if (ary[i] < ary[i+1])
        {
            tmpMin = std::min(tmpMin, ary[i]);
            tmpMax = std::max(tmpMax, ary[i+1]);
        } 
        else
        {
            tmpMin = std::min(tmpMin, ary[i+1]);
            tmpMax = std::max(tmpMax, ary[i]);
        }
    }

    return make_pair<int, int>(tmpMax, tmpMin);
}


// T(n)=T(n/2)+O(1)
int Exponent(int a, unsigned int n)
{
    if (0 == n)
    {
        return 1;
    }
    else if (1 == n)
    {
        return a;
    } 
    else
    {
        if (n & 1)
        {
            return a * Exponent(a * a, n >> 1);
        } 
        else
        {
            return Exponent(a * a, n >> 1);
        }
    }
}


/*
	Description:
		
	Parameters:
        ltBeg[in] - begin_pos of the first deck
        rtBeg[in] - begin_pos of the second deck
        rtEnd[in] - end_pos(off-by-one) of second deck 
	Return Value:
		none
*/
void BottomUpMerge(int* ary, int* aux, int ltBeg, int rtBeg, int rtEnd)
{
    int auxIter = ltBeg;
    int l, r;

    /* ASSERT: ltBeg < rtBeg always holds */
    for (l = ltBeg, r = rtBeg; l < rtBeg && r < rtEnd;)
    {
        if (ary[l] <= ary[r])
        {
            aux[auxIter++] = ary[l++];
        } 
        else
        {
            aux[auxIter++] = ary[r++];
        }
    }

    // if one deck remains
    while (l < rtBeg)
    {
        aux[auxIter++] = ary[l++];
    }

    while (r < rtEnd)
    {
        aux[auxIter++] = ary[r++];
    }
}

// O(nlogn)
void BottomUpMergeSort(int* ary, int* aux, int len)
{
    // successive runs with deck width 1,2,4,...
    for (int deckWidth = 1; deckWidth < len; deckWidth *= 2)
    {
        for (int i = 0; i < len; i += 2 * deckWidth)
        {
            BottomUpMerge(ary, aux, i, std::min(len, i + deckWidth), 
                                       std::min(len, i + 2 * deckWidth));
        }

        // this run finished
        //memcpy_s(ary, sizeof(int) * len, aux, sizeof(int)*len);
        std::copy(aux, aux + len, ary);
    }
}


// assume no zero within the array
void PartRealNum(int* ary, int len)
{
    int l = 0, r = len - 1;

    do 
    {
        while (ary[l] < 0 && l < r)
        {
            ++l;
        }

        while (ary[r] > 0 && l < r)
        {
            --r;
        }

        if (l < r)
        {
            std::swap(ary[l], ary[r]);
        }
    } while (l < r);
}


/*
	Description:
		A[0..rI] - set of R
        A[rI+1..p-1] - set of W
        A[p..bI-1] - set of unexplorerd
        A[bI..len-1] - set of B
	Parameters:
		
	Return Value:
		none
*/
void ArrangeDutchFlag(char* ary, int len)
{
    int rI = -1, p = 0, bI = len;
    while (p < bI)
    {
        if ('R' == ary[p])
        {
            std::swap(ary[++rI], ary[p++]);
        }
        else if ('W' == ary[p])
        {
            ++p;
        }
        else
        {
            std::swap(ary[p], ary[--bI]);
        }
    }
}


// based on every letters are definitely distinct
int MatchPartition(char* src, char pattern, int low, int high)
{
    int l = low - 1;
    int p = low;
    auto MatchProc = [=](char s1, char s2)->int
    {
        char ele1 = std::toupper(s1);
        char ele2 = std::toupper(s2);
        
        return ele1 - ele2;
    };

    while (p < high)
    {
        int diff = MatchProc(src[p], pattern);
        if (diff < 0)
        {
            std::swap(src[p++], src[++l]);
        }
        else if (diff > 0)
        {
            ++p;
        }
        else
        {
            std::swap(src[p], src[high]);
        }
    }

    std::swap(src[l+1], src[high]);
    return l+1;
}

// assume a pair of matched nut and bolt is
// a letter with lower-case and upper-case
// and no letter can appear more than once
void MatchNutsAndBolts(char* nuts, char* bolts, int low, int high)
{
    if (high - low < 1)
    {
        return;
    }

    // two indices must be the same since each pair is distinctly matched
    int nutPiv = MatchPartition(nuts, bolts[low], low, high);
    int boltPiv = MatchPartition(bolts, nuts[nutPiv], low, high);
    assert(nutPiv == boltPiv);

    MatchNutsAndBolts(nuts, bolts, low, nutPiv - 1);
    MatchNutsAndBolts(nuts, bolts, nutPiv + 1, high);
}


int BinSearch1st(const int* ary, int ele, int count)
{
    int l = -1, r = count;
    while (l + 1 != r)
    {
        /* ASSERT: a[l]< e <= a[r] */
        int mid = l + ((r - l) >> 1);
        if (ary[mid] < ele)
        {
            l = mid;
        } 
        else
        {
            r = mid;
        }
    }

    return r == count ? r - 1 : r;
}

int BinSearchLast(const int* ary, int ele, int count)
{
    int l = -1, r = count;

    while (l + 1 != r)
    {
        /* ASSERT: a[l]<= e < a[r] */
        int mid = l + ((r - l) >> 1);
        if (ary[mid] <= ele)
        {
            l = mid;
        } 
        else
        {
            r = mid;
        }
    }

    return l == -1 ? 0 : l;
}

typedef std::pair<unsigned int, unsigned int> RangePair;
RangePair BinSearchRange(const int* ary, int L, int U, int count)
{
    if (L > U)
    {
        return std::make_pair(-1, -1);
    }

    int l = BinSearch1st(ary, L, count);
    int r = BinSearchLast(ary, U, count);

    return std::make_pair(l, r);
}


int BinSearch(const int* ary, int ele, int count)
{
    int l = 0, r = count - 1;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (ary[mid] <= ele)
        {
            l = mid;
        } 
        else
        {
            r = mid - 1;
        }
    }

    return ary[l] == ele ? l : -1;
}


struct TreeNode
{
    TreeNode() : data(0), lChild(NULL), rChild(NULL) {}
    TreeNode(int ele) : data(ele), lChild(NULL), rChild(NULL) {}
    int data;
    TreeNode* lChild;
    TreeNode* rChild;
};

TreeNode* ConstructBinTree(const int* iodrSeq, const int* podrSeq, int il, int ir,
                            int pl, int pr)
{
    if (il > ir)
    {
        return NULL;
    }
    else
    {
        int i = std::find(iodrSeq + il, iodrSeq + ir + 1, podrSeq[pr]) - iodrSeq;        
        if (i == ir + 1)
        {
            std::cerr<<"ERROR: two sequences don't match"<<std::endl;
            std::cerr<<"please call destory function to clear nodes previously created"<<std::endl;
            return NULL;
        }

        TreeNode* node = new TreeNode(podrSeq[pr]);
        node->lChild = ConstructBinTree(iodrSeq, podrSeq, il, i - 1, pl, pl + i - il - 1);
        node->rChild = ConstructBinTree(iodrSeq, podrSeq, i + 1, ir, pl + i - il, pr - 1);

        return node;
    }
}

void PreOrderVisit(const TreeNode* root)
{
    if (root != NULL)
    {
        std::cout<<root->data<<" ";
        PreOrderVisit(root->lChild);
        PreOrderVisit(root->rChild);
    }
}

void DestroyTree(TreeNode*& root)
{
    if (NULL == root)
    {
        return;
    }
    else
    {
        DestroyTree(root->lChild);
        DestroyTree(root->rChild);
        delete root;
        root = NULL;
    }
}
