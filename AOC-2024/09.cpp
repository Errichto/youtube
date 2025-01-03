#include <bits/stdc++.h>
using namespace std;

struct Block {
	int id, size, pos;
};

int main() {
	string s;
	cin >> s;
	int n = s.length();
	int pos = 0;
	vector<Block> blocks;
	for (int i = 0; i < n; i++) {
		int digit = s[i] - '0';
		if (i % 2 == 0) {
			for (int rep = 0; rep < digit; rep++) {
				blocks.push_back(Block{i/2, 1, pos + rep});
			}
		}
		pos += digit;
	}
	// for (Block block : blocks) {
		// cout << block.pos << " " << block.id << " " << block.size << "\n";
	// }
	// return 0;
	while (true) {
		Block me = blocks.back();
		blocks.pop_back();
		bool inserted = false;
		for (int i = 0; i < (int) blocks.size() - 1; i++) {
			int A = blocks[i].pos + blocks[i].size;
			int B = blocks[i+1].pos;
			if (B - A >= me.size) {
				inserted = true;
				me.pos = A;
				blocks.insert(blocks.begin() + i + 1, me);
				break;
			}
		}
		if (!inserted) {
			me.pos = blocks.back().pos + blocks.back().size;
			blocks.push_back(me);
			break;
		}
	}
	long long answer = 0;
	for (Block block : blocks) {
		// cout << block.pos << " " << block.id << "\n";
		answer += (long long) block.pos * block.id;
	}
	cout << answer << "\n";
}
