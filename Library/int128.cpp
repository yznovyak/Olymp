#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

typedef __int128_t int128;
typedef __uint128_t uint128;

string to_string(uint128 value) {
  if (value == 0) return "0";
  string rev = "";
  while (value > 0) {
    rev += '0' + (value % 10);
    value /= 10;
  }
  reverse(rev.begin(), rev.end());
  return rev;
}

string to_string(int128 value) {
  if (value < 0)
    return "-" + to_string(uint128(-value));
  return to_string(uint128(value));
}

int main() {
  int128 tmp1;
  tmp1 = 111111111;
  tmp1 *= tmp1;
  tmp1 *= -1;
  cout << to_string(tmp1) << endl;

  uint128 tmp2 = 1;
  tmp2 <<= 127;
  cout << to_string(tmp2) << endl;

  return 0;
}
