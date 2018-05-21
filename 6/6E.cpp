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

struct seg_node {
    int mini; int maxi;

    seg_node combine(seg_node other) {
        return {min(mini, other.mini), max(maxi, other.maxi)};
    }

    static seg_node combine(seg_node x, seg_node y) {
        return x.combine(y);
    }
};

struct seg_tree {
    int n; vec<seg_node> arr;

    seg_tree() : seg_tree(1) {}

    seg_tree(int n) : seg_tree(vi(n, 0)) {}

    seg_tree(vi v) {
        n = 1; while (n < SZ(v)) n *= 2;
        arr = vec<seg_node>(2 * n);

        REP(i, 0, SZ(v)) arr[n + i] = {v[i], v[i]};
        RREP(i, 1, n) {
            arr[i] = seg_node::combine(arr[2 * i], arr[2 * i + 1]);
        }
    }

    seg_node get(int a, int b) {
        a += n; b += n; seg_node s = {INF, MINF};
        while (a <= b) {
            if ((a & 1) == 1) s = s.combine(arr[a++]);
            if ((b & 1) == 0) s = s.combine(arr[b--]);
            a /= 2; b /= 2;
        }
        return s;
    }

    void update(int k, int x) {
        k += n; arr[k] = {x, x};
        for (k /= 2; k >= 1; k /= 2) {
            arr[k] = seg_node::combine(arr[2 * k], arr[2 * k + 1]);
        }
    }
};

int n, k;
seg_tree books;

bool is_good(int start, int end) {
    if (start > end) return true;
    seg_node s = books.get(start, end);
    return (s.maxi - s.mini <= k);
}

int main() {
    UNTIE();
    cin >> n >> k;
    books = seg_tree(n);

    int best = 0; vpi ranges;
    REP(i, 0, n) {
        int book; cin >> book; books.update(i, book);
        int j = -1; for (int step = i; step >= 1; step /= 2) {
            while (!is_good(j + step, i)) j += step;
        }
        if ((i - j) > best) {
            best = i - j; ranges.clear();
        }
        if ((i - j) == best) ranges.PB({j + 1, i});
    }

    cout << best << " " << SZ(ranges) << "\n";
    AREP(p, ranges) cout << p.F + 1 << " " << p.S + 1 << "\n";
}