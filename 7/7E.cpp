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

enum Op { ADD, MUL, NONE };

struct def {
    Op op;
    bool unsafe;
};

struct part {
    Op op;
    bool from_def;
};

string line; int pos;
bool unsafe = false;
umap<string, def> defs;

part parse_expr();
part parse_add();
part parse_mul();

char next_char() {
    for (; pos < SZ(line) && line[pos] <= ' '; ++pos);
    return line[pos];
}

part parse_expr() {
    part p1 = parse_add();
    while (next_char() == '-' || next_char() == '+') {
        char ch = next_char(); ++pos;
        part p2 = parse_add();
        if (p2.op == Op::ADD && p2.from_def && ch == '-') unsafe = true;
        if (p1.op == Op::ADD && p1.from_def || p2.op == Op::ADD && p2.from_def) p1.from_def == true;
        else p1.from_def == false;
        p1.op = Op::ADD;
    }
    return p1;
}

part parse_add() {
    part p1 = parse_mul();
    while (next_char() == '*' || next_char() == '/') {
        char ch = next_char(); ++pos;
        part p2 = parse_mul();
        if (p1.op == Op::ADD && p1.from_def || p2.op == Op::ADD && p2.from_def || p2.op == Op::MUL && p2.from_def && ch == '/') unsafe = true;
        if (p1.op == Op::MUL && p1.from_def || p2.op == Op::MUL && p2.from_def) p1.from_def == true;
        else p1.from_def == false;
        p1.op = Op::MUL;
    }
    return p1;
}

part parse_mul() {
    char ch = next_char();
    if (ch == '(') {
        ++pos;
        parse_expr();
        assert(next_char() == ')');
        ++pos;
        return { Op::NONE, false };
    } else {
        int pos2 = pos;
        for (; line[pos2] >= 'a' && line[pos2] <= 'z' || line[pos2] >= 'A' && line[pos2] <= 'Z' || line[pos2] >= '0' && line[pos2] <= '9'; ++pos2);
        string name = line.substr(pos, pos2 - pos); pos = pos2;
        if (defs.count(name)) {
            if (defs[name].unsafe) unsafe = true;
            return { defs[name].op, true };
        }
        else return { Op::NONE, false };
    }
}

int main() {
    UNTIE();
    int n; cin >> n;
    RESET_IS(cin);

    REP(i, 0, n) {
        getline(cin, line); pos = line.find("define") + 6; next_char();
        int pos2 = pos;
        for (; line[pos2] >= 'a' && line[pos2] <= 'z' || line[pos2] >= 'A' && line[pos2] <= 'Z'; ++pos2);
        string name = line.substr(pos, pos2 - pos); pos = pos2;
        unsafe = false;
        Op op = parse_expr().op;
        defs[name] = { op, unsafe };
    }

    unsafe = false;
    getline(cin, line); pos = 0;
    parse_expr();
    cout << (unsafe ? "Suspicious" : "OK") << endl;
}
