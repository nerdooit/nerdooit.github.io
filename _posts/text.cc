#include <iostream>
#define MAX 10
using namespace std;

int arr[MAX];
bool visited[MAX];
void perm (int idx, int cnt)
{
	if (idx == cnt) {
		for (int i = 0; i < cnt; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
		return;
	}

	for (int j = 0 ; j < cnt; j++) {
			if (!visited[j]) {
			arr[idx] = j + 1;
			visited[j] = true;
			perm(idx + 1, cnt);
			visited[j] = false;
		}
	}
}

int main() {
	perm(0, 3);
}
