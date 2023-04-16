#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "func.h"
#include <chrono>
#include <string>
using namespace std;

int manh(int x1, int y1, int x2, int y2);

int main(int argc, char *argv[])
{
	int i, n = 0, n_a = 0, n_p = 0, len = 0, z=0, k = 0, res = 0, g1 = 0;
	double x = 0, y = 0;
	char S1[256], s[256];
	char *filename1 = 0, *filename2 = 0;
	if (argc != 3)
	{
		printf("Usage: %s ibm01.pl ibm01.nets\n", argv[0]);
		return 1;
	}
	filename1 = argv[1];
	filename2 = argv[2];
	ifstream f1(filename1);
	f1 >> S1 >> S1 >> z;
	n_a = z;
	f1 >> S1 >> S1 >> z;
	n_p = z;
	vector<point> a(n_a);
	while (n < n_a)
	{
		f1 >> S1 >> x >> y >> S1 >> S1;
		a[n].a.first = x;
		a[n].a.second = y;
		n = n+1;
	}
	n = 0;
	f1.close();
	ifstream f2(filename2);
	f2 >> S1 >> S1 >> z;
	n = z;
	f2 >> S1 >> S1 >> z;
	len = z-n;
	vector<pair<int, pair<int,int>>> g(len);
	n = 0;
	while (n < len)
	{
		f2 >> S1 >> S1 >> z;
		f2 >> s >> S1;
		if (s[0] == 'p')
		{
			string s1 = "";
			k = 1;
			while (s[k] != ' ')
			{
				s1.push_back(s[k]);
				k = k+1;
			}
			g1 = n_a+stoi(s1);
		}
		if (s[0] == 'a')
		{
			string s1 = "";
			k = 1;
			while (s[k] != ' ')
			{
				s1.push_back(s[k]);
				k = k+1;
			}
			g1 = stoi(s1);
		}
		res = 0;
		while (res < z-1)
		{
			f2 >> s >> S1;
			if (s[0] == 'p')
			{
				string s1 = "";
				k = 1;
				while (s[k] != ' ')
				{
					s1.push_back(s[k]);
					k = k+1;
				}
				g[n].second.second = n_a+stoi(s1);
			}
			if (s[0] == 'a')
			{
				string s1 = "";
				k = 1;
				while (s[k] != ' ')
				{
					s1.push_back(s[k]);
					k = k+1;
				}
				g[n].second.second = stoi(s1);
			}
			g[n].second.first = g1;
			g[n].first = manh(a[g[n-res].second.first].a.first, a[g[n].second.first].a.second, a[g[n].second.second].a.first, a[g[n].second.second].a.second);
			n = n+1;
			res = res+1;
		}
	}

	Steiner S(a, n_a);
        S.steiner();
        S.get();

        /*vector<pair<int,int>> res;
	res = s.kruskal(g, m, n);
	for (i = 0; i < res.size(); i++)
	{
	  printf("%d %d\n", res[i].first, res[i].second);
	}*/

	return 0;
}

int manh(int x1, int y1, int x2, int y2)
{
	int l = 0;
	l = abs(x1-x2)+abs(y1-y2);
	return l;
}
