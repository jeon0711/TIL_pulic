#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int N, K, idx;
long long right, left;
string arr[15];
int remainderarr[15];
int remainderof10k[100];
// 10^각인덱스%mod K를 저장해놓는다.P에 인덱스 최대값저장. 자릿수%P로 구함.
// 각 집합의 mod K,remainder와 자릿수만 곱해서
// K는  100보다 작다. 순열의 임의선택이므로 중복되는 순열 존재가능.즉
// 중복고려할필요없다. *10,/k,1,3,2,6,4,5,1,10^k에 대해. 또 이 패턴은 K개 이하,
// 같은수면 같은방법반복 remainder에서 0이 되는 부분있으면 이후로는 다0.
// remainder arr에서 0이 되는부분. 전체는 n!, 0이되는 부분 전체를 발견했으면
// sum:(n-j)!/n!때로 구할수 있음.sum:(1/NC(n-j)인것) 그런 부분이 없으면, 다
// 돌려봐야하나?,부분문제로 나눠서. 우측부터 차례로 채워나간다. 우측에 있는
// 수들로 가능한 mod값들 표시. 가중치도 준다. 모든경우를 다 포함할때까지. 이때
// 모든경우 포함하기 위해  4개통합한다면 해당원소가 있는 3개짜리들 전부 더해야.
// 1234가 있으면 1234만들기 위해선 1 234 2 134 ...를 다 더한걸로
// 만들어야한다.(2^15)*1500
// 중복제거해야하는듯.아니면 틀릴리없음.부분집합 병합할때 전체와 같으면.(같은게
// 여러개면 여러부분에서 병합할때 걸림)
//
long long dp[((long long)1 << 15)][101]{
    0,
};  // 전자는 집합,2^k비트가 1이면 해당원소포함,해당집합의 나머지,리턴값은
    // 해당나머지값가지는경우수
int dplength[((long long)1 << 15)]{
    0,
};  // 집합의 크기(문자열길이총합)
// dplength가 새로 넣는 문자와 같으면 문자열 검사한다.
/*전체개수야 당연히 n!, 중복되는거 있으면 중복되는 문자열이 이미 포함된거에,
다시 이 중복된거 넣어서 만들어지는 문자열의 가지수를 구하고,(나머지와) 이걸
중복되는 부분들과 합쳐서 만들어지는거에서 뺀다. 더할때 무결성을 보장해야한다.
서로다른 경우의 수들로만 이루어진채 시작한다면.왼쪽으로 옮기거나,왼쪽에
더하거나해야함. 같은 string여럿 넣어서 만들어지는 경우를 빼야.중복가능한것들을
다 빼냈을때, 매번 중복가능해지는게 들어올때 매번하면된다. 3개면 3C2로 3개의
부분집합에서 2개짜리 들이 나타나지만(다른부분도같다) 셋을 합칠때 정리하며된다.
전체에서 N!-중복순열수,이다. 걍 중복가능한 부분 다 빼버리고 다 같은 스트링
취급해서 구하고, 2개 중복일때 구하고, 1개중복일때 구하고 해버리면 된다.
중복가능한 부분집합 모였을때 그 스트링 구성하는 경우의 수를 빼버리는거, 그러면
해당 스트링은 항상 1개이고 2개인경우, 3개인경우로 구하면됨(2개는 어떤 수들
대체할지 정하고써야.여럿은 다 대체하고.). 아예 다른순서로 더해지면 위치자체가
섞여버리므로 상관없다. 할수는 있는데 거지같내.
 */
bool divzero;
int set0[100]{
    0,
};
void set(long long input) {
  if (dp[input][K] == 0) {
    long long num = 1;
    long long temp = 0;
    int numidx = 0;
    while (num < input && numidx < N) {
      if (num & input) {
        temp = input - num;
        if (temp) {
          if (dp[temp][K] == 0) {
            set(temp);
          }
          if (dplength[input] == 0) {
            dplength[input] = dplength[temp] + dplength[num];
          }
          dp[input][K] += dp[temp][K];
          for (int i = 0; i < K; i++) {
            if (dp[temp][i] > 0) {
              if (divzero && (dplength[temp] >= idx)) {
                dp[input][i] += dp[temp][i];
              } else if (remainderarr[numidx] == 0) {
                dp[input][i] += dp[temp][i];
              } else {
                if (dplength[temp] > idx) {
                  dp[input]
                    [(i + (remainderarr[numidx] *
                           remainderof10k
                               [set0[remainderof10k[idx]] +
                                ((dplength[temp] - set0[remainderof10k[idx]]) %
                                 (idx + 1 - set0[remainderof10k[idx]]))])) %
                     K] += dp[temp][i];
                } else {
                  dp[input][(i + (remainderarr[numidx] *
                                  remainderof10k[dplength[temp]])) %
                            K] += dp[temp][i];
                }
              }
            }
          }
        } else {
          break;
        }
      }
      num = (num << 1);
      numidx++;
    }
  }
}
int rt_remainder(string input) {
  int rt = 0;
  for (string::iterator i = input.begin(); i < input.end(); i++) {
    rt = rt * 10;
    rt += (char)(*i) - '0';
    rt %= K;
  }
  return rt;
}
void rt(long long an, long long all) {
  long long left, right, anleft, anright;
  if (an == all) {
    printf("1/1");
  } else if (an > 0) {
    left = an;
    right = all;
    while (left && right) {
      if (left < right) {
        right %= left;
      } else {
        left %= right;
      }
    }
    if (left) {
      anleft = (long long)(an / left);
      anright = (long long)(all / left);
      cout << anleft << "/" << anright << endl;
    } else {
      anleft = (long long)(an / right);
      anright = (long long)(all / right);
      cout << anleft << "/" << anright << endl;
    }
  } else {
    printf("0/1");
  }
}
int main(void) {
  long long maintemp = 1;
  divzero = false;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
  }
  cin >> K;
  if (K == 1) {
    cout << "1/1" << endl;
  } else {
    for (int i = 0; i < N; i++) {
      remainderarr[i] = rt_remainder(arr[i]);
    }
    idx = 0;
    remainderof10k[idx] = 1;
    set0[1] = 1;
    idx++;
    while (idx < 100) {
      remainderof10k[idx] = (remainderof10k[idx - 1] * 10) % K;
      if (set0[remainderof10k[idx]] == 0) {
        set0[remainderof10k[idx]] =
            idx + 1;  // 역함수+1,set[k]=m이면 10^(m-1)%K=k
        if (remainderof10k[idx] == 0) {
          divzero = true;
          idx++;
          break;
        }
      } else {
        break;
      }
      idx++;
    }
    for (int i = 0; i < N; i++) {
      dplength[maintemp] = arr[i].length();
      dp[maintemp][K] = 1;
      dp[maintemp][remainderarr[i]] = 1;
      maintemp = (long long)maintemp << 1;
    }
    // idx에는 총개수넣는다.
    set(maintemp - 1);
    rt(dp[maintemp - 1][0], dp[maintemp - 1][K]);
  }
}