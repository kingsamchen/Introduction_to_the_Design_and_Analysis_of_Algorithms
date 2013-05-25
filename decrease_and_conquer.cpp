/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/05/25
** Purpose:	Chapter 5: Decrease-and-Conquer Algorithms
************************************/

#include <algorithm>
#include <vector>
#include <memory>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <iostream>
#include <iterator>
#include <cassert>

using std::vector;
using std::list;
using std::deque;
using std::queue;
using std::for_each;

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


// both assume the graph is connectivity
typedef vector<list<unsigned int>> Graph;
typedef vector<bool> Marker;
void dfs(unsigned int begVex, const Graph& graph, Marker& visited)
{
    visited[begVex] = true;
    //cout<<static_cast<char>('A' + begVex)<<" -> ";

    for_each(graph[begVex].cbegin(), graph[begVex].cend(), [&](unsigned int adjVex)
    {
        if (!visited[adjVex])
        {
            dfs(adjVex, graph, visited);
        }
    });
}

void dfs_iter(const Graph& graph, unsigned int begVex)
{
    Marker visited(graph.size());
    std::stack<unsigned int> visitedButUnexploredVex;
    
    visitedButUnexploredVex.push(begVex);
    visited[begVex] = true;
    while (!visitedButUnexploredVex.empty())
    {
        unsigned int curVex = visitedButUnexploredVex.top();
        visitedButUnexploredVex.pop();

        //cout<<static_cast<char>('A' + curVex)<<" -> ";

        for_each(graph[curVex].cbegin(), graph[curVex].cend(), [&](unsigned int adjVex)
        {
            if (!visited[adjVex])
            {
                // avoid repeatedly add discovered but not yet explored vertices
                visited[adjVex] = true; 
                visitedButUnexploredVex.push(adjVex);
            }
        });
    }
}


void bfs(const Graph& graph, unsigned int begVex)
{
    Marker visited(graph.size());
    queue<unsigned int> visitedButUnexploredVex;

    visited[begVex] = true;
    visitedButUnexploredVex.push(begVex);
    while (!visitedButUnexploredVex.empty())
    {
        unsigned int curVex = visitedButUnexploredVex.front();
        //cout<<static_cast<char>('A' + curVex)<<" -> ";
        for_each(graph[curVex].cbegin(), graph[curVex].cend(), [&](unsigned int adjVex)
        {
            if (!visited[adjVex])
            {
                visited[adjVex] = true;
                visitedButUnexploredVex.push(adjVex);
            }
        });

        visitedButUnexploredVex.pop();
    }
}


bool IsBipartite(const Graph& graph, unsigned int begVex)
{
    Marker visited(graph.size());
    Marker color(graph.size());
    enum{WHITE = 0, BLACK = 1};
    queue<unsigned int> visitedButUnexploredVex;

    visited[begVex] = true;
    color[begVex] = WHITE;
    visitedButUnexploredVex.push(begVex);
    while (!visitedButUnexploredVex.empty())
    {
        unsigned int curVex = visitedButUnexploredVex.front();
        //cout<<static_cast<char>('A' + curVex)<<" -> ";
        for (auto it = graph[curVex].cbegin(); it != graph[curVex].cend(); ++it)
        {
            unsigned int adjVex = *it;
            if (visited[adjVex])
            {
                if (color[adjVex] == color[curVex])
                {
                    //printf_s("illegal edge detected at: %c and %c", 'A' + curVex, 'A' + adjVex);
                    return false;
                }
            }
            else
            {
                visited[adjVex] = true;
                // next level with different color
                color[adjVex] = !color[curVex]; 
                visitedButUnexploredVex.push(adjVex);
            }
        }

        visitedButUnexploredVex.pop();
    }

    //cout<<"It is a bipartite"<<endl;
    return true;
}


bool DFS_Visit(const Graph& graph,
               unsigned int curVex,
               Marker& visited,
               Marker& onStack,
               deque<unsigned int>& sortedSeq)
{
    visited[curVex] = true;
    onStack[curVex] = true;

    for (auto it = graph[curVex].cbegin(); it != graph[curVex].cend(); ++it)
    {
        unsigned int adjVex = *it;
        // cycle detected
        if (onStack[adjVex])
        {
            return false;
        }

        if (!visited[adjVex])
        {
            bool ret = DFS_Visit(graph, adjVex, visited, onStack, sortedSeq);
            if (!ret)
            {
                return false;
            }
        }
    }

    // this vertex exited call
    onStack[curVex] = false;
    sortedSeq.push_front(curVex);
    return true;
}

