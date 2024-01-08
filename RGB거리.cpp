#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
int N;
int paintcost[1000][3];
int dp[1000][3];//[k][j]면 인덱스 k를 j번째 color 선택시의 0~k까지 최소값.
int main(void)
{
cin>>N;
for(int i=0;i<N;i++)
{
    for(int j=0;j<3;j++)
    {
        cin>>paintcost[i][j];
    }
}
dp[0][0]=paintcost[0][0];
dp[0][1]=paintcost[0][1];
dp[0][2]=paintcost[0][2];
for(int i=1;i<N;i++)
{
    for(int j=0;j<3;j++)
    {
            dp[i][j]=min(dp[i-1][(j+1)%3],dp[i-1][(j+2)%3]);
            dp[i][j]+=paintcost[i][j];
    }
}
int an=min(dp[N-1][0],dp[N-1][1]);
an=min(an,dp[N-1][2]);
cout<<an<<endl;
return 0;
} 
