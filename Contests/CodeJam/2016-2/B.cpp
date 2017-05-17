#include <cstdio>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

typedef long long int64;

#define DPRINT(x) cerr << __LINE__ << ": " << #x << " = " << x << endl;

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
  int N, K;
  vector<double> prob;
  double ans;

  void read() {
    scanf("%d %d", &N, &K);
    prob.resize(N);
    for (int i = 0; i < N; i++)
      scanf("%lf", &prob[i]);
  }

  vector<double> calc_probs(const vector<double>& p) {
    vector<double> f(K+1, 0.0), next(K+1);
    f[0] = 1-p[0];
    f[1] = p[0];
    for (int i = 1; i < K; i++) {
      double p0 = p[i];
      next[0] = f[0] * (1-p0);
      for (int j = 1; j <= K; j++)
        next[j] = f[j-1] * p0 + f[j] * (1-p0);
      next.swap(f);
    }
    return f;
  }

  void solve() {
    sort(prob.begin(), prob.end());

    ans = -1;
    for (int t = 0; t <= K; t++) {
      vector<double> p_sub;
      for (int i = 0; i < t; i++)
        p_sub.push_back(prob[i]);
      for (int i = 0; i < K-t; i++)
        p_sub.push_back(prob[N-1-i]);
      vector<double> com_prob = calc_probs(p_sub);
      double seek = com_prob[K/2];
      if (seek > ans)
        ans = seek;
    }
  }

  void print(int num_test) {
    printf("Case #%d: %lf\n", num_test, ans);
  }
};


int main() {
  freopen("B-large-practice.in", "rt", stdin);
  freopen("B-large-practice.out", "wt", stdout);

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
