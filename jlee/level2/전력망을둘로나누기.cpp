// https://school.programmers.co.kr/learn/courses/30/lessons/86971

/*
* ������ �ϳ��� ���� ���鼭 ���� Ž���Ͽ� ����� ������ �ϳ��ϳ� ����.
* n���� ����ž�� �ϳ��� Ʈ�� ���·� ����Ǿ� �ִ�.
* ��, �ѷ� ������ �� ���ʸ� Ž���ϸ� ���� �ϳ��� Ʈ���� ������ �� �� �ִ�.
* 
* solution()�� ������ ���� �������� �����ȴ�.
* 1. init()���� Adjacency list�� �湮����� �ʱ�ȭ �Ѵ�.
* 2. deleteEdgeGetAdj() �� ������ �ϳ� ���Ͽ� ������ ��, �׿� �°� Adjacency list �� �����Ѵ�.
* 3. dfs()�� Ʈ���� Ž���Ѵ�.
* 4. 2���� Ʈ�� ��, Ž���� Ʈ���� ��� ��(cnt)�� Ž������ ���� �κ�(n - cnt) �� ���밪 ���� ���ϰ� �ּҰ� ����.
*/

#include <string>
#include <vector>
#include <cmath>
#include <cstring>

#define MAXN 100

using namespace std;

int n;
vector<vector<int>> wires;
vector<int> adj[MAXN];  // adjacency list
bool visited[MAXN];

int cnt;
int min_abs = 21e8;

void init() {
    for (int i = 0; i < n; i++) adj[i].clear();
    memset(visited, false, sizeof(visited));
}

void deleteEdgeGetAdj(int edgeIdx) {
    for (int i = 0; i < n - 1; i++) {
        if (i == edgeIdx) continue;
        // ��� �ѹ� 1����
        int v1 = wires[i][0] - 1;
        int v2 = wires[i][1] - 1;
        // ���� �׷���
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }
}

void dfs(int now) {

    visited[now] = true;
    cnt++;

    for (int nxt : adj[now]) {
        if (visited[nxt]) continue;
        dfs(nxt);
    }
}

int solution(int n_, vector<vector<int>> wires_) {
    n = n_;
    wires = wires_;

    for (int i = 0; i < n - 1; i++) {
        init();

        deleteEdgeGetAdj(i);
        cnt = 0;
        dfs(0);

        int tmp = abs(cnt - (n - cnt));
        if (min_abs > tmp) min_abs = tmp;
    }

    return min_abs;
}