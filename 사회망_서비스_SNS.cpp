//친구의 친구는 안된다는거. 짝수레벨 전체합.
//A가 얼리어답터가 아니면 A의 친구중 하나는 얼리어답터이다.
//얼리어답터가 아닌친구들만 있으면 안되는거지.
/*서브트리에 대해 구하고 합칠때 해결하자. 합칠때 둘다 얼리어답터면
하나 빼고 봄.child가 하나인 점에서 시작. 아닌걸로 두고 푼다.
반드시 리프있다. 트리를 어떻게 구조화하든 최소는 짝,홀수레벨 얼리어답터화.
왜냐면 어떤트리만들면 새로운 루트로 구조화해도 거기에 속해있던 노드를 빼면, 부모를 자식으로, 동레벨은 다시 자식의 자식,
꼴로 구조화되서 그럼. 순환경로 없으므로 부모 혹은 자식노드중 하나는 얼리어답터여야하고
부모이면 동레벨은 얼리어답터일 필요가 없음.
아니 각 서브트리에 대해 구하고(dps로 하자),그게 최소이면
DFA로 구조화가능.노드들의 상태집합을 각 q1,,,qn이라하며
루트부터 내려가야. 루트가 얼리어답터인경우,아닌경우나누어 찾는다.
연결된 부분 제외하면 남은 서브트리에 대해 서브트리는 안연결된 부분을 루트로 가지므로
r-b트리에서 r을 최소로하는경우다.
가장많이 연결된 노드를 루트로 선택 안하면
리프노드들에 대해 연결된 부분은 얼리어답터여야하고,연결된부분 지워서 생기는 트리에 대해 다시하고...
*/
#include<iostream>
#include <vector>
using namespace std;
class node
{
    public:
    bool isLeaf;
    bool isSelected;
    vector<int> children;
    node(){}
};
vector<node> arr;
vector<bool> selected;
int main(void)
{
    int N,q1,q2,rt;
    cin>>N;
    node temp;
    arr.assign(N,temp);
    selected.assign(N,false);
    for(int i=1;i<N;i++)
    {
        cin>>q1>>q2;
        arr[q1].children.push_back(q2);
        if(arr[q1].children.size()==1)
        {
            arr[q1].isLeaf=true;
        }
        else
        {
            arr[q1].isLeaf=false;
        }
        arr[q2].children.push_back(q1);
        if(arr[q2].children.size()==1)
        {
            arr[q2].isLeaf=true;
        }
        else
        {
            arr[q2].isLeaf=false;
        }
    }
}