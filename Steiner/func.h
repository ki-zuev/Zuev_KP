#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
using namespace std;

int manh(int x1, int y1, int x2, int y2);

struct point 
{
	pair<int,int> a;
	bool s;
	point(){s = false;}
};

class Steiner
{
	private:
		int nv; // количество точек
		int ng; // количество точка-точка
		vector<point> v; // точки
				 //vector<pair<int, pair<int,int>>> vg; // расстояние-точка-точка
		vector<pair<int,int>> vg; // точка-точка
		vector<int> p; // номера точек
		vector<int> rank; // массив для алгоритма Крускала
		vector<int> pgraph; // подграф
		vector<bool> used;

	public:
		int steiner(); // общая длина ребер дерева Штейнера

		int flute(vector<int> graph); // метод FLUTE

		vector<pair<int,int>> kruskal(vector<pair<int,pair<int,int>>> g, int m, int n);

		void dfs(int vect); // DFS для поиска подграфов

		int find_get(int vect) // функция для алгоритма Крускала
		{
			return (vect == p[vect]) ? vect : (p[vect] = find_get(p[vect]));
		}

		void union_sets(int a, int b) // функция для алгоритма Крускала
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

		Steiner(vector<point> v_point, vector<pair<int,int>> v_graph, int n, int m) // конструктор
		{
			nv = n;
			ng = m;
			set(v_point, v_graph, nv, ng);
		}

		void set(vector<point> v_point, vector<pair<int,int>> v_graph, int n, int m) // заполнение точек
		{
			int i;
			for (i = 0; i < n; i++)
			{
				v.push_back(v_point[i]);
				p.push_back(i);
				used.push_back(false);
				rank.push_back(0);
			}
			for (i = 0; i < m; i++)
			{
				vg.push_back(v_graph[i]);
			}
		}

		void getv() // печать точек
		{
			int i;
			for (i = 0; i < nv; i++)
			{
				printf("%d %d %i\n", v[i].a.first, v[i].a.second, v[i].s);
			}
		}

		void getg() // печать графа
		{
			int i;
			for (i = 0; i < ng; i++)
			{
				printf("%d %d\n", vg[i].first, vg[i].second);
			}
		}

		void append(point s_point) // новая точка
		{
			nv = nv+1;
			s_point.s = true;
			v.push_back(s_point);
		}
};
