#include <iostream>
using namespace std;
int arr[9]{
    0,
};
int main(void) {
  int N, M, idx, j;
  cin >> N >> M;
  idx = M;
  arr[0] = -1;
  while (true) {
    for (int i = 1; i < M; i++) {
      cout << (arr[i] + 1) << " ";
    }
    cout << (arr[M] + 1) << endl;
    arr[idx]++;
    if (arr[idx] == N) {
      idx--;
      while (arr[idx] == N - 1) {
        idx--;
      }
      if (idx == 0) {
        break;
      } else {
        arr[idx]++;
        for (int j = idx + 1; j <= M; j++) {
          arr[j] = arr[j - 1];
        }
        idx = M;
      }
    }
  }
}