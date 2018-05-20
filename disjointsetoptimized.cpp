#include<bits/stdc++.h>
using namespace std;
#define N 100005
int father[N],height[N];

void init() {
    for (int i = 0; i < N; ++i) {
        father[i] = i;
        height[i] = 0;
    }
}

int find(int node) {
    if (father[node] != node) {
        father[node] = find(father[node]);
    }
    return father[node];
}

void unite(int A, int B) {
    int rootA = find(A);
    int rootB = find(B);
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
