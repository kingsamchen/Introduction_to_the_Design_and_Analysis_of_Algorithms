/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/10/15
** Purpose:	Chapter 9: Greedy Technique
************************************/

#include <vector>
#include "priorityqueue.h"
#include <utility>
#include <set>
#include <iostream>
#include <queue>

using std::vector;
using KCSTL::PriorityQueue;
using std::priority_queue;
using std::pair;
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


int Test()
{
    Edge e1[] = {{1, 3}, {3, 7}};
    Edge e2[] = {{0, 3}, {2, 4}, {3, 2}};
    Edge e3[] = {{1, 4}, {3, 5}, {4, 6}};
    Edge e4[] = {{0, 7}, {1, 2}, {2, 5}, {4, 4}};
    Edge e5[] = {{2, 6}, {3, 4}};

    vector<Edge> v1(e1, e1 + 2);
    vector<Edge> v2(e2, e2 + 3);
    vector<Edge> v3(e3, e3 + 3);
    vector<Edge> v4(e4, e4 + 4);
    vector<Edge> v5(e5, e5 + 2);

    vector<vector<Edge>> v;
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    v.push_back(v5);

    return Prim(v, 0);
}