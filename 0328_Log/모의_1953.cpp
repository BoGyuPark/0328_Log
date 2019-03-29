#include<iostream>
#include<queue>
using namespace std;
int tc, T, n, m, r, c, l;
int InTrans[8] = { 0,15,3,12,9,10,6,5 };
int OutTrans[8] = { 0,15,3,12,6,5,9,10 };
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> T;
	for (tc = 1; tc <= T; tc++) {
		int a[51][51] = { 0, }, pipeIn[51][51] = { 0, }, pipeOut[51][51] = { 0, };
		int check[51][51] = { 0, };
		cin >> n >> m >> r >> c >> l;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> a[i][j];
				pipeIn[i][j] = InTrans[a[i][j]];
				pipeOut[i][j] = OutTrans[a[i][j]];
			}
		}
		int sum = 1;
		queue<pair<int, int>> q;
		q.push({ r,c });
		check[r][c] = true;
		int s[2] = { 0,2 };
		l--;
		while (l--) {
			int QSize = q.size();
			if (QSize == 0) break;
			while (QSize--) {
				int x = q.front().first, y = q.front().second;
				q.pop();
				for (int i = 0; i < 4; i++) {
					//나갈수 있는방향 체크
					if (pipeIn[x][y] & (1 << i)) {
						int nx = x + dx[i], ny = y + dy[i];
						if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
						if (check[nx][ny] == true) continue;
						if (a[nx][ny] == 0) continue;
						//다음 파이프에서 들어올수있는 방향인지 체크
						if (pipeOut[nx][ny] & (1 << i)) {
							check[nx][ny] = true;
							q.push({ nx,ny });
							sum++;
						}
					}
				}
			}
		}
		cout << '#' << tc << ' ' << sum << '\n';
	}
}