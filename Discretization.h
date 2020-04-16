template <typename T>
struct Discretization {
    vector<T> xp;
    int size() const { return xp.size(); }
    void add(T val) { xp.push_back(val); }
    void discretize() {
        sort(xp.begin(), xp.end());
        xp.resize(unique(xp.begin(), xp.end()) - xp.begin());
    }
    int get(T val) {
        return lower_bound(xp.begin(), xp.end(), val) - xp.begin() + 1;
    }
    void clear() { xp.clear(); }
    T get2(int num) { return xp[num - 1]; }
};