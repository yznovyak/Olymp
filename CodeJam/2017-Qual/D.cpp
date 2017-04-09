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
  int N, K;
  vector<vector<char>> grid, original_grid;

  void read() {
    cin >> N >> K;
    grid.assign(N, vector<char>(N, '.'));
    for (int i = 0; i < K; i++) {
      char ch;
      int r, c;
      cin >> ch >> r >> c;
      if (ch != 'o' && ch != 'x' && ch != '+') {
        fprintf(stderr, "WTF?! read char '%c'\n", ch);
        exit(1);
      }
      grid[r-1][c-1] = ch;
    }
  }

  void print_grid() {
    for (int r = 0; r < N; r++) {
      for (int c = 0; c < N; c++)
        putchar(grid[r][c]);
      puts("");
    }
  }

  void solve() {
    original_grid = grid;

    if (N == 1) {
      grid[0][0] = 'o';
      return;
    }

    int pos = 0;
    for (int c = 1; c < N; c++)
      if (grid[0][c] != '.' && grid[0][c] != '+') {
        pos = c;
        break;
      }

    grid[0].assign(N, '+');
    grid[0][pos] = 'o';
    grid[N-1].assign(N, '+');
    grid[N-1][0] = grid[N-1][N-1] = '.';

    for (int r = N-1, c = 0; r > 0; r--, c = (c+1) % N) {
      if (c == pos) {
        if (r == N-1)
          c = N-1; else
          c = (c+1) % N;
      }
      grid[r][c] = 'x';
    }

    // print_grid();
    // puts("");
  }

  void print(int num_test) {
    int score = 0, placements = 0;
    for (int r = 0; r < N; r++) {
      for (int c = 0; c < N; c++) {
        if (original_grid[r][c] != grid[r][c])
          placements++;
        if (grid[r][c] == 'o')
          score += 2;
        if (grid[r][c] == '+' || grid[r][c] == 'x')
          score++;
      }
    }

    int max_score = 3*N - 2;
    if (N == 1) max_score = 2;

    if (score != max_score) {
      fprintf(stderr, "hmmm case=%d N=%d max_score=%d score=%d\n", num_test, N, max_score, score);
    }

    printf("Case #%d: %d %d\n", num_test, score, placements);
    for (int r = 0; r < N; r++) {
      for (int c = 0; c < N; c++) {
        if (original_grid[r][c] != grid[r][c]) {
          printf("%c %d %d\n", grid[r][c], r+1, c+1);
        }
      }
    }
  }
};


int main() {
  // freopen("input.txt", "rt", stdin);
  freopen("D-small-attempt2.in", "rt", stdin);
  freopen("D-small-attempt2.out", "wt", stdout);

  int T;
  scanf("%d", &T);
  vector<Test> tests(T);
  for (int i = 0; i < T; i++)
    tests[i].read();

  #pragma omp parallel for
  for (int i = 0; i < T; i++) {
    clock_t start = clock();
    tests[i].solve();
    // fprintf(stderr, "Solved test %d in %.3fs\n", i+1, float(clock() - start) / CLOCKS_PER_SEC);
  }

  for (int i = 0; i < T; i++)
    tests[i].print(i+1);

  return 0;
}
