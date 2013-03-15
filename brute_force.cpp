/************************************
** Edition:	Demo
** Author:	Kingsley Chen
** Date:	2013/03/15
** Purpose:	Chapter 3: Brute Force Appoarches
************************************/

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// worst-case time: O(n^2)
int CountSpecificSubStr(const char* sz, char pfx, char sfx)
{
	int count = 0;

	while (*sz != '\0')
	{
		if (*sz == pfx)
		{
			for (auto i = sz + 1; *i != '\0'; ++i)
			{
				if (*i == sfx)
					++count;
			}
		}

		++sz;
	}

	return count;
}


// always O(n)
int CountSpecificSubStr2(const char* sz, char pfx, char sfx)
{
    int ccA = 0, count = 0;

    for (auto it = sz; *it != '\0'; ++it)
    {
        if (*it == pfx)
        {
            ++ccA;
        }
        else if (*it == sfx)
        {
            count += ccA;
        }
    }

    return count;
}


// Desc:partition n positive integers into two disjoint subsets with the same sum
// of their elements.
// all elements in src are non-negative integers
// worst-case time: O(n*2^n)
void PartitionElements(const int* src, size_t len)
{
	int eleSum = 0;
	for (auto i = src; i != len + src; ++i)
	{
		eleSum += *i;	
	}

	if (eleSum & 1)
	{
		cout<<"cannot partition sequence"<<endl;
		return;
	}

	int requiredSubSum = eleSum >> 1;
	size_t subsetCount = (1U << len);
	bool isFindPartition = false;
	vector<unsigned int> disSet1, disSet2;

	// each binary representation of i indicates one subset
	// brute-force approach
	for	(size_t i = 1U; i < subsetCount && !isFindPartition; ++i)
	{
		int subSum = 0;
		disSet1.clear();
		disSet2.clear();

		for (size_t t = 0U; t < len; ++t)
		{
			unsigned int k = 1U << t;
			if (i & k)
			{
				disSet1.push_back(src[len-1-t]);
				subSum += src[len-1-t];
				if (subSum > requiredSubSum)
				{
					break;
				}
				else if (subSum == requiredSubSum)
				{
					cout<<"Find partition set"<<endl;
					isFindPartition = true;
					break;
				}
			}
			else
			{
				disSet2.push_back(k);
			}
		}
	}

    // how can I prove this cannot happen?
	if (!isFindPartition)
	{
		cout<<"not find partition set"<<endl;
	}

	// print two disjoint sets
	cout<<"part I:"<<endl;
	for (auto it = disSet1.crbegin(); it != disSet1.crend(); ++it)
		cout<<*it<<" ";
}
