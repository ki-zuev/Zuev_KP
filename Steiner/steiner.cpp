#include "func.h"

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
	int u = 0, vect = 0, n = graph.size(), m = 0, result = 0, flag = 0, flag1 = 0;
	for (int j = 0; j < n; j++)
	{
		vect = graph[j];
		for (int i = 0; i < ng; i++)
		{
			if (vg[i].first == vect)
			{
				u = vg[i].second;
				for (int k = 0; k < n; k++)
					if (u == graph[k])
						flag1 = -1;
				if (flag1 == 0)
				{
					result += manh(v[vect].a.first, v[vect].a.second, v[u].a.first, v[u].a.second);
					flag = 1;
					break;
				}
			}
			flag1 = 0;
			if (vg[i].second == vect)
			{
				u = vg[i].first;
				for (int k = 0; k < n; k++)
					if (u == graph[k])
						flag1 = -1;
				if (flag1 == 0)
				{
					result += manh(v[vect].a.first, v[vect].a.second, v[u].a.first, v[u].a.second);
					flag = 1;
					break;
				}
			}
			flag1 = 0;
		}
		if (flag == 1)
		{
			flag = 0;
			break;
		}
	}
	vector<pair<int,int>> x(n);
	vector<pair<int,int>> y(n);
	for (int i=0; i<n; i++)
	{
		x[i].first = i;
		x[i].second = v[graph[i]].a.first;
		y[i].first = i;
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
	if (n == 2)
	{
		result += xh[0]+yv[0];
	}
	if (n == 3)
	{
		result += xh[0]+yv[0];
		if (xh[0] != xh[1])
		{
			result += xh[1];
		}
		if (yv[0] != yv[1])
		{
			result += yv[1];
		}
	}
	if (n >= 4)
	{
		if (n >= 5)
		{
			graph[x[0].first] = -1;
			result += xh[0]+yv[0];
			if (n >= 6)
			{
				for (int i=0; i<n; i++)
					if (graph[y[n-1-i].first] != -1)
					{

						graph[y[n-1-i].first] = -1;
						result += yv[n-1-i]+xh[n-1-i];
						break;
					}
				if (n >= 7)
				{
					for (int i=0; i<n; i++)
						if (graph[x[n-1-i].first] != -1)
						{
							graph[x[n-1-i].first] = -1;
							result += xh[n-1-i]+yv[n-1-i];
							break;
						}
					if (n >= 8)
					{
						for (int i=0; i<n; i++)
							if (graph[y[0+i].first] != -1)
							{
								graph[y[0+i].first] = -1;
								result += yv[0+i]+xh[0+i];
								break;
							}
						if (n == 9)
						{
							for (int i=0; i<n; i++)
								if (graph[x[1+i].first] != -1)
								{
									graph[x[1+i].first] = -1;
									result += xh[1+i]+yv[1+i];
									break;
								}
						}
					}
				}
			}
		}
		vector<int> graph1(4);
		for (int i=0; i<graph.size(); i++)
		{
			if (graph[i] != -1)
			{
				graph1[flag] = graph[i];
				flag = flag+1;
			}
		}

		/*m = 3;
		  vector<pair<int,pair<int,int>>> g(m);
		  vector<pair<int,pair<int,int>>> g1(1);
		  for (int i=0; i<m-1; i++)
		  {
		  g[i].first = manh(v[graph1[i]].a.first, v[graph1[i]].a.second, v[graph1[i+1]].a.second, v[graph1[i+1]].a.second);
		  g[i].second.first = graph1[i];
		  g[i].second.second = graph1[i+1];
		  }
		  flag = -1;
		  for (int i=0; i<ng; i++) // добавляем путь 0-3 если он есть
		  {
		  if ((vg[i].first == graph1[0]) || (vg[i].second == graph1[0]))
		  for (int j=0; j<ng; j++)
		  if ((vg[j].first == graph1[3]) || (vg[j].second == graph1[3]))
		  {
		  g1[0].first = manh(x[0].second, y[0].second, x[3].second, y[3].second);
		  g1[0].second.first = graph1[0];
		  g1[0].second.second = graph1[3];
		  g.push_back(g1[0]);
		  m += 1;
		  flag = 1;
		  break;
		  }
		  if (flag == 1)
		  {
		  flag = -1;
		  break;
		  }
		  }
		  for (int i=0; i<ng; i++) // добавляем путь 0-2 если он есть
		  {
		  if ((vg[i].first == graph1[0]) || (vg[i].second == graph1[0]))
		  for (int j=0; j<ng; j++)
		  if ((vg[j].first == graph1[2]) || (vg[j].second == graph1[2]))
		  {
		  g1[0].first = manh(x[0].second, y[0].second, x[2].second, y[2].second);
		  g1[0].second.first = graph1[0];
		  g1[0].second.second = graph1[2];
		  g.push_back(g1[0]);
		  m += 1;
		  flag = 1;
		  break;
		  }
		  if (flag == 1)
		  {
		  flag = -1;
		  break;
		  }    
		  }
		  for (int i=0; i<ng; i++) // добавляем путь 1-3 если он есть
		  {
		  if ((vg[i].first == graph1[1]) || (vg[i].second == graph1[1]))
		  for (int j=0; j<ng; j++)
		  if ((vg[j].first == graph1[3]) || (vg[j].second == graph1[3]))
		  {
		  g1[0].first = manh(x[1].second, y[1].second, x[3].second, y[3].second);
		  g1[0].second.first = graph1[1];
		  g1[0].second.second = graph1[3];
		  g.push_back(g1[0]);
		  m += 1;
		  flag = 1;
		  break;
		  }
		  if (flag == 1)
		  {
		  flag = -1;
		  break;
		  }
		  }
		  vector<pair<int,int>> res;
		res = kruskal(g, m, 4);
		for (int i=0; i<4; i++)
		{
			//result += manh(v[res[i].first].a.first, v[res[i].first].a.second, v[res[i].second].a.first, v[res[i].second].a.second);
			//result += 1;
		}*/

		vector<pair<int,int>> x4(4);
		vector<pair<int,int>> y4(4);
		for (int i=0; i<4; i++)
		{
			x4[i].first = i;
			x4[i].second = v[graph1[i]].a.first;
			y4[i].first = i;
			y4[i].second = v[graph1[i]].a.second;
		}
		sort(x4.begin(), x4.end(), comp);
		sort(y4.begin(), y4.end(), comp);
		vector<int> xh4(4-1);
		vector<int> yv4(4-1);
		for (int i=0; i<4-1; i++)
		{
			xh4[i] = x4[i+1].second-x4[i].second;
			yv4[i] = y4[i+1].second-y4[i].second;
		}
		for (int i=0; i<4-1; i++)
		{
			if (i != 1)
			{
				result += xh4[i]+yv4[i];
			}
			else
			{
				if (xh4[i] < yv4[i])
					result += 2*xh4[i]+yv4[i];
				else
					result += xh4[i]+2*yv4[i];
			}
		}
	}
	return result;
}

vector<pair<int,int>> Steiner::kruskal(vector<pair<int,pair<int,int>>> g, int m, int n)
{
	int cost = 0, i;
	vector<pair<int,int>> res;
	sort (g.begin(), g.end());
	p.resize(n);
	for (i=0; i<n; i++)
		p[i] = i;
	for (i=0; i<m; i++) 
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

void Steiner::dfs(int vect)
{
	int u = 0;
	used[vect] = true;
	pgraph.push_back(vect);
	if (pgraph.size() < 9)
	{
		for (int i = 0; i < ng; i++)
		{
			if (vg[i].first == vect)
			{
				u = vg[i].second;
				if (!used[u])
				{
					dfs(u);
					break;
				}	
			}
			if (vg[i].second == vect)
			{
				u = vg[i].first;
				if (!used[u])
				{
					dfs(u);
					break;
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
