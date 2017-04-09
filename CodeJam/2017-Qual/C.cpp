#include <cstdio>
#include <ctime>
#include <iostream>
#include <ostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

typedef long long int64;

#define DPRINT(x) cout << #x << " = " << x << endl;

template <class T1, class T2>
ostream& operator <<(ostream& os, const pair<T1, T2>& v);

template <typename T, typename U>
ostream& operator <<(ostream& os, const map<T, U>& v) {
    os << "[";
    for (auto ii = v.begin(); ii != v.end(); ++ii) {
        if (ii != v.begin())
          os << " ";
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
  int64 N, K;
  int64 ans_ls = -1, ans_rs = -1;

  void read() {
    cin >> N >> K;
  }

  void solve() {
    map<int64, int64> Q;
    Q[N] = 1;
    while (true) {
      // printf("K=%lld  ", K);
      // DPRINT(Q);
      auto pii = Q.end();
      --pii;
      int64 len = pii->first, cnt = pii->second;
      Q.erase(pii);

      // printf("popped %lld count %lld\n", len, cnt);

      int64 ls = len / 2;
      int64 rs = len - 1 - ls;
      // printf(" ls=%lld rs=%lld\n", ls, rs);
      // cout << endl;

      if (K <= cnt) {
        ans_ls = ls;
        ans_rs = rs;
        break;
      } else {
        K -= cnt;
        Q[ls] += cnt;
        Q[rs] += cnt;
      }
    }
  }

  void print(int num_test) {
    printf("Case #%d: %lld %lld\n", num_test, ans_ls, ans_rs);
  }
};


int main() {
  // freopen("input.txt", "rt", stdin);
  freopen("C-large.in", "rt", stdin);
  freopen("C-large.out", "wt", stdout);

  int T;
  scanf("%d", &T);
  vector<Test> tests(T);
  for (int i = 0; i < T; i++)
    tests[i].read();

  #pragma omp parallel for
  for (int i = 0; i < T; i++) {
    clock_t start = clock();
    tests[i].solve();
    fprintf(stderr, "Solved test %d in %.3fs\n", i+1, float(clock() - start) / CLOCKS_PER_SEC);
  }

  for (int i = 0; i < T; i++)
    tests[i].print(i+1);

  return 0;
}
