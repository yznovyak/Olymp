#include <cstdio>
#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

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

vector<int64> tidy_numbers;

void gen(int64 num, int len) {
  tidy_numbers.push_back(num);
  if (len == 18)
    return;
  for (int i = num % 10; i <= 9; i++)
    gen(num * 10 + i, len+1);
}

struct Test {
  int64 N, ans;

  void read() {
    cin >> N;
  }

  void solve() {
    auto ptr = lower_bound(tidy_numbers.begin(), tidy_numbers.end(), N);
    if (ptr < tidy_numbers.end() && *ptr == N) {
      ans = N;
      return;
    }
    --ptr;
    ans = *ptr;
  }

  void print(int num_test) {
    printf("Case #%d: %lld\n", num_test, ans);
  }
};

int main() {
  // freopen("input.txt", "rt", stdin);
  freopen("B-large.in", "rt", stdin);
  freopen("B-large.out2", "wt", stdout);

  for (int i = 1; i <= 9; i++)
    gen(i, 1);
  sort(tidy_numbers.begin(), tidy_numbers.end());

  int T;
  scanf("%d", &T);
  vector<Test> tests(T);
  for (int i = 0; i < T; i++)
    tests[i].read();

  #pragma omp parallel for
  for (int i = 0; i < T; i++) {
    clock_t start = clock();
    tests[i].solve();
    fprintf(stderr, "Solved test %d in %.2fs\n", i+1, float(clock() - start) / CLOCKS_PER_SEC);
  }

  for (int i = 0; i < T; i++)
    tests[i].print(i+1);

  return 0;
}
