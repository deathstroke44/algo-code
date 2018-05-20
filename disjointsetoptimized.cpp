#include<bits/stdc++.h>
using namespace std;
#define N 100005
typedef long long int int64;
int64 father[N],height[N];

void init() {
    for (int64 i = 0; i < N; ++i) {
        father[i] = i;
        height[i] = 0;
    }
}

int64 find(int64 node) {
    if (father[node] != node) {
        father[node] = find(father[node]);
    }
    return father[node];
}

void unite(int64 A, int64 B) {
    int64 rootA = find(A);
    int64 rootB = find(B);
    if (height[rootA] > height[rootB]) {
        father[rootB] = rootA;
        height[rootA] = max(height[rootA], height[rootB] + 1);
    } else {
        father[rootA] = rootB;
        height[rootB] = max(height[rootB], height[rootA] + 1);
    }
}
int main()
{
	return 0;
}
