// My old implementation of binary search.

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
