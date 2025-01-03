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
			blocks.push_back(Block{i/2, digit, pos});
		}
		pos += digit;
	}
	string out(pos, '.');
	long long answer = 0;
	while ((int) blocks.size() >= 2) {
		Block me = blocks.back();
		// blocks.pop_back();
		bool inserted = false;
		for (int i = 0; i < (int) blocks.size() - 1; i++) {
			int A = blocks[i].pos + blocks[i].size;
			int B = blocks[i+1].pos;
			if (B - A >= me.size) {
				inserted = true;
				me.pos = A;
				blocks.pop_back();
				blocks.insert(blocks.begin() + i + 1, me);
				break;
			}
		}
		if (!inserted) {
			blocks.pop_back();
			// me.pos = blocks.back().pos + blocks.back().size;
			cout << me.pos << " " << me.id << endl;
			// blocks.push_back(me);
			for (int j = 0; j < me.size; j++) {
				answer += (me.pos+j) * me.id;
				out[me.pos+j] = '0' + me.id;
			}
			// break;
		}
	}
	Block me = blocks[0];
	for (int j = 0; j < me.size; j++) {
		out[me.pos+j] = '0' + me.id;
		// answer += (me.pos+j) * me.id;
	}
	cout << out << "\n";
	// for (Block block : blocks) {
		// answer += block.pos * block.id;
	// }
	cout << answer << "\n";
}
