#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//++++++++++++++++++++++++++++++++树结构实现++++++++++++++++++++++++++++++++
/*

struct SNode {
	int val;
	int start;
	int end;
	int lazy_tag;
	SNode *left;
	SNode *right;
	SNode(int x, int l, int r): val(x), start(l), end(r), lazy_tag(0), left(NULL), right(NULL){}
};


SNode* build_tree(vector<int>& line, int l, int r) {
	// 根据输入线段，构造线段树并返回
	SNode *root = new SNode(0, l, r);
	if (l == r) {
		root->val = line[l];
		return root;
	}
	int m = (l + r) >> 1;
	root->left = build_tree(line, l, m);
	root->right = build_tree(line, m + 1, r);
	root->val = root->left->val + root->right->val;
	//printf("tree[%d:%d] = %d\n", l, r, root->val);
	return root;
}

void update(SNode* root, int l, int r, int v) {
	// 更新区间l到r，每个值加v, 默认区间不能大于root的区间
	root->val += v * (min(root->end, r) - max(root->start, l) + 1);
	if (l <= root->start && r >= root->end) {
		root->lazy_tag = v;
		return;
	}
	if (l > root->end || r < root->start) return;
	update(root->left, l, r, v);
	update(root->right, l, r, v);
}

void push_down(SNode* root) {
	if (root->lazy_tag == 0) return;
	int l = root->start, r = root->end;
	int v = root->lazy_tag;
	root->lazy_tag = 0;
	update(root->left, l, r, v);
	update(root->right, l, r, v);
}

int query(SNode* root, int l, int r) {
	// 查询区间l到r的和，默认区间不能大于root的区间
	if (l <= root->start && r >= root->end) return root->val;
	if (l > root->end || r < root->start) return 0;
	push_down(root);
	int ans = 0;
	ans += query(root->left, l, r);
	ans += query(root->right, l, r);
	printf("tree[%d:%d] = %d\n", max(root->start, l), min(root->end, r), ans);
	return ans;
}



void segment_tree_test() {
	vector<int> line(1000, 1);
	SNode * stree = build_tree(line, 0, 999);
	update(stree, 401, 700, 1);
	update(stree, 300, 600, 1);
	cout << query(stree, 301, 700) << endl;
}

*/

// +++++++++++++++++++++++++++++数组实现+++++++++++++++++++++++++++++++++++++
struct snode {
	int l, r;
	int sum;
	int tag;
	snode(int x, int a, int b) : sum(x), l(a), r(b), tag(0) {}
};

static vector<int> nums;
static vector<snode> stree;

int build(int id, int a, int b) {
	stree[id].l = a;
	stree[id].r = b;
	if (a == b) {
		//叶子节点
		stree[id].sum = nums[a];
		//printf("stree[%d](%d ~ %d) set as %d\n", id, a, b, stree[id].sum);
		return nums[a];
	}
	int c = (a + b) / 2;
	stree[id].sum = build(id * 2 + 1, a, c) + build(id * 2 + 2, c + 1, b);
	//printf("stree[%d](%d ~ %d) set as %d\n", id, a, b, stree[id].sum);
	return stree[id].sum;
}

void update(int id, int a, int b, int x) {
	// 更新a到b的区间，每个元素加x
	int l = stree[id].l, r = stree[id].r;
	if (l > b || r < a) return;
	stree[id].sum += (min(r, b) - max(l, a) + 1) * x;
	if (l >= a && r <= b) {
		stree[id].tag = x;
		return;
	}
	update(id * 2 + 1, a, b, x);
	update(id * 2 + 2, a, b, x);
}

void push_down(int id) {
	// 传递tag
	update(id * 2 + 1, stree[id].l, stree[id].r, stree[id].tag);
	update(id * 2 + 2, stree[id].l, stree[id].r, stree[id].tag);
	stree[id].tag = 0;
}

int query(int id, int a, int b) {
	// 查询a到b的区间
	int l = stree[id].l, r = stree[id].r;
	if (l > b || r < a) return 0;
	if (l >= a && r <= b) {
		return stree[id].sum;
	}
	push_down(id);
	return query(id * 2 + 1, a, b) + query(id * 2 + 2, a, b);
}



int segment_tree_test() {
	int n, m;
	cin >> n >> m;
	nums = vector<int>(n, 0);
	for (int i = 0; i < n; ++i) {
		cin >> nums[i];
	}
	stree = vector<snode>(2 * n, snode(0, 0, 0));
	build(0, 0, n - 1);
	while (m-- > 0) {
		int t, a, b;
		cin >> t >> a >> b;
		if (t == 1) {
			// update
			update(0, a-1, a-1, b);
		}
		if (t == 2) {
			// query
			cout << query(0, a-1, b-1) << endl;
		}
	}
	return 0;
}
