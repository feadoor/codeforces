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

vi memory; vpi blocks; int blk;

bool can_alloc(int i, int s) {
    REP(j, i, i + s) {
        if (j >= SZ(memory) || memory[j] > 0) return false;
    }
    return true;
}

void alloc(int s) {
    REP(i, 0, SZ(memory)) {
        if (can_alloc(i, s)) {
            blocks.PB(MP(i, s));
            fill(memory.begin() + i, memory.begin() + i + s, ++blk);
            cout << blk << endl;
            return;
        }
    }
    cout << "NULL" << endl;
}

void erase(int b) {
    if (b <= 0 || b > SZ(blocks) || blocks[b - 1].S == 0) cout << "ILLEGAL_ERASE_ARGUMENT" << endl;
    else {
        int i = blocks[b - 1].F, s = blocks[b - 1].S;
        fill(memory.begin() + i, memory.begin() + i + s, 0);
        blocks[b - 1] = MP(i, 0);
    }
}

void defrag() {

    vi newmem = memory;
    auto newit = newmem.begin();
    REPA(it, memory.begin(), memory.end()) {
        if (*it > 0) *(newit++) = *it;
    }
    fill(newit, newmem.end(), 0);
    memory = newmem;

    vb seen(SZ(blocks), false); int left = 0;
    AREP(m, newmem) {
        if (m > 0 && !seen[m - 1]) {
            seen[m - 1] = true;
            blocks[m - 1] = MP(left, blocks[m - 1].S);
            left += blocks[m - 1].S;
        }
    }
}

int main() {
    int reps, mems; cin >> reps >> mems;
    memory = vi(mems, 0);
    string command; int param;

    REP(r, 0, reps) {
        cin >> command;
        if (command == "defragment") defrag();
        else if (command == "alloc") { cin >> param; alloc(param); }
        else if (command == "erase") { cin >> param; erase(param); }
    }
}
