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

int main() {
    vi v(4); AREP(&x, v) cin >> x; SORT(v);
    if (v[0] + v[1] > v[2] || v[1] + v[2] > v[3]) cout << "TRIANGLE" << endl;
    else if (v[0] + v[1] == v[2] || v[1] + v[2] == v[3]) cout << "SEGMENT" << endl;
    else cout << "IMPOSSIBLE" << endl;
}