/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/03/17
** Purpose:	Chapter 4: Divide-and-Conquer Algorithms
************************************/

#include <algorithm>
#include <xutility>

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