#include <iostream>
#define MAX 10
using namespace std;

int arr[MAX];

void perm (int idx, int cnt)
{
	if (idx == cnt) {
		for (int i = 0; i < cnt; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	for (int j = 0 ; j < cnt; j++) {
		arr[idx] = j + 1;
		perm(idx + 1, cnt);
	}
}

int main() {
	perm(0, 3);
}
