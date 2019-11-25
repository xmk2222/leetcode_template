// Disjoint-set 并查集

#include "stdafx.h"

#include <vector>
using namespace std;

int N;
vector<int> father(N, -1);

int find_father(int x) {
	return x == father[x] ? x : father[x] = find_father(father[x]);
}

void join(int x, int y) {
	// join x and y
	father[find_father(x)] = find_father(y);
}