void TopoSort_DFS(const Graph& graph, deque<unsigned int>& sortedSeq)
{
    Marker visited(graph.size()), onStack(graph.size());

    // if there are unvisited vex, run on it
    // because directed graph is often not strong connected
    for (unsigned int vex = 0; vex < graph.size(); ++vex)
    {
        if (!visited[vex])
        {
            bool ret = DFS_Visit(graph, vex, visited, onStack, sortedSeq);
            if (!ret)
            {
                //cout<<"Not a DAG!"<<endl;
                sortedSeq.clear();
                return;
            }
        }
    }
}

inline void InitializeInDegree(const Graph& graph, vector<unsigned int>& indeg)
{
    for (auto it = graph.cbegin(); it != graph.cend(); ++it)
    {
        for (auto itVex = it->cbegin(); itVex != it->cend(); ++itVex)
        {
            ++indeg[*itVex];
        }
    }
}

void TopoSort(const Graph& graph, deque<unsigned int>& sortedSeq)
{
    // preprocess and initialize in-degree
    // maybe map is a better candidate
    vector<unsigned int> inDegree(graph.size());
    InitializeInDegree(graph, inDegree);

    // find all source and enqueue
    queue<unsigned int> sourceQue;
    for (unsigned int vex = 0; vex < inDegree.size(); ++vex)
    {
        if (0 == inDegree[vex])
        {
            sourceQue.push(vex);
        }
    }

    // dequeue and remove and enqueue if turned into a source
    unsigned int count = 0;
    while (!sourceQue.empty())
    {
        unsigned int vex = sourceQue.front();
        sourceQue.pop();
        sortedSeq.push_back(vex);
        ++count;

        for_each(graph[vex].cbegin(), graph[vex].cend(), [&](unsigned int adjVex)
        {
            if (0 == --inDegree[adjVex])
            {
                sourceQue.push(adjVex);
            }
        });
    }

    if (count != graph.size())
    {
        //cout<<"Not a DAG"<<endl;
        sortedSeq.clear();
    }
}


void GenPermu(int A[], int i, int n)
{
    if (i == n-1)
    {
        for (int k = 0; k < n; ++k)
        {
            //cout<<A[k]<<" ";
        }

        //cout<<endl;
        return;
    }
    else
    {
        // avoid generating duplicated sequence
        auto CheckSwapValid = [=](const int A[], int i, int j)->bool
        {
            for (int t = i; t < j; ++t)
            {
                if (A[t] == A[j])
                {
                    return false;
                }
            }

            return true;
        };

        for (int k = i; k < n; ++k)
        {
            if (CheckSwapValid(A, i, k))
            {
                std::swap(A[k], A[i]);
                GenPermu(A, i + 1, n);
                std::swap(A[k], A[i]);
            }
        }
    }
}


bool GetNextPermu(int A[], int n)
{
    int j = n - 2;
    while (A[j] >= A[j+1] && j >= 0)
    {
        --j;
    }   

    if (j < 0)
    {
        //cout<<"reached last permutation in lexical order"<<endl;
        return false;
    }

    int i = n - 1;
    while (A[j] >= A[i])
    {
        --i;
    }

    std::swap(A[j], A[i]);

    int l = j + 1, r = n - 1; 
    while (l < r)
    {
        std::swap(A[l], A[r]);
        ++l;
        --r;
    }

    return true;
}

void GenPermuLexic(int ary[], size_t len)
{
    // ary will be modified.
    // if this is not what your want, backup it.
    while (GetNextPermu(ary, static_cast<int>(len)))
    {
        // print_outs(ary, ary + len);
    }
}


void GenPermuJTrotter(int ary[], size_t len)
{
    //enum {LEFT = 0, RIGHT = 1};
    vector<bool> arrowDirec(len);
    
    auto FindLargestMobile = [=](const int ary[], size_t len,
                                 const vector<bool>& flag,
                                 int& largMobileIdx)->bool
    {
        int largest = -1; // sentinal
        for (unsigned int i = 0; i < len; ++i)
        {
            if (!flag[ary[i]-1])    // LEFT arrow
            {
                if (0 == i)
                {
                    continue;
                }
                else if (ary[i] > ary[i-1] && (largest == -1 || ary[i] > ary[largest]))
                {
                    largest = i;
                }
            } 
            else
            {
                if (i == len - 1)
                {
                    continue;
                }
                else if (ary[i] > ary[i+1] && (largest == -1 || ary[i] > ary[largest]))
                {
                    largest = i;
                }
            }
        }

        largMobileIdx = largest;
        return largest != -1 ? true : false;
    };

    int largestMobileIdx = -1;

    // 1st permutation
    //print_out(ary, ary + len);
    while (FindLargestMobile(ary, len, arrowDirec, largestMobileIdx))
    {
        // swap mobile and its arrow direction adjacent
        if (arrowDirec[ary[largestMobileIdx]-1]) // RIGHT arrow
        {
            std::swap(ary[largestMobileIdx], ary[largestMobileIdx+1]);
            ++largestMobileIdx;
        }
        else
        {
            std::swap(ary[largestMobileIdx], ary[largestMobileIdx-1]);
            --largestMobileIdx;
        }

        for_each(ary, ary + len, [&](int ele)
        {
            if (ele > ary[largestMobileIdx])
            {
                arrowDirec[ele-1] = !arrowDirec[ele-1];
            }
        });

        //print_out(ary, ary + len);
    }
}


