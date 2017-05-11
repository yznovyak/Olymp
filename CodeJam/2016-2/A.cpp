#include <cstdio>
#include <ctime>
#include <iostream>
#include <vector>
#include <map>

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

map<pair<char, int>, string> correct;

struct Test {
  int N, P, R, S;
  string ans;

  void read() {
    scanf("%d %d %d %d", &N, &R, &P, &S);
  }

  bool is_ok(string s) {
    return
      count(s.begin(), s.end(), 'P') == P &&
      count(s.begin(), s.end(), 'R') == R &&
      count(s.begin(), s.end(), 'S') == S;
  }

  void solve() {
    ans = "IMPOSSIBLE";
    for (char ch : string("PRS"))
      if (is_ok(correct[{ch, N}])) {
        ans = correct[{ch, N}];
        break;
      }

    // string stupid = string(P, 'P') + string(R, 'R') + string(S, 'S');
    // do {
    //   string s = stupid;
    //   bool bad = false;
    //   while (s.size() > 1) {
    //     string s2 = "";
    //     for (size_t i = 0; i < s.size(); i += 2) {
    //       if (s[i] == s[i+1]) {
    //         bad = true;
    //         break;
    //       }
    //       if (s[i] == 'P' && s[i+1] == 'R') s2 += 'P';
    //       if (s[i] == 'P' && s[i+1] == 'S') s2 += 'S';
    //       if (s[i] == 'R' && s[i+1] == 'P') s2 += 'P';
    //       if (s[i] == 'R' && s[i+1] == 'S') s2 += 'R';
    //       if (s[i] == 'S' && s[i+1] == 'P') s2 += 'S';
    //       if (s[i] == 'S' && s[i+1] == 'R') s2 += 'R';
    //     }
    //     if (bad) break;
    //     s = s2;
    //   }
    //   if (!bad) {
    //     // if (ans != stupid)
    //     //   cout << "Hmmm " << ans << " " << stupid << endl;
    //     ans = stupid;
    //     break;
    //   }
    // } while (next_permutation(stupid.begin(), stupid.end()));
  }

  void print(int num_test) {
    printf("Case #%d: %s\n", num_test, ans.c_str());
  }
};

string cc(string a, string b) {
  if (a > b)
    swap(a, b);
  return a + b;
}

int main() {
  // freopen("input.txt", "rt", stdin);
  freopen("A-large-practice.in", "rt", stdin);
  freopen("A-large-practice.out", "wt", stdout);

  correct[{'P', 0}] = "P";
  correct[{'R', 0}] = "R";
  correct[{'S', 0}] = "S";
  for (int n = 1; n <= 12; n++) {
    correct[{'P', n}] = cc(correct[{'P', n-1}], correct[{'R', n-1}]);
    correct[{'R', n}] = cc(correct[{'R', n-1}], correct[{'S', n-1}]);
    correct[{'S', n}] = cc(correct[{'S', n-1}], correct[{'P', n-1}]);
  }

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
