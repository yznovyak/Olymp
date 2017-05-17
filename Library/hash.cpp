#include <unordered_set>

using namespace std;

void hash_combine(size_t& seed, size_t v) {
  seed ^= v + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename T1, typename T2>
struct PairHash {
  std::hash<T1> h1;
  std::hash<T2> h2;

  inline size_t operator()(const pair<T1, T2>& p) {
    size_t seed = 0;
    hash_combine(seed, h1(p.first));
    hash_combine(seed, h2(p.second));
    return seed;
  }
};

struct PiiHash {
  inline size_t operator()(const pair<int, int>& p) {
    size_t seed = p.first;
    hash_combine(seed, p.second);
    return seed;
  }
};

unordered_set<pair<int, int>, PiiHash> set_of_pii;

int main() {
  set_of_pii.insert({1,2});
  set_of_pii.insert({3,4});
  return 0;
}
