#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include "func.h"
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
	int i, n = 0, n_a = 0, n_p = 0, n_g = 0, z=0, k = 0, res = 0, g1 = 0;
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
	n_g = z-n;
	//vector<pair<int, pair<int,int>>> g(n_g);
	vector<pair<int,int>> g(n_g);
	n = 0;
	while (n < n_g)
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
				//g[n].second.second = n_a+stoi(s1);
				g[n].second = n_a+stoi(s1);
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
				//g[n].second.second = stoi(s1);
				g[n].second = stoi(s1);
			}
			//g[n].second.first = g1;
			g[n].first = g1;
			//g[n].first = manh(a[g[n-res].second.first].a.first, a[g[n].second.first].a.second, a[g[n].second.second].a.first, a[g[n].second.second].a.second);
			n = n+1;
			res = res+1;
		}
	}
	Steiner S(a, g, n_a, n_g);
	//S.getv();
	//S.getg();
	int result = 0;
	result = S.steiner();
	printf("%d\n", result);
	/*vector<pair<int,int>> result;
	result = S.kruskal(g, n_g, n_a);
	for (i = 0; i < result.size(); i++)
	{
		printf("%d %d\n", result[i].first, result[i].second);
	}*/

	return 0;
}
