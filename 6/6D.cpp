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
#define INFL numeric_limits<ll>::max()

#define MMOD(x, m) ((x) < 0 ? (x) % (m) + (m) : (x) % (m))
#define ABS(x) ((x) < 0 ? -(x) : (x))

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

int n, a, b; vi h;
int nxt[10][17][17];
int memo[10][17][17];

int solve(int pos, int prev, int pprev) {
    if (memo[pos][prev][pprev] != -1) return memo[pos][prev][pprev];
    if (pos == n - 1) {
        if (prev * b <= h[pos]) return memo[pos][prev][pprev] = 1e9;
        else return memo[pos][prev][pprev] = 0;
    }

    int ans = 1e9; int tmp; REP(curr, 0, 17) {
        if (pprev * b + prev * a + curr * b <= h[pos - 1]) continue;
        if ((tmp = (curr + solve(pos + 1, curr, prev))) < ans) {
            ans = tmp;
            nxt[pos][prev][pprev] = curr;
        }
        if (prev * b + curr * a > h[pos] && curr * b > h[pos + 1]) break;
    }
    return memo[pos][prev][pprev] = ans;
}

int solve() {
    memset(memo, -1, sizeof memo);
    return solve(1, 0, 0);
}

void output(int pos, int prev, int pprev) {
    if (pos == n - 1) return;
    REP(i, 0, nxt[pos][prev][pprev]) cout << pos + 1 << " ";
    output(pos + 1, nxt[pos][prev][pprev], prev);
}

void output() {
    output(1, 0, 0);
}

int main() {
    cin >> n >> a >> b;
    h = vi(n); AREP(&v, h) cin >> v;
    cout << solve() << endl; output();
}