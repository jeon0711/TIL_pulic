// 하나의 직선의 연장선상에는 아무 끝점도 없다.
/*최악은 모두 겹치는경우. 한점에서 만나지만 않으면 되니까 한 막대가
여럿과 겹칠수 있다.두점 a,b사이 a(1-c)+b*c(c<0)이 내부점.
구역별로 나누고, 구역에서 겹치면,
*/
#include <iostream>
#include <vector>
#define normal 0
#define aldeleted -1
using namespace std;
// 겹치는 것들만 남긴다.
// 언제나 한개만 겹치는 애들은 제거하면 된다. 만약 두개이상만 남으면,
/* 3개가 다 겹치면 경우의 수는 3개, 막대가 a,b,c일때 a를 제거하고 b,c와 겹치는
모든 막대제거 혹은 b,...로 3가지.셋다 불가능하면 -1리턴하고, 가능한게 있으면
계속 진행.100*100에서 10*10, 10*10에서 1로 해상도 높여간다.
*/
int N;
class stick {
 public:
  pair<int, int> first;
  pair<int, int> second;
  double yvec;
  int sticknum;
  vector<int> int_arr;
};
class student {
 public:
  stick stickarr[3];
  int stickstatus[3];
  int leftstick;  // 상태해소되야하는 자신의 스틱개수
  pair<int, int> xlength;
  pair<int, int> ylength;
  bool deleteable;
};
student starr[1000];
bool is_duplicated_sub(int arrin, stick& instick, int j) {
  int x0, x1;
  double y[2][2];
  bool temp, rt, temp1;
  temp1 = false;
  for (int i = 0; i < j; i++) {
    x0 = max(starr[arrin].stickarr[i].first.first, instick.first.first);
    x1 = min(starr[arrin].stickarr[i].second.first, instick.second.first);
    if (x0 < x1)  // 같을수는 없으므로
    {
      y[0][0] = starr[arrin].stickarr[i].yvec *
                    (x0 - starr[arrin].stickarr[i].first.first) +
                starr[arrin].stickarr[i].first.second;
      y[1][0] =
          instick.yvec * (x0 - instick.first.first) + instick.first.second;
      y[0][1] = starr[arrin].stickarr[i].yvec *
                    (x1 - starr[arrin].stickarr[i].first.first) +
                starr[arrin].stickarr[i].first.second;
      y[1][1] =
          instick.yvec * (x1 - instick.first.first) + instick.first.second;
      if (y[0][0] < y[1][0]) {
        temp = true;
      } else {
        temp = false;
      }
      if (y[0][1] < y[1][1]) {
        rt = true;
      } else {
        rt = false;
      }
      if (!((temp && rt) || (!(temp || rt)))) {
        instick.int_arr.push_back(arrin * 3 + i);
        starr[arrin].stickarr[i].int_arr.push_back(instick.sticknum);
        if (starr[arrin].stickstatus[i] == 0) {
          starr[arrin].leftstick++;
        }
        starr[arrin].stickstatus[i]++;
        temp1 = true;
      }
    }
  }
  return temp1;
}
bool is_duplicated_stick(int arrin, stick& instick) {
  bool rt = false;
  bool temp = false;
  int y0, y1, x0, x1;
  double y[2][2];
  if (starr[arrin].xlength.first > instick.second.first ||
      starr[arrin].xlength.second < instick.second.first) {
    return rt;
  } else {
    if (instick.first.second < instick.second.second) {
      y0 = instick.first.second;
      y1 = instick.second.second;
    } else {
      y0 = instick.second.second;
      y1 = instick.first.second;
    }
    if (y0 > starr[arrin].ylength.second || y1 < starr[arrin].ylength.first) {
      return rt;
    } else {
      /*여기서 이제 체크 rt==true,rt받아서 이게 true이므로 해당
       * student.stickstatus변경*/
      return is_duplicated_sub(arrin, instick, 3);
    }
  }
}
bool delete_stick(int input) {}
int main(void) {
  vector<int> stack;
  vector<int> ansstack;
  int ansrt = 0;
  scanf("%d", &N);
  int x[2], y[2], temp;
  for (int i = 0; i < N; i++) {
    starr[i].xlength = make_pair(10000, -10000);
    starr[i].ylength = make_pair(10000, -10000);
    starr[i].deleteable = true;
    for (int j = 0; j < 3; j++) {
      scanf("%d %d %d %d", &x[0], &y[0], &x[1], &y[1]);
      if (x[0] > x[1]) {
        temp = x[0];
        x[0] = x[1];
        x[1] = temp;
        temp = y[0];
        y[0] = y[1];
        y[1] = temp;
      }
      starr[i].stickarr[j].first.first = x[0];
      starr[i].stickarr[j].first.second = y[0];
      starr[i].stickarr[j].second.first = x[1];
      starr[i].stickarr[j].second.second = y[1];
      starr[i].stickarr[j].yvec =
          ((double)(y[1] - y[0]) / (double)(x[1] - x[0]));
      starr[i].stickarr[j].sticknum = i * 3 + j;
      for (int k = 0; k < i; k++) {
        if (is_duplicated_stick(k, starr[i].stickarr[j])) {
          if (starr[i].stickstatus[j] == 0) {
            starr[i].leftstick++;
          }
          starr[i].stickstatus[j]++;
        }
      }
      if (is_duplicated_sub(i, starr[i].stickarr[j], j)) {
        if (starr[i].stickstatus[j] == 0) {
          starr[i].leftstick++;
        }
        starr[i].stickstatus[j]++;
      }
      if (starr[i].xlength.first > x[0]) {
        starr[i].xlength.first = x[0];
      }
      if (starr[i].xlength.second < x[1]) {
        starr[i].xlength.second = x[1];
      }
      if (starr[i].ylength.first > y[0]) {
        starr[i].ylength.first = y[0];
      }
      if (starr[i].ylength.second < y[1]) {
        starr[i].ylength.second = y[1];
      }
    }
  }
  for (int i = 0; i < N; i++) {
    if (starr[i].leftstick == 1) {
      stack.push_back(i);
    }
  }
  while (!stack.empty()) {
    int st0 = stack.back();
    int st1;
    stack.pop_back();
    if (starr[st0].leftstick) {
      if (starr[st0].deleteable) {
        starr[st0].deleteable = false;
        ansstack.push_back(st0);
        ansrt++;
        for (int i = 0; i < 3; i++) {
          if (starr[st0].stickstatus[i] > 0) {
            for (vector<int>::iterator it =
                     starr[st0].stickarr[i].int_arr.begin();
                 it < starr[st0].stickarr[i].int_arr.end(); it++) {
              if (starr[(*it) / 3].stickstatus[(*it) % 3]) {
                starr[(*it) / 3].stickstatus[(*it) % 3]--;
                if (starr[(*it) / 3].stickstatus[(*it) % 3] == 0) {
                  starr[(*it) / 3].leftstick--;
                  if (starr[(*it) / 3].leftstick == 1 &&
                      starr[(*it) / 3].deleteable) {
                    stack.push_back((*it) / 3);
                  } else {
                    ansrt = -1;
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  for (int i = 0; i < N; i++) {
    cout << starr[i].leftstick << endl;
  }
  cout << ansrt << endl;
}