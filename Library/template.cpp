#include <cstdio>
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>

using namespace std;

typedef int64_t int64;

// BEGIN CUT
#define DBG(x) #x << " = " << x
#define REP(i,n) for (int i = 0; i < (n); i++)
#define REPV(i,v) for (size_t i = 0; i < v.size(); i++)
#define ALL(x) (x).begin(), (x).end()
#define SORT(x) sort(ALL(x))
#define UNIQUE(x) SORT(x), x.resize(unique(ALL(x)) - x.begin())
#define pb push_back

template <class T1, class T2>
ostream& operator <<(ostream& os, const pair<T1, T2>& v) {
  os << "(" << v.first << " " << v.second << ")";
  return os;
}

template <typename T,
          typename U = typename T::value_type,
          typename = typename enable_if<!is_same<T, string>::value>::type>
ostream& operator<<(ostream& os, const T& v) {
  os << '[';
  for (const auto& it : v)
    os << it << " ";
  if (!v.empty()) os << "\b";
  os << "]";
  return os;
}
// END CUT

int main() {
#ifdef LocalHost
  freopen("input.txt", "rt", stdin);
#endif
  cin.tie(0);
  cout.tie(0);
  ios_base::sync_with_stdio(0);

  vector<int> vec = {1,2,3, 1,2,10};
  vector<pair<int, int>> vec2 = {{1,2}, {2,3}};
  set<int> s = {10,20,30,40,50};
  map<int, int> m = {{1,2}, {3,4}};
  unordered_set<int> s2 = {10,20,30,40,50};
  unordered_map<int, int> m2 = {{1,2}, {3,4}};

  cout << DBG(vec) << endl;
  cout << DBG(vec2) << endl;
  cout << DBG(s) << endl;
  cout << DBG(m) << endl;
  cout << DBG(s2) << endl;
  cout << DBG(m2) << endl;

  UNIQUE(vec);
  cout << DBG(vec) << endl;

  return 0;
}
