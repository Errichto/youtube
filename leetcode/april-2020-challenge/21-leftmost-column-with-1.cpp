/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int x, int y);
 *     vector<int> dimensions();
 * };
 */

//00000000111111111111111
//???????1???????????????

// O(H+W)

class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        vector<int> vec = binaryMatrix.dimensions();
        int H = vec[0], W = vec[1];
        int answer = W;
        for(int row = 0; row < H; ++row) {
            while(answer > 0 && binaryMatrix.get(row, answer - 1) == 1) {
                answer--;
            }
        }
        if(answer == W) {
            answer = -1;
        }
        return answer;
        /*
        vector<int> order;
        for(int i = 0; i < H; ++i) {
            order.push_back(i);
        }
        random_shuffle(order.begin(), order.end());
        for(int row : order) {
            if(answer == 0) {
                break;
            }
            int low = 0, high = answer - 1;
            // first one
            if(binaryMatrix.get(row, high) == 0) {
                continue;
            }
            // O(H + log(H) * log(W))
            while(low <= high) {
                int mid = low + (high - low) / 2;
                if(binaryMatrix.get(row, mid) == 1) {
                    answer = min(answer, mid);
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
            }
        }
        if(answer == W) {
            answer = -1;
        }
        return answer;*/
    }
};
