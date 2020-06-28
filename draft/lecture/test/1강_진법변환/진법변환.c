#include <stdio.h>
char d[21] = "0123456789ABCDEFGHIJ"; // 1~20진법에서 사용될 숫자문자열
	 // 예를들어 8진법은 0~7까지의 문자만 사용하고 20진법은 0~J까지 사용함
void f(int n, int k)
{
	// TODO
	if (n < k) {
    printf("%c",d[n%k]);
    return;
  }
  f(n/k, k);
  printf("%c",d[(n%k)%k]);

}

int main()
{
	int n, k;
	scanf("%d %d", &n, &k);
	f(n, k);
	return 0;
}

