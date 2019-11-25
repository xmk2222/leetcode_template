#include "stdafx.h"
#include <stdio.h>
#include <cstring>

using namespace std;

void get_next(char* p, int *next) {
	int n = strlen(p);
	next[0] = -1;
	int i = -1;
	int j = 0;
	while (j < n) {
		if (i == -1 || p[i] == p[j]) {
			next[++j] = ++i;
		}
		else {
			i = next[i];
		}
	}
}

int kmp_search(char* s, char* p) {
	const int plen = strlen(p), slen = strlen(s);
	int *next = new int[plen];
	get_next(p, next);
	int i = 0, j = 0;
	while (i < slen && j < plen) {
		if (j == -1 || s[i] == p[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	if (j == plen) return i - j;
	else return -1;
}

void kmp_test() {
	char* s = "dababcdabcdabd";
	char* p = "abcdabd";
	printf("%s\n%s\n%d\n", s, p, kmp_search(s, p));
}
