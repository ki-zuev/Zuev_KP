#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "func.h"
#include <chrono>
using namespace std;

int main(int argc, char *argv[])
{
	int n = 0, m, i, z1=0, z=0;
	char *filename = 0;
	if (argc != 2)
	{
		printf("Usage: %s input\n", argv[0]);
		return 1;
	}
	filename = argv[1];
	FILE *f;
	f = fopen(filename, "r");
	if (fscanf(f, "%d", &z1) == 1)
	{
		m = z1;
	}
	vector<pair<int,pair<int,int>>> g(m);
	while (fscanf(f, "%d", &z) == 1)
	{
		g[n].first = z;
		fscanf(f, "%d", &z);
		g[n].second.first = z;
		fscanf(f, "%d", &z);
		g[n].second.second = z;
		n = n+1;
	}
	n = g[m-1].second.second;
	fclose(f);

	double k;
	vector<point> mas(n);
	for (i = 0; i < n; i++)
	{
		k = i;
		mas[i].a.first = i;
		mas[i].a.second = k/10;
	}
	Steiner s(mas, n);
	s.steiner();
	s.get();

	vector<pair<int,int>> res;
	res = s.kruskal(g, m, n);
	for (i = 0; i < res.size(); i++)
	{
		printf("%d %d\n", res[i].first, res[i].second);
	}

	return 0;
}
