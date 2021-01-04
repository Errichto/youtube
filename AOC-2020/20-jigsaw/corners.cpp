	// ...
	long long product = 1;
	for(Tile a : tiles) {
		for(Tile b : tiles) {
			if(a.matches(b) && a.id != b.id) {
				degree++;
			}
		}
		if(degree == 2) { // corner
			product *= a.id;
		}
	}
	cout << product;
}
