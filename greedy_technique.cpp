/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/10/25
** Purpose:	Chapter 9: Greedy Technique
************************************/

#include <vector>
#include "priorityqueue.h"
#include <utility>
#include <set>
#include <iostream>
#include <queue>
#include <tuple>

using std::vector;
using KCSTL::PriorityQueue;
using std::priority_queue;
using std::pair;
using std::tuple;
using std::set;
using std::for_each;
using std::cout;
using std::endl;

struct Edge
{
    int to;
    int cost;
};

// <cost, vertex_id>
typedef pair<int, int> P;
typedef vector<vector<Edge>> Graph;

int Prim(const Graph& graph, int start = 0)
{
    vector<P> mstEdge;
    vector<bool> inTree(graph.size(), false);
    vector<int> prev(graph.size(), -1);
    vector<int> dist(graph.size(), 999999);
    int minCost = 0;

    PriorityQueue<P, std::greater<P>> pq;
    pq.insert(P(0, start));
    dist[start] = 0;

    while (!pq.empty())
    {
        P v = pq.top();
        pq.ExtractTop();
        inTree[v.second] = true;

        if (dist[v.second] < v.first)
        {
            continue;
        }

        minCost += v.first;
        mstEdge.push_back(v);

        for (int i = 0; i < graph[v.second].size(); ++i)
        {
            // check every neighbor vertex not in MST
            int adjVexId = graph[v.second][i].to;
            int adjVexCost = graph[v.second][i].cost;
            if (!inTree[adjVexId])
            {
                if (adjVexCost < dist[adjVexId])
                {
                    prev[adjVexId] = v.second;
                    dist[adjVexId] = adjVexCost;
                    pq.insert(P(adjVexCost, adjVexId));
                }
            }
        }
    }

    for_each(mstEdge.cbegin(), mstEdge.cend(), [=](const P& v)
    {
        cout<<v.first<<"--->"<<(char)('a' + v.second)<<endl;
    });

    return minCost;
}

int Dijkstra(const Graph& graph, int start = 0)
{
    const int INF = 999999, UNDEFINED = -1;
    vector<int> dist(graph.size(), INF);
    vector<int> prev(graph.size(), UNDEFINED);
    PriorityQueue<P, std::greater<P>> pq;

    dist[start] = 0;
    pq.insert(P(0, start));

    while (!pq.empty())
    {
        P p = pq.top();
        pq.ExtractTop();

        if (dist[p.second] < p.first)
        {
            continue;
        }

        for (int i = 0; i < graph[p.second].size(); ++i)
        {
            Edge e = graph[p.second][i];
            if (dist[p.second] + e.cost < dist[e.to])
            {
                dist[e.to] = dist[p.second] + e.cost;
                prev[e.to] = p.second;
                pq.insert(P(dist[e.to], e.to));
            }
        }
    }

    // print sequence
    int i = prev.size() - 1;
    while (i != -1)
    {
        cout<<i<<endl;
        i = prev[i];
    }

    return dist.back();
}

class DisjointSet
{
	public:
		DisjointSet(int count) : _rank(count, 0)
        {
            _parent.reserve(count);
            for (int i = 0; i < count; ++i)
            {
                _parent.push_back(i);
            }
        }

        int Find(int i)
        {
            if (_parent[i] == i)
            {
                return i;
            } 
            else
            {
                // employ path-compression
                int root = Find(_parent[i]);
                _parent[i] = root;

                return root;
            }
        }

        void Union(int i, int j)
        {
            int rtI = Find(i);
            int rtJ = Find(j);
            int rankI = _rank[i], rankJ = _rank[j];

            if (rtI == rtJ)
            {
                return;
            }
            else
            {
                if (rankI < rankJ)
                {
                    _parent[rtI] = rtJ;
                }
                else if (rankI > rankJ)
                {
                    _parent[rtJ] = rtI;
                } 
                else
                {
                    _parent[rtI] = rtJ;
                    ++_rank[rtJ];
                }
            }
        }

        size_t count() const
        {
            return _parent.size();
        }

    private:
        DisjointSet(const DisjointSet&);
        DisjointSet& operator =(const DisjointSet&);

	private:
        vector<int> _parent;
        vector<int> _rank;
};

// <weight, from, to>
typedef tuple<int, int, int> edge;
int Kruskal(vector<edge>& graph, int vexCnt)
{
    // sort all edges in the order of their weight
    std::sort(graph.begin(), graph.end());

    int cnt = 0;
    vector<edge> tree;
    tree.reserve(vexCnt);
    DisjointSet s(vexCnt);

    for (int i = 0, j = 0; i < vexCnt - 1 && j < graph.size(); ++j)
    {
        const edge& e = graph[j];
        int src = std::get<1>(e);
        int dest = std::get<2>(e);

        // does not create a cycle
        if (s.Find(src) != s.Find(dest))
        {
            s.Union(src, dest);
            cnt += std::get<0>(e);
            tree.push_back(e);
            ++i;
        }
    }

    // print MST information
    for_each(tree.cbegin(), tree.cend(), [=](const edge& e)
    {
        char src = std::get<1>(e) + 'A';
        char dest = std::get<2>(e) + 'A';
        int wei = std::get<0>(e);

        cout<<src<<"-->"<<dest<<" : "<<wei<<endl;
    });

    return cnt;
}

int Test()
{
    //Edge e1[] = {{1, 3}, {3, 7}};
    //Edge e2[] = {{0, 3}, {2, 4}, {3, 2}};
    //Edge e3[] = {{1, 4}, {3, 5}, {4, 6}};
    //Edge e4[] = {{0, 7}, {1, 2}, {2, 5}, {4, 4}};
    //Edge e5[] = {{2, 6}, {3, 4}};

    //vector<Edge> v1(e1, e1 + 2);
    //vector<Edge> v2(e2, e2 + 3);
    //vector<Edge> v3(e3, e3 + 3);
    //vector<Edge> v4(e4, e4 + 4);
    //vector<Edge> v5(e5, e5 + 2);

    //vector<vector<Edge>> v;
    //v.push_back(v1);
    //v.push_back(v2);
    //v.push_back(v3);
    //v.push_back(v4);
    //v.push_back(v5);
    //return Prim(v);

    edge es[] = {edge(3,0,1), edge(7,0,3), edge(4, 1, 2), edge(2,1,3),edge(5, 2, 3), edge(6,2,4),edge(4,3,4)};
    vector<edge> e(es, es + _countof(es));
    return Kruskal(e, 5);
}