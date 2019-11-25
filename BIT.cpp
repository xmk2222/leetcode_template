static vector<int> nums;
static vector<int> bit;
static vector<int> bit2;
static int n, m;

int lowbit(int k) {
	if (k == 0) return 0;
	return k & (-k);
}

//======================================
/*
//++++++++++++++初级树状数组++++++++++++++

void add(int id, int k) {
	// 对nums[id] 加上k，对应的对BIT的对应位置加k
	while (id <= n) {
		bit[id] += k;
		id += lowbit(id);
	}
}

int sum(int id) {
	// 返回nums[0:id]的和
	int ans = 0;
	while (id > 0) {
		ans += bit[id];
		id -= lowbit(id);
	}
	return ans;
}

//++++++++++++++点更新，区间查询++++++++++++++
void bit_test(){
	cin >> n >> m;
	bit = vector<int>(n + 1, 0);
	for (int i = 1; i < n+1; ++i) {
		int x;
		cin >> x;
		add(i, x);
	}
	while (m-- > 0) {
		int t, a, b;
		cin >> t >> a >> b;
		if (t == 1) {
			//update
			add(a, b);
		}
		if (t == 2) {
			// query
			cout << sum(b) - sum(a-1) << endl;
		}
	}
}

//++++++++++++++++区间更新，点查询++++++++++++
// 树状数组存储差分值
void bit_test() {
	cin >> n >> m;
	bit = vector<int>(n + 1, 0);
	nums = vector<int>(n + 1, 0);
	for (int i = 1; i < n + 1; ++i) {
		cin >> nums[i];
		add(i, nums[i] - nums[i - 1]);
	}
	while (m-- > 0) {
		int t, a, b, k;
		cin >> t;
		if (t == 1) {
			//update
			cin >> a >> b >> k;
			add(a, k);
			add(b + 1, -k);
		}
		if (t == 2) {
			// query
			cin >> a;
			cout << sum(a) << endl;
		}
	}
}
*/
//=====================================
//++++++++++++++++进阶树状数组++++++++++++++++
// 区间更新，区间查询，维护两个数组，公式为sum[1:n] = n * sum_1^n(bit[i]) - sum_1^n(bit[i] * (i-1))
// bit2[i] = bit[i] * (i - 1)

void add(int id, int k) {
	int i = id;
	while (id <= n) {
		bit[id] += k;
		bit2[id] += k * (i - 1);
		id += lowbit(id);
	}
}

int sum(int id) {
	int i = id;
	int ans = 0;
	while (id > 0) {
		ans += i * bit[id] - bit2[id];
		id -= lowbit(id);
	}
	return ans;
}

void bit_test() {
	cin >> n >> m;
	bit = vector<int>(n + 1, 0);
	bit2 = vector<int>(n + 1, 0);
	nums = vector<int>(n + 1, 0);
	for (int i = 1; i < n + 1; ++i) {
		cin >> nums[i];
		add(i, nums[i] - nums[i - 1]);
	}
	while (m-- > 0) {
		int t, a, b, k;
		cin >> t;
		if (t == 1) {
			//update
			cin >> a >> b >> k;
			add(a, k);
			add(b + 1, -k);
		}
		if (t == 2) {
			// query
			cin >> a >> b;
			cout << sum(b) - sum(a - 1) << endl;
		}
	}
}
