double A;
double f(double x) { return sqrt(1 + 4 * A * A * x * x); }

double simpson(double a, double b) {
    double c = a + (b - a) / 2;
    return (f(a) + 4 * f(c) + f(b)) * (b - a) / 6;
}

double asr(double a, double b) {
    double mid = a + (b - a) / 2;
    double cur = simpson(a, b);
    double fl = simpson(a, mid), fr = simpson(mid, b);
    if (fabs(fl + fr - cur) < 15 * EPS) return fl + fr + (fl + fr - cur) / 15;
    return asr(a, mid) + asr(mid, b);
}

double getlen(double w, double h) {
    A = 4 * h / (w * w);
    return 2 * asr(0, w / 2);
}
