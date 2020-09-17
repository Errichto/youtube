class MinStack {
public:
    
    /*4, 6, 3, 2
    (4, 4)
    (6, 4)
    (3, 3)
    (2, 2)*/
    
    stack<pair<int,int>> s;
        
    /** initialize your data structure here. */
    MinStack() {
        //while(!s.empty()) {
         //   s.clear();
            
    }
    
    void push(int x) {
        if(s.empty()) {
            s.push({x, x});
        }
        else {
            s.push({x, min(x, s.top().second)});
        }
    }
    
    void pop() {
        if(!s.empty()) {
            s.pop();
        }
    }
    
    int top() {
        return s.top().first;
    }
    
    int getMin() {
        return s.top().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
