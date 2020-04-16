#define get(p) nodes[p]
template <typename T>
struct Queue {
    T nodes[MAXN * 4];
    int head, tail;

    Queue() {
        head = 1;
        tail = 0;
    }
    inline bool empty() const { return head > tail; }
    inline void clear() {
        head = 1;
        tail = 0;
    }
    inline void push_back(T val) { nodes[++tail] = val; }
    inline void pop_back() { tail--; }
    inline void push_front(T val) { nodes[--head] = val; }
    inline void pop_front() { head++; }
    inline T front() const { return get(head); }
    inline T back() const { return get(tail); }
};