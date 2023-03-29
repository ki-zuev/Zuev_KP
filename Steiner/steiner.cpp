#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <cmath>
#include "func.h"
using namespace std;

vector<point> Steiner::steiner()
{
	vector<point> x;
	point p;
	p.a.first = 10;
	p.a.second = 15;
	append(p);
	return x;
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
