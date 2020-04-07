class Solution {
    int f(int n) { // log(N)
        int sum = 0;
        while(n) {
            int digit = n % 10;
            n /= 10;
            sum += digit * digit;
        }
        return sum;
    }
public:
    bool isHappy(int n) {
        for(int rep = 0; rep < 20; rep++) {
            n = f(n);
            if(n == 1) {
                return true;
            }
        }
        return false;
    }
        /*
        unordered_set<int> visited;
        for(int rep = 0; rep < 20; ++rep) {
            if(n == 1) {
                return true;
            }
            n = f(n);
            if(visited.count(n) == 1) {
                return false;
            }
            visited.insert(n);
        }
        assert(false);
    }*/
};
