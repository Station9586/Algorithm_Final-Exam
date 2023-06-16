#include <bits/stdc++.h>
#define pb push_back
#define INF INT_MAX
#define all(x) (x).begin(), (x).end()
#ifdef LOCAL
#define eprintf(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); }
#else
#define eprintf(...) 42
#endif

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef map<int, int> mi;

int n, m;

vi gp[10010];
vi rev[10010];

int scc[10010];
int idx = 0;

int vis[10010];

stack<int> book;

int cnt = 0;

void dfs1 (int a) {
    vis[a] = true;
    for (auto i: gp[a]) {
        if (!vis[i]) dfs1(i);
    }
    book.push(a);
}

void dfs2 (int a, int b) {
    vis[a] = true;
    scc[a] = idx;
    for (auto i: rev[a]) {
        if (!vis[i]) dfs2(i, b);
    }
}

int main (int argc, const char* argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    int a, b;
    for (int i = 0; i < m; i ++) {
        cin >> a >> b;
        gp[a].pb(b);
        rev[b].pb(a);
    }

    for (int i = 1; i <= n; i ++) {
        if (!vis[i]) dfs1(i);
    }

    memset(vis, 0, sizeof(vis));

    while (!book.empty()) {
        int now = book.top();
        book.pop();
        if (vis[now]) continue;
        idx ++;
        dfs2(now, now);
    }

    vi in(idx, 0);

    for (int i = 1; i <= n; i ++) {
        for (auto j: gp[i]) {
            if (scc[i] != scc[j]) {
                in[scc[j] - 1] ++;
            }
        }
    }

    if (count(all(in), 0) > 1) cout << "No source vertex.\n";
    else cout << "Has a source vertex.\n";
    
    return 0;
}