void GenPowerSets(const int ary[], size_t len)
{
    unsigned int endBinRep = (1U << len);
    vector<int> genedSet;
    genedSet.reserve(len >> 1);

    std::cout<<"EMPTY"<<std::endl;
    for (unsigned int binRep = 1U; binRep < endBinRep; ++binRep)
    {
        // theoritically can be optimized by using BSR instruction
        // to avoid checking bits that are never could be used in this round
        for (unsigned int i = 0U; i < len; ++i)
        {
            if ((1U << i) & binRep)
            {
                genedSet.push_back(ary[i]);
            } 
        }

        std::copy(genedSet.cbegin(), genedSet.cend(), std::ostream_iterator<int>(std::cout, " "));
        std::cout<<std::endl;
        genedSet.clear();                  
    }
}


void BitString(size_t n, vector<unsigned int>& bin)
{
    if (0 == n)
    {
        std::copy(bin.cbegin(), bin.cend(), std::ostream_iterator<unsigned int>(std::cout, " "));
        std::cout<<std::endl;
    }
    else
    {
        bin[n-1] = 0;
        BitString(n-1, bin);
        
        bin[n-1] = 1;
        BitString(n-1, bin);
    }
}


void GenCombination(vector<unsigned int>& combin, size_t first, size_t last, size_t k)
{
    if (k == 0)
    {
        std::copy(combin.cbegin(), combin.cend(), std::ostream_iterator<unsigned>(std::cout, " "));
        std::cout<<std::endl;
    } 
    else
    {
        for (size_t i = first; i <= last - k + 1; ++i)
        {
            combin[k-1] = i;
            GenCombination(combin, i + 1, last, k - 1);
        }
    }
}


// Russian Peasant Method Multiplication
int RPMMul(int n, int m)
{
    if (1 == n)
    {
        return m;
    } 
    else if (n & 1)
    {
        return RPMMul((n - 1) >> 1, m << 1) + m;
    }
    else
    {
        return RPMMul(n >> 1, m << 1);
    }
}


int LogFloor(unsigned int n)
{
    int i = 0;
    while (n > 1)
    {
        n >>= 1;
        ++i;
    }

    return i;
}


int Partition(int a[], int left, int right)
{
    int piv = a[left];
    int l = left, r = right + 1;
 
    do
    {
        do 
        {
            ++l;
        } while (a[l] < piv && l < r);
 
        do 
        {
            --r;
        } while (a[r] > piv);
 
        if (l < r)
        {
            std::swap(a[l], a[r]);
        }
    }while (l < r);
 
    std::swap(a[left], a[r]);
    return r;
}

int KthSmallestEle(int ary[], int l, int r, int k)
{
    assert(l + 1 <= k && k <= r + 1);
    int s = Partition(ary, l, r);
    if (1 + s == k)
    {
        return ary[s];
    }
    else if (1 + s < k)
    {
        return KthSmallestEle(ary, s + 1, r, k);
    } 
    else
    {
        return KthSmallestEle(ary, l, s - 1, k);
    }
}


int KthSmallestEleIter(int ary[], size_t len, int k)
{
    assert(k >= 1 && k <= static_cast<int>(len));
    int l = 0, r = len - 1;
    int index = -1;
    while (l <= r)
    {
        int s = Partition(ary, l, r);
        if (s + 1 == k)
        {
            index = s;
            break;
        }
        else if (s + 1 < k)
        {
            l = s + 1;
        } 
        else
        {
            r = s - 1;
        }
    }

    assert(index != -1);
    return ary[index];
}


int InterpolationSearch(const int ary[], size_t len, int key)
{
    int l = 0, r = len - 1;

    while (l <= r)
    {
        // the line may be horizon, thus no valid slope
        int detY = ary[r] - ary[l];
        if (detY == 0)
        {
            return ary[l] == key ? l : -1;
        } 
        else
        {
            // guess a possible index based on built line equation
            int x = (key - ary[l]) * (r - l) / detY + l;
            if (ary[x] == key)
            {
                return x;
            }
            else if (ary[x] < key)
            {
                l = x + 1;
            }
            else
            {
                r = x - 1;
            }
        }
    }

    return -1;
}