namespace IO {
const int MAXSIZE = 1 << 20;
char buf[MAXSIZE], *p1, *p2;
#define gc()                                                                 \
    (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) \
         ? EOF                                                               \
         : *p1++)
inline int rd() {
    int x = 0, f = 1;
    char c = gc();
    while (!isdigit(c)) {
        if (c == '-') f = -1;
        c = gc();
    }
    while (isdigit(c)) x = x * 10 + (c ^ 48), c = gc();
    return x * f;
}
char pbuf[1 << 20], *pp = pbuf;
inline void push(const char& c) {
    if (pp - pbuf == 1 << 20) fwrite(pbuf, 1, 1 << 20, stdout), pp = pbuf;
    *pp++ = c;
}
inline void flush() { fwrite(pbuf, 1, pp - pbuf, stdout), pp = pbuf; }
inline void write(int x) {
    static int sta[35];
    if (x < 0) x = -x, push('-');
    int top = 0;
    do {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) push(sta[--top] + '0');
    push('\n');
}

inline void writeInt(int x) {
    static int sta[35];
    if (x < 0) x = -x, putchar('-');
    int top = 0;
    do {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) putchar(sta[--top] + 48);
    putc('\n', stdout);
}
}  // namespace IO