/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/07/10
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

/*
def SolveLinearEquationSystem(coeffMatrix, valVector):
    # create the augmented matrix
    augMatrix = []
    for i in range(0, len(coeffMatrix)):
        augMatrix.append(coeffMatrix[i] + [valVector[i]])
    
    for i in range(0, len(augMatrix) - 1):
        # find row containing largest ith col ele then swap with row i
        # ensure scaling factor will never exceed 1
        # otherwise, round-off error may be bring about due to different magnitude order
        # in subsequent subtraction operations
        pivot = i
        for t in range(i + 1, len(augMatrix)):
            if abs(augMatrix[t][i]) > abs(augMatrix[pivot][i]):
                pivot = t

        if pivot != i:
            augMatrix[i], augMatrix[pivot] = augMatrix[pivot], augMatrix[i]

        for j in range(i + 1, len(augMatrix)):
            # assume a[i,i] is non-zero
            tmp = augMatrix[j][i] / augMatrix[i][i] 
            for k in range(i, len(augMatrix[0])):
                augMatrix[j][k] -= augMatrix[i][k] * tmp

    #backward substitution
    solVector = [0] * len(augMatrix)
    for p in range(0, len(augMatrix)):
        i = len(augMatrix) - 1 - p
        tmp = 0.0
        for t in range(i + 1, len(augMatrix)):
            k = len(augMatrix) + i - t
            tmp += augMatrix[i][k] * solVector[k]

        solVector[i] = (augMatrix[i][-1] - tmp) / augMatrix[i][i]

    return solVector
*/


