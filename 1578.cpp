#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int t, n, m, cnt;
int cl[N], vi[N], s[N], top;
vector<int> g[N], cy[N];

void solve(int u, int p) {
    vi[u] = 1;
    s[++top] = u;
    for (int v : g[u]) {
        if (!vi[v]) {
            solve(v, u);
        } else if (v != p && vi[v] == 1) {
            cnt++;
            cy[cnt].push_back(v);
            while (s[top+1] != v) {
                cy[cnt].push_back(s[top--]);
            }
            cy[cnt].push_back(v);
        }
    }
    vi[u] = 2;
    top--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            g[i].clear();
            cl[i] = vi[i] = 0;
        }
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        cnt = top = 0;
        for (int i = 1; i <= n; i++) {
            if (!vi[i]) {
                solve(i, -1);
            }
        }
        bool ok = true;
        for (int i = 1; i <= cnt; i++) {
            int sz = cy[i].size();
            if (sz > 400001) {
                ok = false;
                break;
            }
            for (int j = 0; j < sz; j++) {
                int x = cy[i][j];
                cl[x] = j % 2;
            }
        }
        if (!ok) {
            cout << "No\n";
            continue;
        }
        cout << "Yes\n";
        for (int i = 1; i <= n; i++) {
            cout << cl[i] << " " << (i <= 200000 ? i-1 : i-200001) << "\n";
        }
    }
    return 0;
}
