/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/10/02
** Purpose:	Chapter 8: Dynamic Programming
************************************/

#include <vector>
#include <cassert>

using std::vector;
using std::min;
using std::max;

int Binomial(int n, int k)
{
    assert(n >= 0 && k >= 0);

    int tblWidth = 1 + min(k, n >> 1);
    const int BUF_SIZE = (n + 1) * tblWidth;
    int* buf = new int[BUF_SIZE];
    
    int binomMin = k <= (n >> 1) ? k : n - k;
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= min(i,binomMin); ++j)
        {
            if (j == 0 || i == j)
            {
                buf[i*tblWidth+j] = 1;
            } 
            else
            {
                buf[i*tblWidth+j] = buf[(i-1)*tblWidth+j] + buf[(i-1)*tblWidth+j-1];
            }
        }
    }

    int val = buf[n*tblWidth+binomMin];
    delete [] buf;

    return val;
}

// only need O(k) space
int Binomial2(int n, int k)
{
    assert(n >= 0 && k >= 0);
    int* buf = new int[k+1];

    for (int i = 0; i <= n; ++i)
    {
        int firstCalculable;
        if (i <= k)
        {
            buf[i] = 1;
            firstCalculable = i - 1;
        } 
        else
        {
            firstCalculable = k;
        }

        // since we know buf[i,0] = 1 virtually
        // and we update table on the basis of immediate predecessor right to left
        for (int j = firstCalculable; j > 0; --j)
        {
            buf[j] += buf[j-1];
        }
    }

    int val = buf[k];
    delete [] buf;

    return val;
}

/*
	brief:
		obtain transitive closure from its adjacent matrix
	param:
		m[in,out] - an adjacent matrix
        len[in]   - matrix length 
	return:
		none
*/
void TransitiveClosure(int* m, int len)
{
    for (int k = 0; k < len; ++k)
    {
        for (int i = 0; i < len; ++i)
        {
            for (int j = 0; j < len; ++j)
            {
                m[i*len+j] = m[i*len+j] | (m[i*len+k] & m[k*len+j]);
            }
        }
    }
}

/*
	brief:
		calculate all-pair shortest path
	param:
		m[in,out] - an adjacent matrix
        len[in]   - matrix length 
	return:
		none
*/
void FloydAllPairShortestPath(int* m, int len)
{
    for (int k = 0; k < len; ++k)
    {
        for (int i = 0; i < len; ++i)
        {
            for (int j = 0; j < len; ++j)
            {
                m[i*len+j] = min(m[i*len+j], m[i*len+k] + m[k*len+j]);
            }
        }
    }
}

int Knapsack(const vector<int>& v, const vector<int>& w, int W)
{
    int n = v.size();
    vector<int> V((n + 1) * (W + 1));

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= W; ++j)
        {
            if (j - w[i-1] < 0)
            {
                V[i*(W+1)+j] = V[(i-1)*(W+1)+j];
            } 
            else
            {
                V[i*(W+1)+j] = max(V[(i-1)*(W+1)+j], v[i-1] + V[(i-1)*(W+1)+(j-w[i-1])]);
            }
        }
    }

    return V.back();
}