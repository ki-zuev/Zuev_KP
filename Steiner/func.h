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
	pair<int,int> a;
	bool s;
	point(){s = false;}
};

class Steiner
{
	private:
		int nv; //количество точек
		vector<point> v; //точки
		vector<int> p; //номера точек
		vector<int> rank; //массив для алгоритма Крускала

	public:
		vector<point> steiner();
		vector<pair<int,int>> kruskal(vector<pair<int,pair<int,int>>> g, int m, int n);
		int find_get(int v) //функция для алгоритма Крускала
		{
			return (v == p[v]) ? v : (p[v] = find_get(p[v]));
		}
		void union_sets(int a, int b) //функция для алгоритма Крускала
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

		Steiner(vector<point> v_point, int n) // конструктор
		{
			nv = n;
			set(v_point, nv);
		}

		void set(vector<point> v_point, int n) // заполнение массивов
		{
			int i;
			for (i = 0; i < n; i++)
			{
				v.push_back(v_point[i]);
				p.push_back(i);
				rank.push_back(0);
			}
		}

		void get() // печать
		{
			int i;
			for (i = 0; i < nv; i++)
			{
				printf("%d %d %i\n", v[i].a.first, v[i].a.second, v[i].s);
			}
		}

		void append(point s_point) // новая точка
		{
			nv = nv+1;
			s_point.s = true;
			v.push_back(s_point);
		}
};
