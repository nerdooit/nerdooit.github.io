#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#define MAX_LENGTH (10000)
int naiveMatching(char *originalStr, char *searchStr);
int main()
{
	char sentence[] = "ABACABABABACABABACABABACABABABACABABACABABACA";
	char word[] = "ABACABA";
	int count;
	count = naiveMatching(sentence, word);
	printf("%d번 검색완료!!!\n", count);
	return 0;
}
int naiveMatching(char *originalStr, char *searchStr)
{
	size_t i, j;
	size_t originalStrLen, searchStrLen;
	int matchFlag;
	int matchCnt=0;
	// TO DO
	originalStrLen = strlen(originalStr);
	searchStrLen = strlen(searchStr);

	for (i = 0; i <= (originalStrLen - searchStrLen); i++) {
		matchFlag = true;
		for (j = 0; j < searchStrLen; j++) {
			if (originalStr[i + j] != searchStr[j]) {
				matchFlag = false;
				break;
			}
		}
		if (matchFlag == true) {
			matchCnt++;
		}
	}
	

	return matchCnt;
}


