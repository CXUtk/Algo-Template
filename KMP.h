#include <string>
using namespace std;

char text[MAXN];
char substr[MAXN];
int fail[MAXN];
void getFail() {
    fail[1] = 0;
    // m: size of substring
    for (int i = 2; i <= m; i++) {
        int cur = i - 1, pre = fail[i - 1];
        while (pre && substr[pre + 1] != substr[i]) cur = pre, pre = fail[pre];
        if (substr[pre + 1] == substr[i]) fail[i] = fail[cur] + 1;
    }
}
void match() {
    // n: length of text string
    int psub = 0;
    for (int i = 1; i <= n; i++) {
        while (psub && substr[psub + 1] != text[i]) psub = fail[psub];
        if (substr[psub + 1] == text[i]) psub++;
        if (psub == m) {
            // found string !!
            printf("%d\n", i - m + 1);
        }
    }
}

void getFail(int* fail, const char* substr) {
    int m = strlen(substr);
    fail[0] = fail[1] = 0;
    for (int i = 1; i < m; i++) {
        int j = fail[i];
        while (j && substr[i] != substr[j]) j = fail[j];
        fail[i + 1] = (substr[i] == substr[j] ? j + 1 : 0);
    }
}

void getFail(int* fail, const string& str) {
    int m = str.size();
    fail[0] = fail[1] = 0;
    for (int i = 1; i < m; i++) {
        int j = fail[i];
        while (j && substr[i] != substr[j]) j = fail[j];
        fail[i + 1] = (substr[i] == substr[j] ? j + 1 : 0);
    }
}