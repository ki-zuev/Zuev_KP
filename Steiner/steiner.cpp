#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "func.h"
using namespace std;

bool comp (pair<int,int> a, pair<int,int> b)
{
        return a.second < b.second;
}

int Steiner::steiner()
{
	int result = 0;
	for (int i = 0; i < nv; i++)
	{
          if (!used[i])
          {
            dfs(i);
            result += flute(pgraph);
          }
          pgraph.clear();
        }
	return result;
}

int Steiner::flute(vector<int> graph)
{
	/*point p;
	p.a.first = 10;
	p.a.second = 15;
	append(p);*/
	int n = graph.size();
	vector<pair<int,int>> x(n);
	vector<pair<int,int>> y(n);
	for (int i=0; i<n; i++)
	{
	  x[i].first = graph[i];
	  x[i].second = v[graph[i]].a.first;
	  y[i].first = graph[i];
	  y[i].second = v[graph[i]].a.second;
	}
	sort (x.begin(), x.end(), comp);
	sort (y.begin(), y.end(), comp);
	vector<int> xh(n-1);
	vector<int> yv(n-1);
	for (int i=0; i<n-1; i++)
	{
	  xh[i] = x[i+1].second-x[i].second;
	  yv[i] = y[i+1].second-y[i].second;
	}
        return 1;
}

vector<pair<int,int>> Steiner::kruskal(vector<pair<int,pair<int,int>>> g, int m, int n)
{
	int cost = 0, i;
	vector<pair<int,int>> res;
	sort (g.begin(), g.end());
	p.resize(n);
	for (i=0; i<n; ++i)
		p[i] = i;
	for (i=0; i<m; ++i) 
	{
		int a = g[i].second.first,  b = g[i].second.second,  l = g[i].first;
		if (find_get(a) != find_get(b)) 
		{
			cost += l;
			res.push_back(g[i].second);
			union_sets(a, b);
		}
	}
	return res;
}

// DFS для поиска подграфов
void Steiner::dfs(int v) 
{
    int u = 0;
    used[v] = true; // отмечаем, что вершина посещена
    pgraph.push_back(v); // добавляем её в текущий подграф
    
    // запускаем DFS от всех непосещённых соседей вершины v
    if (pgraph.size() < 9)
    {
    for (int i = 0; i < ng; i++)
    {
      if (vg[i].first == v)
      {
        u = vg[i].second;
        if (!used[u])
        {
            dfs(u);
        }
      }
    }
    }
}

int manh(int x1, int y1, int x2, int y2)
{
	int l = 0;
	l = abs(x1-x2)+abs(y1-y2);
	return l;
}
