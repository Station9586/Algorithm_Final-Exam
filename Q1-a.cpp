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

int vis[10010];

unordered_set<int> book;

void dfs (int a) {
    vis[a] = true; // 經過該點後將其的vis設為true代表已經走過，避免重複走訪
    for (auto i: gp[a]) { // 走過該點所有的子節點
        if (!vis[i]) dfs(i); // 不斷走訪該點可到達的最遠路徑
    }
    book.insert(a); // 紀錄所有走過的點
}

int main (int argc, const char* argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m; // 總共有 n 個節點與 m 條邊
    int a, b, x;
    for (int i = 0; i < m; i ++) {
        cin >> a >> b;
        gp[a].pb(b); // 建圖 (使用vector紀錄圖的資訊)
    }
    cin >> x; // 輸入欲判斷的點，並判斷是否為source vertex.
    dfs(x); // 直接由該點去走訪DFS，若可以走到所有其他的點就代表是source vertex
    if (book.size() == n) cout << x << " is a source vertex.\n"; // unordered_set大小 == n 代表可以經過所有的點 -> source vertex.
    else cout << x << " isn't a source vertex.\n"; // 反之則不是
    return 0;
}