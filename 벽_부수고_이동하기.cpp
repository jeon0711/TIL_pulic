#include <deque>
#include <iostream>
#include <string>
#include <vector>
// 최단경로 구하는 방식대로 가면서 벽을 2개부셔야하면 그만탐색.
using namespace std;
int N, M;
int xvec[4]{1, 0, -1, 0};
int yvec[4]{0, 1, 0, -1};
class node {
 public:
  int x, y, z;
  node() : x(0), y(0), z(0) {}
  node(int inx, int iny, int inz) : x(inx), y(iny), z(inz) {}
};
int metrix[1000][1000][2]{
    0,
};
int input[1000][1000];
int main(void) {
  string inputstr;
  deque<node> nodevec;
  int xp, yp, zp;
  int answer = 1000 * 1000;
  int min;
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    cin >> inputstr;
    for (int j = 0; j < M; j++) {
      metrix[i][j][0] = answer;
      metrix[i][j][1] = answer;
      input[i][j] = inputstr[j] - '0';
    }
  }
  metrix[0][0][0] = 1;
  nodevec.push_back(node(0, 0, 0));
  while (!nodevec.empty()) {
    node temp = nodevec.front();
    nodevec.pop_front();
    for (int i = 0; i < 4; i++) {
      xp = temp.x + xvec[i];
      yp = temp.y + yvec[i];
      zp = temp.z;
      if ((xp < N) && (xp >= 0) && (yp >= 0) && (yp < M)) {
        if (input[xp][yp] == 0) {
          if ((metrix[xp][yp][0] > metrix[temp.x][temp.y][temp.z] + 1) &&
              (metrix[xp][yp][zp] > metrix[temp.x][temp.y][temp.z] + 1)) {
            metrix[xp][yp][zp] = metrix[temp.x][temp.y][temp.z] + 1;
            nodevec.push_back(node(xp, yp, zp));
          }
        } else if (zp == 0 && input[xp][yp] == 1) {
          if ((metrix[xp][yp][0] > metrix[temp.x][temp.y][temp.z] + 1) &&
              (metrix[xp][yp][1] > metrix[temp.x][temp.y][temp.z] + 1)) {
            metrix[xp][yp][1] = metrix[temp.x][temp.y][temp.z] + 1;
            nodevec.push_back(node(xp, yp, 1));
          }
        }
      }
    }
  }
  min = metrix[N - 1][M - 1][0];
  if (metrix[N - 1][M - 1][1] < min) {
    min = metrix[N - 1][M - 1][1];
  }
  if (min == answer) {
    cout << -1 << endl;
  } else {
    cout << min << endl;
  }
}