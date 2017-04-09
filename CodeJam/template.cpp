#include <cstdio>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

typedef long long int64;

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
  void read() {
  }

  void solve() {
  }

  void print(int num_test) {
    printf("Case #%d: \n", num_test);
  }
};


int main() {
  freopen("input.txt", "rt", stdin);
  // freopen("A-small-attempt0.in", "rt", stdin);
  // freopen("A-small-attempt0.out", "wt", stdout);

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
