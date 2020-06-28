#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_
#define MAX 100
#define INF (MAX * MAX)
#define NIL -1

extern int G[MAX][MAX];	 // 그래프 인접행렬 배열 
extern int V[MAX];	     // 노드 사용 체크 배열 
extern int D[MAX];		 // 최단거리 저장 배열 
extern int P[MAX];		 // 직전노드 저장 배열 
extern int vertex;		 // 정점 수 저장 
extern int edge;		 // 간선 수 저장 

void initGraph(void);    //그래프 데이터를 읽어들여 인접행열 생성 
void printGraph(void);   //그래프 인접행열 출력 
void dijkstra(int s);    // 전달된 정점으로 부터 나머지 정점까지의 최소 가중치를 계산하고 경로를 연산함
void printDistance(int s);    // 시작정점으로 부터 각 정점까지의 최소가중치를 저장하고 있는 배열 출력 함수 
void printPath(int s, int t); // 시작 정점->끝 정점까지의 path 및 가중치 출력
void printPredecessor(void);  // 직전정점 저장 배열 출력 함수 

#endif /* DIJKSTRA_H_ */

