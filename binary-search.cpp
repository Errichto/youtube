// 1) Looking for 'target' in a sorted array.
int f() {
    int left = 0, right = n - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(a[mid] == target) {
            return mid;
        }
        else if(a[mid] > target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1;
}

// 2) Looking for the index of the first element that satisfies some property.
// F F T T T T <- find first index that has TRUE
int f() {
    int left = 0, right = n - 1; // add +1 to 'right' if the answer can be outside [left, right]
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(property(mid)) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
    return left;
}


// ========== Everything below is just notes/drafts. ==========













#include <iostream>
using namespace std;

// easy version
int f() {
	int left = 0, right = n - 1;
	while(left <= right) {
		int mid = left + (right - left) / 2;
		if(a[mid] == x) {
			return mid;
		}
		if(a[mid] > x) {
			right = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	return -1; // no element
}



// 1) F F T T T T <- find first index that has TRUE

// 2) T T T T F F <- find last index that has TRUE

// Gupta's version
int f() { // version (1)
	int left = 0, right = n - 1;
	int ans = n;
	while(left <= right) {
		int mid = left + (right - left) / 2;
		if(property(mid)) {
			ans = min(ans, mid); // ans = min(ans, mid)
			right = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	return ans;
}
int f() { // version (2)
	int left = 0, right = n - 1;
	int ans = -1;
	while(left <= right) {
		int mid = left + (right - left) / 2;
		if(property(mid)) {
			ans = max(ans, mid); // ans = min(ans, mid)
			low = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return ans;
}

// standard version
int f() { // version (1) T T T T F F F <- find last index that has TRUE
	int left = 0, right = n; // find first FALSE instead
	while(left < right) {
		int mid = left + (right - left) / 2;
		if(!property(mid)) {
			right = mid;
		}
		else {
			left = mid + 1;
		}
	}
	return left - 1; // returns -1 if there are no such elements
}

// [5, 10, 15]
//  F  F   F  T

// [4, 6, 8, 7, 1]
//  F  F  T  T  ?
//  [2, 4, 5, 9]
//   F  F  F  ?
int f() { // version (2) F F T T T T <- find first index that has TRUE
	// answer not defined for [F F F] so let N be the answer then
	int left = 0, right = n; // search in interval [0, n]
	while(left < right) {
		int mid = left + (right - left) / 2; // _ _ _ _
		// if(mid == n - 1 || a[mid] > a[mid+1]) { //property(mid)) {
		if(property(mid)) {
			right = mid;
		}
		else {
			left = mid + 1; // [n-1, n] -> mid = n - 1    --> interval [n, n]
		}
	}
	// left == right
	return left; // returns n if no such elements
}


// short version from CF
// [5, 7, 10, 15, 14, 10]
//  F  F  F   T    T  ?

// [5, 7, 10, 15]
//  F  F  F    ?

// N = 4
//   0 1 2 3  
// ? T T T T ?

int f() {  // version (2) F F T T T T <- find first index that has TRUE
	int left = -1, right = n; // [F F F] -> [(F) F F F (T)]
	// N = 3
	// [x, x, 1, 2, 3]
	while(right - left > 1) {
		int mid = left + (right - left) / 2;
		if(a[mid] > a[mid+1]) { //property(mid)) {
			right = mid;
		}
		else {
			left = mid;
		}
	}
	return right; // first TRUE
	// return left; // last FALSE
}



// 2 4 5 10 15 24
// find the first element not smaller than 6
bool property(int i) {
	return a[i] >= 6;
}

// find the last element not greater than 20
// -> find the first element greater than 20
bool property(int i) {
	return a[i] > 20;
}
// 5, 6, 7
// 30, 40, 50

int f() {
	int left = 0, right = n - 1;
	while(left <= right) {
		int mid = (left + right) / 2;
		if(a[mid] == x) {
			return mid;
		}
		if(a[mid] < x) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return -1; // not found :(
	
	property: a[mid] < a[mid+1]
	
	// find the first element with some property
	int left = 0, right = n - 1;
	// left = 5, right = 6 -> mid = 5
	
	// _   _   _   _
	//     m  m+1
	
	while(left < right) {
		int mid = left + (right - left) / 2;
		if(a[mid] > a[mid+1]) {
			right = mid;
		}
		else {
			left = mid + 1; // look to the right
		}
	}
	return left;
}

int main() {
	
	
}
