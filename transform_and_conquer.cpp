/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/06/20
** Purpose:	chapter 6: Transform-and-Conquer Algorithms
************************************/

#include <algorithm>

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

