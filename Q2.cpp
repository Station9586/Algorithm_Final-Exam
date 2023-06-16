#include <bits/stdc++.h>
#define pb push_back
#define INF INT_MAX
 
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef map<int, int> mi;
 
int vis[1000];
ll gp[1000][1000] = {};
int parent[600];
 
int n, m;
 
ll ans = 0;
 
bool bfs () {
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 1; i <= n; i ++) {
            if (gp[now][i] > 0 and !vis[i]) {
                q.push(i);
                vis[i] = true;
                parent[i] = now;
            }
        }
    }
    return vis[n]; // 1 -> 還有路徑, 0 -> 沒有路徑
}

int main (int argc, const char* argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    int a, b, c;
    for (int i = 0; i < m; i ++) {
        cin >> a >> b >> c;
        gp[a][b] += c;
    }
    cout << "Initial: " << "\n";
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (gp[i][j] != 0) cout << i << " -> " << j << ": " << gp[i][j] << "\n";
        }
    }
    cout << "\nAugmenting Paths: \n";
    while (bfs()) {
        ll flow = 1e18;
        for (int i = n; i != 1; i = parent[i]) { // 1. 找到路徑和終點連接的點, 接者找和該點連接的點直到為起點 1 為止
            flow = min(flow, gp[parent[i]][i]); // 找最小的 flow
        }
        ans += flow;
        for (int i = n; i != 1; i = parent[i]) {
            gp[parent[i]][i] -= flow; // 扣掉
            gp[i][parent[i]] += flow; // 可以反悔
        }
        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j <= n; j ++) {
                // cout << gp[i][j] << " ";
                if (gp[i][j] != 0) cout << i << " -> " << j << ": " << gp[i][j] << "\n";
            }
        }
        cout << "\n";
    }
    cout << "Maximum Flow: " << ans << "\n";
    return 0;
}