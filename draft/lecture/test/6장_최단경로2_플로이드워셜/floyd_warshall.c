#include<stdio.h>
#define MAX 100   // 최대 노드 개수 
#define INF  1000  // 무한 가중치 

int dist[MAX+1][MAX+1];  // 그래프 연결 정보 저장(인접 행렬법)
int path[MAX+1][MAX+1];  // path 저장 배열 
int vertext,edge;     // 정점의 개수와 간선의 개수 저장 
void initGraph();    // 데이터 파일의 내용을 인접행렬로 생성하는 함수 
void floydWarshall();  // floydWarshall 알고리즘으로 최단거리와 경로 구하는 함수 
void printPath(int s, int t);   // 경로 출력 재귀함수(시작정점과 끝 정점을 제외한 중간정점 출력)  
void printGraph(int (*p)[MAX+1]);  // 인접행렬이나  직전정점(Predecessor) 저장 배열 출력 

int main()
{
	int s, e;
	initGraph();
	printf("[Graph matrix]\n");
	printGraph(dist);
	
	floydWarshall();  // floydWarshall 알고리즘 수행 
	 
	printf("[Predecessor]\n");
	printGraph(path);

	// 경로 출력
	s = 1;   // 출발 정점 1 
	e = 6;   // 도착 정점 6 
	printf("%d->%d 이동 경로 : %d >", s, e, s);
	printPath(1,6);
	printf("%d\n", e);

	return 0;
}

/*--------------------------------------------------------------------------------------
Function Name : floydWarshall() - floydWarshall 알고리즘으로 최단거리와 경로 구하는 함수 
Argument      : 없음 
Return Valuse : 없음
--------------------------------------------------------------------------------------*/
void floydWarshall()
{
	// TODO
	int i, j, k;

	for (k = 1; k <= vertext; k++) {
		for (i = 1; i <= vertext; i++) {
			for (j = 1; j <= vertext; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = k;
				}
			}
		}
	}
}

/*--------------------------------------------------------------------------------------
Function Name : initGraph() - 데이터 파일의 내용을 인접행렬로 생성하는 함수 
Argument      : 없음 
Return Valuse : 없음
--------------------------------------------------------------------------------------*/
void initGraph()
{
	// TODO	
	int i,j,s,e,w;

	freopen("data.txt", "rt", stdin);
	scanf("%d %d", &vertext, &edge);
	for (i = 1; i <= vertext; i++) {
		for (j = 1; j <= vertext; j++) {
			dist[i][j] = INF;
		}
		dist[i][i] = 0;
	}

	for (i = 1; i <= edge; i++) {
		scanf("%d %d %d", &s, &e, &w);
		if (w == 0) {
			dist[s][e] = INF;
		} else {
			dist[s][e] = w;
		}
	}
}

/*--------------------------------------------------------------------------------------
Function Name : printGraph() - 인접행렬이나  직전정점(Predecessor) 저장 배열 출력 
Argument      : p - 출력할 배열 
Return Valuse : 없음
--------------------------------------------------------------------------------------*/
void printGraph(int (*p)[MAX+1])
{
	int i, j;
	
	for (i=1; i<=vertext; i++) {
		for (j=1; j<=vertext; j++) {
			printf("%5d", p[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}
/*--------------------------------------------------------------------------------------
Function Name : printPath() - 경로 출력 재귀함수(시작정점과 끝 정점을 제외한 중간정점 출력) 
Argument      : s, t  -  지정 정점 
Return Valuse : 없음
--------------------------------------------------------------------------------------*/
void printPath(int s, int t)
{
	// TODO
	if (path[s][t] == 0) {
		return;
	}
	printPath(s, path[s][t]);
	printf(" %d > ",path[s][t]);
	printPath(path[s][t], t);
}
	


