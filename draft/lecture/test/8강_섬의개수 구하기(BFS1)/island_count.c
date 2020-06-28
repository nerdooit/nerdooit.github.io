#include<stdio.h>
#define MAX 50
typedef enum{false, true} bool;

int a[MAX][MAX];      // 땅과 바다 정보 저장 배열 
int check[MAX][MAX];  // 탐색여부 체크 배열 
int dx[] = { 0, 0, 1,-1, 1, 1,-1,-1 };  // 8방향 탐색을 위한 x 상대좌표 배열 
int dy[] = { 1,-1, 0, 0, 1,-1, 1,-1 };  // 8방향 탐색을 위한 y 상대좌표 배열 
int w, h;  // 지도의 너비, 높이  저장변수
int queue[MAX*MAX*2];  // 너비우선 탐색 시 사용할 선형 queue 
int front, rear;       

int dataLoad();   // TC에 해당하는 데이터 읽어 들이는 함수 
bool inRange(int x, int y); // 지도 범위 검사 함수 
void bfs(int x, int y);  // 너비우선 탐색 함수 

int main()
{
	int cnt;
	int i, j, k, tc;
	
	freopen("land.txt", "rt", stdin);
	scanf("%d", &tc);
	
	for(k = 1; k<=tc; k++){
		cnt = 0;
		dataLoad();
		for (i = 0; i<h; i++) {
			for (j = 0; j<w; j++) {
				if (a[i][j] == 1 && check[i][j] == 0) {
					bfs(i, j);
					cnt++;   // 섬의 개수 count 
				}
			}
		}
		printf("섬의 개수 : %d개\n", cnt);
	}
	return 0;
}
/*--------------------------------------------------------------------------------------
Function Name : bfs() - 연결되어진 섬을 너비우선으로 탐색하는 함수 
Argument      : x, y - 탐색을 시작할 x, y 좌표 
Return Valuse : 없음
--------------------------------------------------------------------------------------*/
void bfs(int x, int y)
{
	// TODO
	int k, nx, ny;
	front = rear = 0;

	queue[rear++] = x;
	queue[rear++] = y;

	while(front != rear) {
		x = queue[front++];
		y = queue[front++];

		for (k = 0; k < 8; k++) {
			nx = x + dx[k];
			ny = y + dy[k];

			if (inRange(nx, ny) == true) {
				if ((a[nx][ny] == 1) && (check[nx][ny] == 0)) {
					queue[rear++] = nx;
					queue[rear++] = ny;
					check[nx][ny] = 1;
				}
			}
		}
	}

}
/*--------------------------------------------------------------------------------------
Function Name : dataLoad() - 데이터파일내의 땅과 바다 정보를 읽어서 저장하고 check배열을 초기화 시킴 
Argument      : 없음
Return Valuse : 없음
--------------------------------------------------------------------------------------*/
int dataLoad()
{
	int i, j; /* iterator */
	scanf("%d %d", &w, &h);
	if (w == 0 && h == 0) return false;
	for (i = 0; i<h; i++) {
		for (j = 0; j<w; j++) {
			scanf("%d", &a[i][j]);  // 땅과 바다의 정보를  
			check[i][j] = 0;  // check 배열 초기화 
		}
	}
	return true;
}
/*--------------------------------------------------------------------------------------
Function Name : inRange() - x, y 범위체크 함수 
Argument      : x, y - x, y 좌표 값 
Return Valuse : 지도 범위내의 위치이면 true, 범위 밖이면 false 리턴 
--------------------------------------------------------------------------------------*/
bool inRange(int x, int y)
{
	if (0 <= x && x < h && 0 <= y && y < w) {
		return true;
	}
	else{
		return false;
	}
}

