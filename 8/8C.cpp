#ifndef __SCL_STD_HEADER
#define __SCL_STD_HEADER

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define RESET_IS(is) (is).ignore(numeric_limits<streamsize>::max(), '\n')
#define UNTIE() ios::sync_with_stdio(0); cin.tie(0)
#define SETP(p) cout << setprecision(p)
#define FIX_OS() cout << fixed

typedef unsigned int uint;
typedef long long ll; typedef unsigned long long ull;
typedef vector<int> vi; typedef vector<uint> vui;
typedef vector<ll> vll; typedef vector<ull> vull;
typedef vector<bool> vb;
typedef vector<double> vd;
typedef vector<string> vs;

typedef pair<int, int> pi; typedef pair<uint, uint> pui;
typedef pair<ll, ll> pll; typedef pair<ull, ull> pull;
typedef pair<double, double> pd;
typedef vector<pi> vpi; typedef vector<pui> vpui;
typedef vector<pll> vpll; typedef vector<pull> vpull;
typedef vector<pd> vpd;

template <typename T> using vec = vector<T>;
template <typename T, typename S> using umap = unordered_map<T, S>;
template <typename T> using uset = unordered_set<T>;
template <typename T> using mset = multiset<T>;
template <typename T> using umset = unordered_multiset<T>;
template <typename T> using pqueue = priority_queue<T>;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> iset;

#define INF numeric_limits<int>::max()
#define MINF numeric_limits<int>::min()
#define INFL numeric_limits<ll>::max()
#define MINFL numeric_limits<ll>::min()

#define MMOD(x, m) ((x) < 0 ? (x) % (m) + (m) : (x) % (m))
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define SQ(x) ((x) * (x))

#define REP(i, a, b) for (int i = (a); i < (b); ++i)
#define REPL(i, a, b) for (ll i = (a); i < (b); ++i)
#define REPA(i, a, b) for (auto i = (a); i < (b); ++i)
#define RREP(i, a, b) for (int i = (b); --i >= (a);)
#define RREPL(i, a, b) for (ll i = (b); --i >= (a);)
#define RREPA(i, a, b) for (auto i = (b); --i >= (a);)

#define INREP(i, a, b) for (int i = (a); i <= (b); ++i)
#define INREPL(i, a, b) for (ll i = (a); i <= (b); ++i)
#define INREPA(i, a, b) for (auto i = (a); i <= (b); ++i)
#define INRREP(i, a, b) for (int i = (b); i >= (a); --i)
#define INRREPL(i, a, b) for (ll i = (b); i >= (a); --i)
#define INRREPA(i, a, b) for (auto i = (b); i >= (a); --i)

#define AREP(v, con) for (auto v : (con))

#define PB push_back
#define PF push_front
#define POPB pop_back
#define POPF pop_front
#define MP make_pair
#define MT make_tuple
#define F first
#define S second
#define LB lower_bound
#define UB upper_bound
#define EQR equal_range

#define SZ(v) ((int) (v).size())
#define ALL(v) (v).begin(), (v).end()
#define RALL(v) (v).rbegin(), (v).rend()

#define SORT(v) sort(ALL(v))
#define RSORT(v) sort(RALL(v))

#define MAXE(v) max_element(ALL(v))
#define MINE(v) min_element(ALL(v))

#endif

int d[25][25]; int ans[1<<25]; int coords[25][25]; int nexts[1<<25];

int main() {
    int hx, hy; cin >> hx >> hy;
    int n; cin >> n;
    coords[n][0] = hx; coords[n][1] = hy;

    REP(i, 0, n) {
        cin >> coords[i][0] >> coords[i][1];
    }

    INREP(i, 0, n) {
        INREP(j, 0, n) {
            d[i][j] = SQ(coords[i][0] - coords[j][0]) + SQ(coords[i][1] - coords[j][1]);
        }
    }

    REP(i, 0, 1<<n) ans[i] = INF;
    ans[0] = 0;

    REP(i, 0, 1<<n) if (ans[i] < INF) {
        REP(j, 0, n) if (!(i & (1 << j))) {
            REP(k, j, n) if (!(i & (1 << k))) {
                int l = i | (1 << j) | (1 << k);
                int poss = ans[i] + d[n][j] + d[j][k] + d[k][n];
                if (ans[l] > poss) ans[l] = poss, nexts[l] = i;
            }
            break;
        }
    }

    cout << ans[(1 << n) - 1] << endl;
    int fin = (1 << n) - 1;
    while (fin) {
        int nextfin = nexts[fin]; int outs = fin ^ nextfin;
        cout << 0 << " ";
        REP(i, 0, n) if (outs & (1 << i)) cout << i + 1 << " ";
        fin = nextfin;
    }
    cout << 0 << endl;
}
