#include <cstdio>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

typedef long long int64;

const int kMaxN = 128;
const char str[] = {'+', 'x', 'o'};

int N;
char grid[kMaxN][kMaxN];
int max_score;

bool check(int r, int c, char has_to) {
  if (r < 0 || r >= N || c < 0 || c >= N) return true;
  if (grid[r][c] == '.') return true;
  return grid[r][c] == has_to;
}

bool is_ok(int r, int c) {
  if (grid[r][c] != '+') {
    for (int i = -N; i <= N; i++) {
      if (i == 0) continue;
      if (!check(r+i, c, '+')) return false;
      if (!check(r, c+i, '+')) return false;
    }
  }
  if (grid[r][c] != 'x') {
    for (int i = -N; i <= N; i++) {
      if (i == 0) continue;
      if (!check(r+i, c+i, 'x')) return false;
      if (!check(r+i, c-i, 'x')) return false;
    }
  }
  return true;
}

void print_grid() {
  for (int r = 0; r < N; r++)
    puts(grid[r]);
}

int64 cnt;

void gen(int pos, int score) {
  cnt++;
  if (score > max_score) {
    max_score = score;
    printf("\nnew max = %d\n", max_score);
    print_grid();
  }

  while (pos < N*N) {
    int r = pos / N, c = pos % N;

    if (grid[r][c] != '.') {
      gen(pos+1, score);

      if (grid[r][c] != 'o') {
        char tmp = grid[r][c];
        grid[r][c] = 'o';
        if (is_ok(r, c))
          gen(pos+1, score+1);
        grid[r][c] = tmp;
      }
    } else {
      for (int i = 0; i < 3; i++) {
        grid[r][c] = str[i];
        if (is_ok(r, c))
          gen(pos+1, score + (i < 2 ? 1 : 2));
        grid[r][c] = '.';
      }
    }

    pos++;
  }
}

int main() {
  N = 6;
  for (int r = 0; r < N; r++) {
    for (int c = 0; c < N; c++)
      grid[r][c] = '.';
    grid[r][N] = 0;
  }

  // grid[0][0] = '+';
  // grid[0][1] = '+';
  // grid[0][2] = '+';
  // grid[0][3] = '+';
  // grid[0][4] = 'o';

  cnt = 0;
  max_score = -1;
  gen(0, 0);
  printf("\n count = %lld\n", cnt);
}
