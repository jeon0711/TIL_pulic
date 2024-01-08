/*
정점을 분할해서 a-b가 1보다 크면 b 내부에서의 연결을
만들어(비순환경로로,단일경로) a->b0...bk로 나누면 연결되어있는지를 표시하기
때문에 행렬 거듭제곱으로 T번만에 도착할수 있는 경우의수를 구하면 된다.
거듭제곱으로 구하지 않으면 T가 너무 커짐. 간선크기는 5이하인점.이 힌트였음.
행렬연산으로 구할수 있도록 변형했어야했고, 그래프에서 노드 합칠수 있다면
분할할수도 있다는거. 있는 도구를 사용할수 있도록. 애초에 풀수있는건 d<=5여서.
*/
#include <bitset>
#include <climits>
#include <cstdio>
#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#define div 1000003
using namespace std;
int N, S, E;
long long T;  // 이게 딱 10^10까지.
map<long long, int> resultarr[10][10];
int input_metrix[10][10]{
    0,
};
int answer;
class metrix {
 public:
  long long min;
  long long max;
  int count;
  int range;
  long long rangearr[10][10][2];
  map<long long, int>
      arr[10][10];  // a,b [0]는 해당부분 최소,100000은 최대값을 넣는다.
  // 0에는 min,max넣어두면됨.어차피 연산하려면 다 돌아봐야하니까  차이는 없다.
  // 이전최대값 *10이 배열범위를 넘으면 *10배 확장.
  metrix() : min(INT_MAX), max(0), count(0), range(0) {
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        rangearr[i][j][0] = INT_MAX;
        rangearr[i][j][1] = 0;
      }
    }
  }
  void print_map() {
    for (int i = 0; i < N; i++) {
      cout << i << " ";
      for (int j = 0; j < N; j++) {
        cout << j << endl;
        for (map<long long, int>::iterator it = arr[i][j].begin();
             it != arr[i][j].end(); it++) {
          cout << it->first << " " << it->second << endl;
        }
      }
      cout << endl;
    }
  }
  void operator=(metrix other) {
    range = other.range;
    min = T;
    max = 0;
    count = other.count + 1;
    long long temp, temp1;
    for (int i = 0; i < range; i++) {
      for (int k = 0; k < range; k++) {
        for (int j = 0; j < range; j++) {
          if (other.rangearr[i][j][1] > 0 && other.rangearr[j][k][1] > 0) {
            // i,j, j,k검사해 i,k만든다.임시로 트리만들어서 넣고, 거기서
            // 연산끝낸뒤에 다 넣는다.
            for (map<long long, int>::iterator it = other.arr[i][j].begin();
                 it != other.arr[i][j].end(); it++) {
              for (map<long long, int>::iterator it2 = other.arr[j][k].begin();
                   it2 != other.arr[j][k].end(); it2++) {
                temp = (it->first) + (it2->first);
                temp1 = (it->second) * (it2->second);
                temp1 %= div;
                if (temp < T) {
                  if (rangearr[i][k][0] > temp) {
                    rangearr[i][k][0] = temp;
                  }
                  if (rangearr[i][k][1] < temp) {
                    rangearr[i][k][1] = temp;
                  }
                  if (min > temp) {
                    min = temp;
                  }
                  if (max < temp) {
                    max = temp;
                  }
                  if (arr[i][k].find(temp) != arr[i][k].end()) {
                    arr[i][k][temp] += temp1;
                    arr[i][k][temp] %= div;
                  } else {
                    arr[i][k][temp] = temp1;
                  }
                } else if (temp == T && i == S && k == E) {
                  answer += temp1;
                  answer %= div;
                }
              }
            }
          }
        }
        for (map<long long, int>::iterator it = arr[i][k].begin();
             it != arr[i][k].end(); it++) {
          if (resultarr[i][k].find(it->first) != resultarr[i][k].end()) {
            resultarr[i][k][it->first] += it->second;
          } else {
            resultarr[i][k][it->first] = it->second;
          }
        }
      }
    }
  }
};

// 새로만든게 위에서 없으면 여기넣고,위에는 더한다.
// fmetrix[a][b][0].nodenum은 fmetrix[a][b]의 idx, 해당값 이하로만 돌린다.

