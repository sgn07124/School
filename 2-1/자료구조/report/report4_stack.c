#include <stdio.h>
#define MAX_STACK_SIZE 400
#define FALSE 0
#define TRUE 1
#define EXIT_ROW 18 //행  탈출
#define EXIT_COL 18 //열 

typedef struct {
	int vert; // 수직 좌표
	int horiz; // 수평 좌표
} offsets;
offsets move[8] = { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} }; // 방향 표시

typedef struct {
	short int row;
	short int col;
	short int dir;
} element;
element stack[MAX_STACK_SIZE];

void path(void);
void push(int* top, element position);
element pop(int* top);

int top;

int maze[20][20] = {

	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,1,1,0,1,1,1,0,0,0,0,0,0,0,1,0,1,1,1},
	{1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,0,0,0,1},
	{1,0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1},
	{1,0,1,1,0,1,1,1,0,0,0,1,0,0,0,1,0,1,0,1},
	{1,0,1,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1},
	{1,0,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0,1,0,1},
	{1,1,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1},
	{1,0,0,0,0,1,0,1,0,1,0,1,1,1,1,0,0,1,0,1},
	{1,0,0,0,0,1,0,1,0,1,0,0,1,0,0,0,1,1,0,1},
	{1,1,1,1,0,0,1,0,0,1,0,1,1,0,0,0,1,1,0,1},
	{1,1,1,1,0,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1},
	{1,1,1,1,0,1,0,0,0,1,0,1,1,1,0,0,0,0,0,1},
	{1,1,1,0,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0,1},
	{1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1},
	{1,0,1,0,0,1,0,1,0,0,1,0,1,1,1,1,1,0,1,1},
	{1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,1,1},
	{1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int mark[20][20] = { 0, };

void path(void) { // 경로가 있다면 패스 출력
	int i, row, col, next_row, next_col, dir;
	int found = FALSE; // 1이면 출구
	element position;
	mark[1][1] = 1; // 방문 설정 (시작점)
	top = 0; // 시작점 스택에 push
	stack[0].row = 1;
	stack[0].col = 1;
	stack[0].dir = 1;
	while (top > -1 && !found) { // stack에 path가 남아있고 출구를 찾지 못한 상태
		position = pop(&top); // 스택에서 pop
		row = position.row;
		col = position.col;
		dir = position.dir;
		while (dir < 8 && !found) { // 내 주변의 8방향을 찾아보기
			next_row = row + move[dir].vert;
			next_col = col + move[dir].horiz;
			if (next_row == EXIT_ROW && next_col == EXIT_COL) { // 다음 위치가 EXIT 이면
				found = TRUE; // 탈출 성공
			}
			else if (!maze[next_row][next_col] && !mark[next_row][next_col]) { // 다음 위치가 0이면서 방문한 적이 없을 때
				mark[next_row][next_col] = TRUE;
				position.row = row;
				position.col = col;
				position.dir = ++dir;
				push(&top, position); // 스택에 현재 위치 저장
				row = next_row;
				col = next_col;
				dir = 0;
			}
			else ++dir; // exit이 아니며 갈 수 없은 곳일 때 (방문을 했었거나 벽이거나)
		}
	}

	if ( found ) { // 출구 찾음
		printf("\n\n< Path > \n"); // 방문한 길 출력
		printf("row col\n");
		for (i = 0; i <= top; i++)
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
	}
	else printf("no path found!!\n"); // 미로 탈출 X
}

void push(int *top, element position) {
	(*top)++;
	stack[*top].row = position.row;
	stack[*top].col = position.col;
	stack[*top].dir = position.dir;
}

element pop(int* top) {
	element result;
	if (*top < 0) {
		printf("Stack is Empty.\n");
	}
	else {
		result = stack[*top];
		(*top)--;
	}
	return result;
}


int main() {
	printf("< Maze >\n"); // 미로 출력
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
	path(); // 경로 출력
	return 0;
}
