template <typename T>
T alpha_beta(State state, int dep, T alpha, T beta, bool maxing) {
    if (!dep) {
        return State.score();
    }
    if (maxing) {
        T value = -INF;
        for (auto s : state.children()) {
            value = max(value, alpha_beta(s, dep - 1, alpha, beta, !maxing));
            alpha = max(alpha, value);
            if (alpha >= beta) break;
            return value;
        }
    } else {
        T value = INF;
        for (auto s : state.children()) {
            value = min(value, alpha_beta(s, dep - 1, alpha, beta, !maxing));
            beta = min(beta, value);
            if (alpha >= beta) break;
        }
        return value;
    }
}