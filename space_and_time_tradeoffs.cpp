/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/08/14
** Purpose:	chapter 7: space and time tradeoffs
************************************/

#include <vector>
#include <cassert>
#include <map>

using std::vector;
using std::map;
using std::pair;

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

bool IsInitialized(size_t idx, const int* iniEleSeq, const int* eleIniSeq)
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