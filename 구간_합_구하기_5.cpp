#include <cstdio>
using namespace std;
int N, M;
int row[1024][1024]{
    0,
};
int all[1024][1024]{
    0,
};
int main(void) {
  int x[2], y[2], sum;
  scanf("%d %d", &N, &M);
  for (int i = 0; i < N; i++) {
    scanf("%d", &row[i][0]);
    if (i == 0) {
      all[i][0] = row[i][0];
    } else {
      all[i][0] = all[i - 1][0] + row[i][0];
    }
    for (int j = 1; j < N; j++) {
      scanf("%d", &row[i][j]);
      row[i][j] += row[i][j - 1];
      if (i == 0) {
        all[i][j] = row[i][j];
      } else {
        all[i][j] = all[i - 1][j] + row[i][j];
      }
    }
  }
  for (int i = 0; i < M; i++) {
    scanf("%d %d %d %d", &x[0], &y[0], &x[1], &y[1]);
    x[0]--;
    y[0]--;
    x[1]--;
    y[1]--;
    sum = all[x[1]][y[1]];
    if (x[0] > 0) {
      sum -= all[x[0] - 1][y[1]];
    }
    if (y[0] > 0) {
      sum -= all[x[1]][y[0] - 1];
    }
    if (x[0] > 0 && y[0] > 0) {
      sum += all[x[0] - 1][y[0] - 1];
    }
    printf("%d \n", sum);
  }
}