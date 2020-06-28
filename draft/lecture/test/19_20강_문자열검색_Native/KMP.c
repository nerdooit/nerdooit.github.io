#include <stdio.h>
#include <string.h>
#define MAX 100
char sentence[] = "ABACABABABACABABACABABACABABABACABABACABABACA";
char word[] = "ABACABA";

char fixTable[100];

void printFixTable(void)
{
	int i;
	int length = strlen(word) + 1;
	for (i = 0; i < length; i++) {
		printf("%2d", fixTable[i]);
	}
	printf("\n");
}

void printstring(const char *str)
{
	int i;
	printf("  ");
	for (i = 0; i < strlen(str); i++) {
		printf("%2c", str[i]);
	}
	printf("\n");
}
void makeFixTable(void)
{
	int j = 0;
	int i;
	int length = strlen(word);

	for (i = 1; i < length; i++) {
		while ((j > 0) && (word[i] != word[j])) {
			j = fixTable[j];
		}
		if (word[i] == word[j]) {
			fixTable[i + 1] = ++j;
		}
	}
	fixTable[0] = -1;
}

int findPattern(void)
{
	int j = 0;
	int i;
	int slen = strlen(sentence);
	int wlen = strlen(word);
	int cnt = 0;
	for (i = 0; i < slen; i++) {
		while ((j > 0) && (sentence[i] != word[j])) {
			j = fixTable[j];
		}
		if(j<0){ // j가 음수이면 i만  증가 시킴
			j = 0;
		}
		if (sentence[i] == word[j]) {
			j++;
			if (j == wlen) {
				cnt += 1;
				printf("%d번 검색완료!!!\n", cnt);
				j = fixTable[j];
			}
		}
	}
	return cnt;
}

int main(void)
{
	int cnt;
	makeFixTable();
	printstring(sentence);
	printstring(word);
	printFixTable();
	cnt = findPattern();
	printf("%d번 검색\n", cnt);
	return 0;
}

