#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <iostream>
#include <queue>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

#define REP(i,n) for (int i(0), _n(n); i < _n; i++)

#define ALL(c) (c).begin(), (c).end()
#define SORT(c) sort(ALL(c))
#define REVERSE(c) reverse(ALL(c))
#define UNIQUE(c) SORT(c),(c).resize(unique(ALL(c))-(c).begin())

#define INF 1000000000
#define X first
#define Y second
#define pb push_back
#define sz size()

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PII;
typedef vector<PII> VPII;

#define DPRINT(x) cout << #x << " = " << x << endl;

template <class T1, class T2>
ostream& operator <<(ostream& os, const pair<T1, T2>& v);

template <class T>
ostream& operator <<(ostream& os, const vector<T>& v) {
    os << "[";
    for (typename vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if (ii != v.begin()) os << " ";
        os << *ii;
    }
    os << "]";
    return os;
}

template <class T1, class T2>
ostream& operator <<(ostream& os, const pair<T1, T2>& v) {
    os << "(" << v.first << " " << v.second << ")";
    return os;
}

struct Test {
  int ans;
  string str;
  int N, K;

  void read() {
    cin >> str >> K;
    N = str.size();
  }

  void solve() {
    ans = 0;
    for (int i = 0; i < N; i++) {
      if (str[i] == '-') {
        ans++;
        for (int j = 0; j < K; j++)
          if (i+j >= N) {
            ans = -1;
            return;
          } else
            str[i+j] ^= '+' ^ '-';
      }
    }
  }

  void print(int num_test) {
    printf("Case #%d: ", num_test);
    if (ans >= 0)
      printf("%d\n", ans); else
      printf("IMPOSSIBLE\n");
  }
};

int main() {
  // freopen("input.txt", "rt", stdin);
  freopen("A-large.in", "rt", stdin);
  freopen("A-large.out", "wt", stdout);

  int T;
  scanf("%d", &T);
  vector<Test> tests(T);
  for (int i = 0; i < T; i++)
    tests[i].read();

  #pragma omp parallel for
  for (int i = 0; i < T; i++) {
    clock_t t0 = clock();
    tests[i].solve();
    fprintf(stderr, "Solved test %3d in %.2fs\n", i+1, float(clock() - t0) / CLOCKS_PER_SEC);
  }

  for (int i = 0; i < T; i++)
    tests[i].print(i+1);

  return 0;
}
