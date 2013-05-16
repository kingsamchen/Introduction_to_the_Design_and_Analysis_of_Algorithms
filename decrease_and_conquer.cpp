/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/05/16
** Purpose:	Chapter 5: Decrease-and-Conquer Algorithms
************************************/

#include <algorithm>
#include <vector>
#include <memory>
#include <list>
#include <stack>
#include <queue>
#include <deque>

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