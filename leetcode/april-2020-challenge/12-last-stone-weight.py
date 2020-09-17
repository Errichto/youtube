import heapq 
class Solution:
    def lastStoneWeight(self, stones: List[int]) -> int:
        size = len(stones)
        for i in range(size):
            stones[i] = -stones[i]
        heapq.heapify(stones)
        while size >= 2:
            y = -heapq.heappop(stones)
            x = -heapq.heappop(stones)
            if x == y:
                size -= 2
            else:
                size -= 1
                heapq.heappush(stones, -(y - x))
        if size == 0:
            return 0
        return -heapq.heappop(stones)
        
