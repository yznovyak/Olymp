#include <vector>
#include <cmath>
using namespace std;
typedef int64_t int64;

bool is_prime(int n) {
  if (n <= 1) return false;
  if (n % 2 == 0) return n == 2;

  for (int i = 3; i*i <= n; i += 2)
    if (n % i == 0)
      return false;
  return true;
}

int gcd(int a, int b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int64 extended_gcd(int64 a, int64 b, int64& x, int64& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }

  int64 x1, y1;
  int64 d = extended_gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a/b) * y1;
  return d;
}

int64 mod_inverse(int64 a, int64 p) {
  int64 x, y;
  extended_gcd(a, p, x, y);
  x %= p;
  if (x < p) x += p;
  return x;
}

vector<int> eratosphene_sieve(size_t n) {
  if (n <= 1) return vector<int>();
  vector<bool> is_prime(1 + n/2, true);
  vector<int> primes;
  size_t capacity = 1.2 * n / log(n);  // 1.2 is enough for n >= 1000
  primes.reserve(capacity);
  primes.push_back(2);
  for (size_t i = 3; i <= n; i += 2) {
    if (is_prime[i/2]) {
      primes.push_back(i);
      if (i*i <= n)
        for (size_t j = (i*3)/2; j < is_prime.size(); j += i)
          is_prime[j] = false;
    }
  }
  return primes;
}

vector<int> prime_factors(int n) {
  vector<int> res, primes = eratosphene_sieve((int) ceil(sqrt(n)));
  for (int p : primes) {
    if (n % p == 0) {
      res.push_back(p);
      while (n % p == 0)
        n /= p;
    }
  }
  if (n > 1)
    res.push_back(n);
  return res;
}

// returns vector of pairs <prime, power>.
vector<pair<int, int>> factorize(int n) {
  vector<int> primes = eratosphene_sieve((int) ceil(sqrt(n)));
  vector<pair<int,int>> res;
  for (int p : primes) {
    int k = 0;
    while (n % p == 0) {
      n /= p;
      k++;
    }
    if (k > 0)
      res.push_back({p, k});
  }
  if (n > 1)
    res.push_back({n,1});
  return res;
}

const int kMod = 1000000000 + 7;

vector<int64> compute_binomials(int N) {
  vector<int64> binomials(N+1);
  binomials[0] = 1 % kMod;
  for (int i = 1; i <= N; i++) {
    int64 k = ((N+1-i) * mod_inverse(i, kMod)) % kMod;
    binomials[i] = (binomials[i-1] * k) % kMod;
  }
  return binomials;
}

int mod_binom(int n, int k) {
  if (k < 0 || k > n) return 0;
  if (n-k < k) k = n-k;

  int64 num = 1, denom = 1;
  for (int i = 0; i < k; i++) {
    num = (num * (n-i)) % kMod;
    denom = (denom * (i+1)) % kMod;
  }
  return (num * mod_inverse(denom, kMod)) % kMod;
}
