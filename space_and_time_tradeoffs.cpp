/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/08/22
** Purpose:	chapter 7: space and time tradeoffs
************************************/

#include <vector>
#include <cassert>
#include <map>
#include <string>
#include <unordered_map>

using std::vector;
using std::map;
using std::pair;
using std::string;
using std::unordered_map;

// all elements in src range from 0 to k
void CountingSort(vector<int>& src, unsigned int k)
{
    vector<int> aux(k+1);

    for (auto it = src.cbegin(); it != src.cend(); ++it)
    {
        ++aux[*it];
    }

    for (auto it = aux.begin() + 1; it != aux.end(); ++it)
    {
        *it += *(it - 1);
    }

    vector<int> tmp(src.size());
    for (auto it = src.crbegin(); it != src.crend(); ++it)
    {
        tmp[--aux[*it]] = *it;
    }

    src.swap(tmp);
}

void XorSwap(int& x, int& y)
{
    x ^= y;
    y ^= x; // y = x
    x ^= y;
}

// elements range between [0, size)
void SortSequnce(vector<int>& src)
{
    vector<int> tmp(src.size());
    for (auto it = src.cbegin(); it != src.cend(); ++it)
    {
        tmp[*it] = *it;
    }

    src.swap(tmp);
}

// an in-place implementation of above algorithm
void SortSequenceInPlace(vector<int>& src)
{
    int size = src.size();
    for (int i = 0; i != size; ++i)
    {
        while (src[i] != i)
        {
            std::swap(src[src[i]], src[i]);
        }
    }
}

inline int& Count()
{
    static int count;
    return count;
}

void SetAssign(int val, int* src, size_t len, size_t idx,
               int* iniEleSeq, int* eleIniSeq)
{
    assert(idx >= 0 && idx < len);
    src[idx] = val;
    iniEleSeq[Count()] = idx;
    eleIniSeq[idx] = Count();
    ++Count();
}

bool IsInitialized(int idx, const int* iniEleSeq, const int* eleIniSeq)
{
    return (eleIniSeq[idx] >= 0 && eleIniSeq[idx] < Count()) &&
           iniEleSeq[eleIniSeq[idx]] == idx ? true : false;
}

// assume the value of each node in the tree is distinct
struct Node
{
    int value;
    Node* left;
    Node* right;
};

void Preorder(const Node* root, map<int,int>& preordSeq, int& seq)
{
    if (root == nullptr)
    {
        return;
    }

    preordSeq.insert(pair<int,int>(root->value, seq++));
    Preorder(root->left, preordSeq, seq);
    Preorder(root->right, preordSeq, seq);
}

void Postorder(const Node* root, map<int,int>& postordSeq, int& seq)
{
    if (root == nullptr)
    {
        return;
    }

    Postorder(root->left, postordSeq, seq);
    Postorder(root->right, postordSeq, seq);
    postordSeq.insert(pair<int,int>(root->value, seq++));
    
}

void OrderPreProcess(const Node* root,
                     map<int,int>& preordSeq,
                     map<int,int>& postordSeq)
{
    int preordCount = 0;
    int postordCount = 0;

    Preorder(root, preordSeq, preordCount);
    Postorder(root, postordSeq, postordCount);
}

bool IsAncestry(const Node* node1, const Node* node2,
                const map<int,int>& preordSeq, const map<int,int>& postordSeq)
{
    if (preordSeq.at(node1->value) <= preordSeq.at(node2->value) &&
        postordSeq.at(node1->value) >= postordSeq.at(node2->value))
    {
        return true;
    } 
    else
    {
        return false;
    }
}

// please trust NRV optimization
inline unordered_map<char,int> InitializeShiftTable(const string& pattern)
{
    unordered_map<char,int> shiftTable;

    const int CNT_SIZE = pattern.size() - 1;
    for (int i = 0; i < CNT_SIZE; ++i)
    {
        shiftTable[pattern[i]] = CNT_SIZE - i;
    }

    return shiftTable;
}

inline int Tbl(const unordered_map<char,int>& tbl, int patLen, char c)
{
    auto it = tbl.find(c);

    // c is not in pattern
    if (it == tbl.cend())
    {
        return patLen;
    } 
    else
    {
        return it->second;
    }
}

int HorspoolMatching(const string& str, const string& pattern)
{
    auto tbl = InitializeShiftTable(pattern);
    // avoid need for casting below
    int STR_LEN = str.size();
    int PATTERN_LEN = pattern.size();
    int i = PATTERN_LEN - 1;

    while (i < STR_LEN)
    {
        int matchedCnt = 0;
        while (matchedCnt < PATTERN_LEN &&
               str[i-matchedCnt] == pattern[PATTERN_LEN-1-matchedCnt])
        {
            ++matchedCnt;
        }

        // found
        if (matchedCnt == PATTERN_LEN)
        {
            return i - matchedCnt + 1;
        } 
        else
        {
            i += Tbl(tbl, PATTERN_LEN, str[i]);
        }
    }

    return -1;
}

inline unordered_map<char,int> InitBadCharShiftTbl(const string& pattern)
{
    return InitializeShiftTable(pattern);
}

// suffix[i] == s --> P[i-s..i] == P[m-s..m] && P[i-s-1] != P[m-s-1]
vector<int> LongestSuffixLength(const string& pattern)
{
    vector<int> suffix(pattern.size());
    const int PATTERN_SIZE = pattern.size();

    *--suffix.end() = PATTERN_SIZE;
    for (int i = PATTERN_SIZE - 2; i >= 0; --i)
    {
        int k = i;
        while (k >= 0 && pattern[k] == pattern[PATTERN_SIZE-1-i+k])
        {
            --k;
        }

        suffix[i] = i - k;
    }

    return suffix;
}

vector<int> InitGoodCharShiftTbl(const string& pattern)
{
    const int PATTERN_SIZE = pattern.size();
    vector<int> gcShiftTbl(PATTERN_SIZE, PATTERN_SIZE);

    vector<int> suffix = LongestSuffixLength(pattern);

    // consider prefix matches with suffix first
    for (int i = PATTERN_SIZE - 1; i >= 0; --i)
    {
        if (suffix[i] == i + 1)
        {
            for (int j = 0; j < PATTERN_SIZE - 1 - i; ++j)
            {
                if (gcShiftTbl[j] == PATTERN_SIZE)
                {
                    gcShiftTbl[j] = PATTERN_SIZE - 1 - i;
                }
            }
        }
    }

    // now consider good characters are totaly matched
    // with some occurrence
    for (int i = 0; i <= PATTERN_SIZE - 2; ++i)
    {
        int sufLen = suffix[i];
        if (i > 0 && pattern[i-sufLen] != pattern[PATTERN_SIZE - 1 - sufLen])
        {
            gcShiftTbl[PATTERN_SIZE - 1 - sufLen] = PATTERN_SIZE - 1 - i;
        }
    }

    return gcShiftTbl;
}