void swapmetrix(int x, int y) {
  int temp = 0;
  for (int i = 0; i < N; i++) {
    temp = input_metrix[x][i];
    input_metrix[x][i] = input_metrix[y][i];
    input_metrix[y][i] = temp;
  }
  temp = 0;
  for (int i = 0; i < N; i++) {
    temp = input_metrix[i][x];
    input_metrix[i][x] = input_metrix[i][y];
    input_metrix[i][y] = temp;
  }
  input_metrix[x][x] = 0;
  input_metrix[y][y] = 0;
}
int main(void) {
  answer = 0;
  string str0;
  metrix matrixarr[10];
  scanf("%d %d %d %lld", &N, &S, &E, &T);
  S--;
  E--;

  for (int i = 0; i < N; i++) {
    cin >> str0;
    for (int j = 0; j < N; j++) {
      input_metrix[i][j] = str0[j] - '0';
    }
  }

  if (S != E) {
    if (E == 0 && S == N - 1) {
      swapmetrix(E, S);

    } else if (S == N - 1) {
      swapmetrix(0, N - 1);
      swapmetrix(E, N - 1);
    } else if (E == 0) {
      swapmetrix(0, N - 1);
      swapmetrix(S, 0);
    } else {
      swapmetrix(E, N - 1);
      swapmetrix(S, 0);
    }
    S = 0;
    E = N - 1;
  }
  matrixarr[0].count = 0;
  matrixarr[0].min = T;
  matrixarr[0].max = 0;
  matrixarr[0].range = N;
  for (int i = S; i <= E; i++) {
    for (int j = S; j <= E; j++) {
      if (input_metrix[i][j] > 0) {
        matrixarr[0].arr[i][j][input_metrix[i][j]] = 1;
        matrixarr[0].rangearr[i][j][0] = input_metrix[i][j];
        matrixarr[0].rangearr[i][j][1] = input_metrix[i][j];
        resultarr[i][j][input_metrix[i][j]] = 1;
        if (input_metrix[i][j] > matrixarr[0].max) {
          matrixarr[0].max = input_metrix[i][j];
        }
        if (input_metrix[i][j] < matrixarr[0].min) {
          matrixarr[0].min = input_metrix[i][j];
        }
      }
    }
  }
  int i, d = 0;
  while (matrixarr[i].max > 0)  // T가 나왔다면,5~1*2^k-1사이값.
  {
    i++;
    matrixarr[i] = matrixarr[i - 1];
    if (answer > 0 && d == 0) {
      d = i - 1;
    }
  }  // 1,..1111 10000,
  i--;
  int k = i - 1;
  while (i > 0) {
    k = i - 1;  // 최초로 T값 넘은 i-1에서 위로가며 더한뒤, 해당 i부터내려가면서
                // 하나씩 다 더한다. T의크기별로 정렬해둬야한다.lowerbound로
                // 바로나오게
    // 더한값이 T넘으면 버리고, 기존값 보존하면서 더하면 전체경우의수 나옴.
    // 단 s에서 나가는 경로만 보면됨. 그리고 s-a해당경로와 T의차가 a-e경로의
    // 누적값들중의 최대값*2보다 낮으면 버린다(고려하는 matrix가 앞으로 더할
    // 값들중 최고값이도록,최대값은 기존것들중 최대값으로 유지한다),
    while (k >= 0) {
      if (matrixarr[i].max + matrixarr[k].max >= T) {
        for (int j = S; j <= E; j++) {
          if (matrixarr[i].rangearr[S][j][1] + matrixarr[k].rangearr[j][E][1] >=
              T) {
            for (map<long long, int>::iterator it =
                     matrixarr[i].arr[S][j].begin();
                 it != matrixarr[i].arr[S][j].end(); it++) {
              for (map<long long, int>::iterator it1 =
                       matrixarr[k].arr[j][E].begin();
                   it1 != matrixarr[k].arr[j][E].end(); it1++) {
                if (it1->first + it->first == T) {
                  answer += (it1->second) * it->second;
                  answer %= div;
                }
              }
            }
          }
        }
      }
      k--;
    }
    i--;
  }
  cout << answer << endl;
}
