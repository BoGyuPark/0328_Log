#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int tc, T, n, m, k, a, b;
int FindEmptyQ(vector<queue<int>> q) {
	for (int i = 1; i < q.size(); i++) {
		if (q[i].size() == 0) return i;
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> T;
	for (tc = 1; tc <= T; tc++) {
		cin >> n >> m >> k >> a >> b;
		vector<queue<int>> recq(n+1), repq(m+1), TimeQ(1001);
		queue<int>  recWq, repWq;
		int ReceptionLog[12][1001] = { 0, }, RepairLog[12][1001] = { 0, };
		int aList[12] = { 0, }, bList[12] = { 0, };
		for (int i = 1; i <= n; i++) cin >> aList[i];
		for (int i = 1; i <= m; i++) cin >> bList[i];
		int MAXtime = 0;
		for (int i = 1; i <= k; i++) {
			int temp; cin >> temp;
			MAXtime = temp;
			TimeQ[temp].push(i);
		}
		
		int t = 0;
		while (true) {
			//t초에 해당하는 고객번호를 접수대기큐에 넣는다.
			while (!TimeQ[t].empty()) {
				recWq.push(TimeQ[t].front());
				TimeQ[t].pop();
			}

			//빈 접수창구에 접수대기큐에 있는 순서대로 push
			while (true) {
				if (!recWq.empty()) {
					int emptyNum = FindEmptyQ(recq);
					if (emptyNum == -1) break;
					//a[j]개 만큼 고객번호를 넣는다.
					for (int j = 0; j < aList[emptyNum]; j++)	recq[emptyNum].push(recWq.front());
					
					//각 접수창구에 들어간 고객번호를 저장
					ReceptionLog[emptyNum][recWq.front()]++;
					recWq.pop();
				}
				else break;
			}

			//빈 정비창구에 정비대기큐에 있는 순서대로 push
			while (true) {
				if (!repWq.empty()) {
					int emptyRepairNum = FindEmptyQ(repq);
					if (emptyRepairNum == -1) break;
					//a[j]개 만큼 고객번호를 넣는다.
					for (int j = 0; j < bList[emptyRepairNum]; j++)	repq[emptyRepairNum].push(repWq.front());
					
					//각 정비창구에 들어간 고객번호를 저장
					RepairLog[emptyRepairNum][repWq.front()]++;
					repWq.pop();
				}
				else break;
			}
			
			//접수 창구를 매번 pop
			for (int i = 1; i <= n; i++) {
				if (!recq[i].empty()) {
					int temp = recq[i].front();
					recq[i].pop();
					//pop한 창구가 비었다(즉, 해당 고객은 정비대기줄로 푸쉬)
					if (recq[i].empty()) repWq.push(temp);
				}
			}

			//정비 창구를 매번 pop
			for (int i = 1; i <= m; i++) {	if (!repq[i].empty()) repq[i].pop();}
			
			//차량 접수 및 정비가 끝난 경우
			int flag = 0;
			for (int i = 1; i <= n; i++) {	if (recq[i].size() == 0) flag++;}
			//for (int i = 1; i <= m; i++) {	if (repq[i].size() == 0) flag++;}
			//if (MAXtime<t && flag == n + m && recWq.empty() && repWq.empty()) break;
			if (MAXtime < t && recWq.empty() && repWq.empty()&& flag==n) break;
			t++;
		}
		
		int sum = 0;
		//A접수창구와 B정비창구를 지난 고객번호를 찾자!!!
		for (int i = 1; i <= k; i++) {
			if (ReceptionLog[a][i] == 1 && RepairLog[b][i] == 1) {
				sum += i;
			}
		}
		if (sum == 0) sum = -1;
		cout << '#' << tc << ' ' << sum << '\n';
	}
}