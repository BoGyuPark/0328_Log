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
			//t�ʿ� �ش��ϴ� ����ȣ�� �������ť�� �ִ´�.
			while (!TimeQ[t].empty()) {
				recWq.push(TimeQ[t].front());
				TimeQ[t].pop();
			}

			//�� ����â���� �������ť�� �ִ� ������� push
			while (true) {
				if (!recWq.empty()) {
					int emptyNum = FindEmptyQ(recq);
					if (emptyNum == -1) break;
					//a[j]�� ��ŭ ����ȣ�� �ִ´�.
					for (int j = 0; j < aList[emptyNum]; j++)	recq[emptyNum].push(recWq.front());
					
					//�� ����â���� �� ����ȣ�� ����
					ReceptionLog[emptyNum][recWq.front()]++;
					recWq.pop();
				}
				else break;
			}

			//�� ����â���� ������ť�� �ִ� ������� push
			while (true) {
				if (!repWq.empty()) {
					int emptyRepairNum = FindEmptyQ(repq);
					if (emptyRepairNum == -1) break;
					//a[j]�� ��ŭ ����ȣ�� �ִ´�.
					for (int j = 0; j < bList[emptyRepairNum]; j++)	repq[emptyRepairNum].push(repWq.front());
					
					//�� ����â���� �� ����ȣ�� ����
					RepairLog[emptyRepairNum][repWq.front()]++;
					repWq.pop();
				}
				else break;
			}
			
			//���� â���� �Ź� pop
			for (int i = 1; i <= n; i++) {
				if (!recq[i].empty()) {
					int temp = recq[i].front();
					recq[i].pop();
					//pop�� â���� �����(��, �ش� ���� �������ٷ� Ǫ��)
					if (recq[i].empty()) repWq.push(temp);
				}
			}

			//���� â���� �Ź� pop
			for (int i = 1; i <= m; i++) {	if (!repq[i].empty()) repq[i].pop();}
			
			//���� ���� �� ���� ���� ���
			int flag = 0;
			for (int i = 1; i <= n; i++) {	if (recq[i].size() == 0) flag++;}
			//for (int i = 1; i <= m; i++) {	if (repq[i].size() == 0) flag++;}
			//if (MAXtime<t && flag == n + m && recWq.empty() && repWq.empty()) break;
			if (MAXtime < t && recWq.empty() && repWq.empty()&& flag==n) break;
			t++;
		}
		
		int sum = 0;
		//A����â���� B����â���� ���� ����ȣ�� ã��!!!
		for (int i = 1; i <= k; i++) {
			if (ReceptionLog[a][i] == 1 && RepairLog[b][i] == 1) {
				sum += i;
			}
		}
		if (sum == 0) sum = -1;
		cout << '#' << tc << ' ' << sum << '\n';
	}
}