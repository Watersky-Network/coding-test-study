// https://school.programmers.co.kr/learn/courses/30/lessons/169199?language=cpp

/*
* 1. ���� Ž���� ���� ĭ���� �̵� �� ���� �ִ�.
* 2. �̵� Ƚ���� cost �̹Ƿ� �̵� ĭ���� �����ϴ�. ��, ������ ����ġ�� ������ Ž���̴�.
* 
* DFS ó�� flag�� cnt ������ �ذ��� �� ����.
* BFS Ž�� �� ���� �������� �����Ǳ� ���� �� �������� cnt ���־�� �ϴµ�
* visted �迭�� ����ϰų� dist �迭�� �ϳ� �� ����� ����Ѵ�.
*/

#include <string>
#include <vector>
#include <queue>

#define MAXN 100

using namespace std;

vector<string> board;
int visited[MAXN][MAXN];
int cnt;

int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

struct Node {
    int y, x;
};

Node start, goal;

void init() {
    int y = board.size();
    int x = board[0].size();

    int tmp = 0;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (board[i][j] == 'R') {
                start = { i, j };
                tmp++;
            }
            if (board[i][j] == 'G') {
                goal = { i, j };
                tmp++;
            }
            if (tmp == 2) return;
        }
    }
}

bool isOut(Node n) {
    int y = board.size();
    int x = board[0].size();

    return (n.y < 0 || n.y >= y || n.x < 0 || n.x >= x);
}

void bfs() {
    queue<Node> q;
    q.push(start);
    visited[start.y][start.x] = 1;

    while (!q.empty()) {
        Node now = q.front();
        q.pop();

        if (board[now.y][now.x] == 'G') return;

        for (int i = 0; i < 4; i++) {
            Node nxt = { now.y + dy[i], now.x + dx[i] };
            if (isOut(nxt)) continue;
            if (board[nxt.y][nxt.x] == 'D') continue;

            while (1) {
                nxt.y += dy[i];
                nxt.x += dx[i];
                if (isOut(nxt) || board[nxt.y][nxt.x] == 'D') {
                    nxt.y -= dy[i];
                    nxt.x -= dx[i];
                    break;
                }
            }

            if (visited[nxt.y][nxt.x] != 0) continue;

            visited[nxt.y][nxt.x] = visited[now.y][now.x] + 1;
            q.push(nxt);
        }
    }
}

int solution(vector<string> board_) {
    board = board_;
    init();
    bfs();

    if (visited[goal.y][goal.x] == 0) return -1;

    // ������ �湮 ���� üũ�� ���� bfs() ���� 1�� ���� �����ְ� Ž�� ������ �� ����
    return visited[goal.y][goal.x] - 1;
}