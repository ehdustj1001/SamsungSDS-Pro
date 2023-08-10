//2023.8.9
#include <iostream>
#include <vector>
using namespace std;

int n,m;
int num[100001];
int minTree[400000] = {0,};
int maxTree[400000] = {0,};

void init(int node, int start, int end) {

    if(start == end) {
        minTree[node] = maxTree[node] = num[start];
        return;
    }

    int mid = (start+end)/2;
    init(node*2,start,mid);
    init(node*2+1,mid+1,end);

    minTree[node] = min(minTree[node*2],minTree[node*2+1]);
    maxTree[node] = max(maxTree[node*2],maxTree[node*2+1]);
}

pair<int,int> find(int node, int start, int end, int left, int right) {
    //1. [left, right]와 [start, end]가 겹치지 않는 경우
    if(end < left || start > right) return make_pair(INT32_MAX,0);

    //2. [left, right]가 [start, end]를 포함하는 경우
    else if(left <= start && right >= end) return make_pair(minTree[node],maxTree[node]);
    //3. [start, end]가  [left, right]를 포함하는 경우 ,  [start, end] [left, right]와 겹치는 부분이 있는 경우
    else {
        int mid = (start+end)/2;
        pair<int,int> left_result = find(node*2,start,mid,left,right);
        pair<int,int> right_result = find(node*2+1,mid+1,end,left,right);
        return make_pair(min(left_result.first, right_result.first),max(left_result.second, right_result.second));
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n >> m;

    for(int i=1;i<=n;i++) {
        cin >> num[i];
    }

    init(1,1,n);

    while(m--) {
        int a,b;
        cin >> a >> b;
        pair<int,int> ans = find(1,1,n,a,b);
        cout << ans.first << " " << ans.second << "\n";
    }

    return 0;

}
