/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/05/11
** Purpose:	Chapter 5: Decrease-and-Conquer Algorithms
************************************/

#include <vector>
#include <memory>

using std::vector;

// I think it is more elegant to code in python for this question
/*
def PowerSet(seq):
    if len(seq) == 0:
        return [[]] 

    ps1 = PowerSet(seq[1:])
    ps2 = copy.deepcopy(ps1) 

    # each set in part I contains element seq[0]
    # whereas in part II dosen't
    for ele in ps1:
        ele.append(seq[0])

    return ps1 + ps2
*/


void BinInsert(vector<int>& ary)
{
    for (unsigned int i = 1; i < ary.size(); ++i)
    {
        unsigned int l = 0, r = i;
        int val = ary[i];

        // index l is the target after loop finised
        while (l < r)
        {
            unsigned int mid = l + ((r - l) >> 1);
            if (ary[mid] <= val)    /* mid + 1 <= i’ <= r */
            {
                l = mid + 1;
            }   
            else    /* l <= i’ <= mid – 1 */
            {
                r = mid;
            }
        }

        // avoid cross the bound if l happens to be last index in array
        if (i > l)
        {
            memmove(&ary[l+1], &ary[l], sizeof(int) * (i - l));
            ary[l] = val;
        }
    }
}


void ShellSort(int ary[], size_t len)
{
    size_t gap = 1;
    while (gap < len / 3)
    {
        gap = 3 * gap + 1;
    }
    
    // for every gap length, do the insertion
    while (gap >= 1)
    {
        for (size_t i = gap; i < len; ++i)
        {
            int val = ary[i];
            size_t j = i;
            for (; j >= gap && ary[j-gap] > val; j -= gap)
            {
                ary[j] = ary[j-gap];
            }

            ary[j] = val;
        }

        gap /= 3;
    }
}

