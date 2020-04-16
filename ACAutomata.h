#include <queue>
#include <string>

using namespace std;
struct AC_Automata {
    static const int LETTERS = 26;
    struct TNode {
        TNode* children[LETTERS];
        TNode* fail;
        int cnt;

        TNode() {
            cnt = 0;
            fail = nullptr;
            memset(children, 0, sizeof(children));
        }
    };

    TNode* root;

    AC_Automata() { root = new TNode(); }

    inline void insert(const string& word) {
        TNode* node = root;
        int size = word.size();
        for (int i = 0; i < size; i++) {
            char c = word[i] - 'a';
            if (!node->children[c]) {
                node->children[c] = new TNode();
            }
            node = node->children[c];
        }
        node->cnt++;
    }

    inline void build() {
        queue<TNode*> Q;
        for (int i = 0; i < LETTERS; i++) {
            if (root->children[i]) {
                root->children[i]->fail = root;
                Q.push(root->children[i]);
            }
        }
        while (!Q.empty()) {
            auto cur = Q.front();
            Q.pop();
            for (int i = 0; i < LETTERS; i++) {
                if (cur->children[i]) {
                    TNode* p = cur->fail;
                    while (!p->children[i]) {
                        p = p->fail;
                    }
                    if (!p)
                        cur->children[i]->fail = root;
                    else
                        cur->children[i]->fail = p->children[i];
                    Q.push(cur->children[i]);
                }
            }
        }
    }
    inline int query(const string& str) {
        int size = str.size();
        TNode* node = root;
        int ans = 0;
        for (int i = 0; i < size; i++) {
            int c = str[i] - 'a';
            while (!node->children[c] && node != root) node = node->fail;
            TNode* p = node->children[c];
            if (!p) p = root;
            node = p;
            while (p != root) {
                if (p->cnt > 0) {
                    ans += p->cnt;
                    p->cnt = -1;
                } else
                    break;
                p = p->fail;
            }
        }
        return ans;
    }
};