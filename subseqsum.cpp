#include <iostream>
#include <climits>
#include <vector>
#include <map>
using namespace std;
int N, K,P,L;
long long right,left;
string arr[15];
int remainder[100];//10^각인덱스%mod K를 저장해놓는다.P에 인덱스 최대값저장. 자릿수%P로 구함.
int remainderarr[15];//각 집합의 mod K,remainder와 자릿수만 곱해서 
//K는  100보다 작다. 순열의 임의선택이므로 중복되는 순열 존재가능.즉 중복고려할필요없다.
//*10,/k,1,3,2,6,4,5,1,10^k에 대해. 또 이 패턴은 K개 이하, 같은수면 같은방법반복
//remainder에서 0이 되는 부분있으면 이후로는 다0. remainder arr에서 0이 되는부분.
//전체는 n!, 0이되는 부분 전체를 발견했으면 sum:(n-j)!/n!때로 구할수 있음.sum:(1/NC(n-j)인것)
//그런 부분이 없으면, 다 돌려봐야하나?,
int rt_remainder(string input)
{}
int main(void)
{vector<int> vect;
	int idx=1;
cin>>N;
L=0;
P=0;
for(int i=0; i<N; i++)
{
	cin>>arr[i];
	L+=arr[i].length();
}
cin>>K;
remainder[0]=1;
while(idx)
{
	remainder[idx]=remainder[idx-1]*10;
	remainder[idx]%=K;
	if(remainder[idx]==0)
	{
		P=idx;
		break;
	}
	else if(remainder[idx]==1)
	{
		P=idx;
		idx=0;
		break;
	}
	idx++;
}
for(int i=0; i<N; i++)
{
remainderarr[i]=rt_remainder(arr[i]);
if(remainderarr[i]==0)
{
	vect.push_back(i);
}
}
if(idx)//0이되는 부분있음.
{
if(vect.empty())
{

}
else
{
	
}
}
else
{if(vect.empty())
{

}
else
{
	//아무것도없다.전체 다 돌아봐야.
}

}
}