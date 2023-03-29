#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cmath>
#include <utility>
using namespace std;

struct point 
{
	pair<double,double> a;
	bool s;
	point(){s = false;}
};

class Steiner
{
	private:
		int nv;
		vector<point> v;
		vector<int> p;
		vector<int> rank;

	public:
		vector<point> steiner();
		vector<pair<int,int>> kruskal(vector<pair<int,pair<int,int>>> g, int m, int n);
		int find_get(int v) 
		{
			return (v == p[v]) ? v : (p[v] = find_get(p[v]));
		}
		void union_sets(int a, int b)
		{
			a = find_get(a);
			b = find_get(b);
			if (a != b) 
			{
				if (rank[a] < rank[b])
					swap(a,b);
				p[b] = a;
				if (rank[a] == rank[b])
					rank[a]++;
			}
		}

		Steiner(vector<point> v_point, int n)
		{
			nv = n;
			set(v_point, nv);
		}

		void set(vector<point> v_point, int n)
		{
			int i;
			for (i = 0; i < n; i++)
			{
				v.push_back(v_point[i]);
				p.push_back(i);
				rank.push_back(0);
			}
		}

		void get()
		{
			int i;
			for (i = 0; i < nv; i++)
			{
				printf("%lf %lf %i\n", v[i].a.first, v[i].a.second, v[i].s);
			}
		}

		void append(point s_point)
		{
			nv = nv+1;
			s_point.s = true;
			v.push_back(s_point);
		}
};
