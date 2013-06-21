/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/06/21
** Purpose:	chapter 6: Transform-and-Conquer Algorithms
************************************/

#include <algorithm>
#include <vector>
#include <tuple>

using std::vector;
using std::pair;
using std::tuple;
using std::sort;
using std::make_pair;
using std::make_tuple;

bool IsElementUnique(int ary[], size_t len)
{
    std::sort(ary, ary + len);

    for (size_t i = 0; i < len - 1; ++i)
    {
        if (ary[i] == ary[i+1])
        {
            return false;
        }
    }

    return true;
}

int ComputeMode(int ary[], size_t len)
{
    std::sort(ary, ary + len);

    int mode = ary[0], modeFrequency = 0;

    // i always points to the first occurence of a element that might be the mode
    for (size_t i = 0; i < len;)
    {
        int runVal = ary[i], runLen = 1;

        while (i + runLen < len && ary[i+runLen] == runVal)
        {
            ++runLen;
        }

        if (runLen > modeFrequency)
        {
            mode = runVal;
            modeFrequency = runLen;
        }

        i += runLen;
    }

    return mode;
}

void Intersection(vector<int>& a, vector<int>& b, vector<int>& commonEle)
{
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    for (auto itA = a.cbegin(), itB = b.cbegin(); itA != a.cend() && itB != b.cend();)
    {
        if (*itA == *itB)
        {
            commonEle.push_back(*itA);
            ++itA;
            ++itB;
        }
        else if (*itA < *itB)
        {
            ++itA;
        } 
        else
        {
            ++itB;
        }
    }
}

tuple<bool,pair<int,int>> FindSumMatch(int ary[], size_t len, int val)
{
    sort(ary, ary + len);

    for (size_t l = 0, r = len - 1; l < r;)
    {
        int attemptSum = ary[l] + ary[r];
        if (attemptSum == val)
        {
            return make_tuple(true, make_pair(ary[l], ary[r]));
        }
        else if (attemptSum < val)
        {
            ++l;
        } 
        else /* attemptSum > val */
        {
            --r;
        }
    }

    return make_tuple(false, make_pair(0, 0));            
}

/*
def MaximumOverlappedIntervals(intervals):
    leftEnd = []
    rightEnd = []
    
    for (l, r) in intervals:
        leftEnd.append(l)
        rightEnd.append(r)

    leftEnd.sort()
    rightEnd.sort()

    # len(leftEnd) must equal len(rightEnd)
    l = r = 0
    m = overloap = 0
    while l < len(leftEnd) and r < len(rightEnd):
        if leftEnd[l] < rightEnd[r]:
            overloap += 1
            l += 1
            if overloap > m:
                m = overloap
        else:
            overloap -= 1
            r += 1

    return m
*/