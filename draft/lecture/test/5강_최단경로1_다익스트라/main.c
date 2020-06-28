#include <stdio.h>
#include "Dijkstra.h"

int main(void) {
	int i;
	int start; // 출발 정점 저장변수 

	freopen("data2.txt", "r", stdin);

	initGraph();
	printGraph();

	start = 1;  // B 정점 기준  
	dijkstra(start);  // B 정점 기준  
	printDistance(start);
	printPredecessor();

	printf("--- %c 기준 최소 비용 및 경로 ---\n", start+'A');
	for (i=0 ; i<vertex ; i++) {
		printf("최소비용 : %c -> %c : %d\n", start+'A', i + 'A', D[i]);
		printPath(start, i);
	}

	return 0;
}

