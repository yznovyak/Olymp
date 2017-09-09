#include <vector>

using namespace std;

// Range-Min-Query
struct RMQ {
  vector<vector<int>> data;

  void init(const vector<int>& v) {
    data.resize(32 - __builtin_clz(v.size()));
    data[0] = v;
    for (int p = 0; (1 << p) < data[p].size(); p++) {
      data[p+1].resize(data[p].size() - (1 << p));
      for (auto it1 = data[p].begin(), it2 = data[p].begin() + (1 << p), out = data[p+1].begin();
           out != data[p+1].end();
           ++it1, ++it2, ++out)
        *out = min(*it1, *it2);
    }
  }

  int query(int L, int R) {  // min of arr[L..R), L < R
    int p = 31 - __builtin_clz(R-L);
    return min(data[p][L], data[p][R - (1 << p)]);
  }
};
