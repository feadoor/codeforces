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

ll gcd(ll a, ll b) {
    a = (a > 0) ? a : -a; b = (b > 0) ? b : -b;
    while (b != 0) {
        ll c = b; b = a % b; a = c;
    }
    return a;
}

pll bezout(ll a, ll b) {
    ll s = 0, old_s = 1;
    ll t = 1, old_t = 0;
    ll r = b, old_r = a;
    ll swap;

    while (r != 0) {
        ll q = old_r / r;
        swap = r; r = old_r - q * r; old_r = swap;
        swap = s; s = old_s - q * s; old_s = swap;
        swap = t; t = old_t - q * t; old_t = swap;
    }

    return (old_s * a + old_t * b) >= 0 ? MP(old_s, old_t) : MP(-old_s, -old_t);
}

ll invmod(ll a, ll m) {
    pll bz = bezout(a, m);
    return bz.F % m;
}

// Solves By == C mod A
ll dioph(ll b, ll c, ll a) {
    c = ((-c) % a); c = (c < 0) ? c + a : c;
    a = (a > 0) ? a : -a;
    ll g = gcd(b, a);
    if (c % g != 0) return MINFL;

    a = a / g; b = b / g; c = c / g;
    ll im = invmod(b, a);
    return (c * im) % a;
}

int main() {
    ll a, b, c; cin >> a >> b >> c;

    if (a == 0) {
        ll y = (-c) / b;
        if (b * y + c == 0) cout << 0 << " " << y << endl;
        else cout << -1 << endl;
    } else if (b == 0) {
        ll x = (-c) / a;
        if (a * x + c == 0) cout << x << " " << 0 << endl;
        else cout << -1 << endl;
    } else {
        ll y = dioph(b, c, a);
        if (y == MINFL) cout << -1 << endl;
        else {
            ll x = (-b * y - c) / a;
            cout << x << " " << y << endl;
        }
    }
}
