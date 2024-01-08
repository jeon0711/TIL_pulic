#include <bitset>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
int main(void) {
  int A, B, C, idx, digitidx, temp;
  long long answer = 1;
  long long arr[32]{
      0,
  };
  bitset<32> multarr;
  // arr[i]=a^(2^i)%C
  idx = 0;
  digitidx = 0;
  scanf("%d %d %d", &A, &B, &C);
  arr[0] = A % C;
  if (arr[0]) {
    multarr = B;
    while (idx < 31) {
      arr[idx + 1] = (arr[idx] * arr[idx]) % C;
      idx++;
    }
    for (int i = 0; i < 31; i++) {
      if (multarr[i]) {
        answer *= arr[i];
        answer %= C;
      }
    }
    cout << answer << endl;
  } else {
    cout << 0 << endl;
  }
}