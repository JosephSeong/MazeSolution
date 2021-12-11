#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 
#define MAZE_SIZE 10

typedef struct Mouse
{
	short x;
	short y;
}Mouse;

typedef struct Stack
{
	Mouse data[MAX_SIZE];
	int top;
}Stack;

char maze[MAZE_SIZE][MAZE_SIZE];

void init(Stack* p) { p->top = -1; }

int is_full(Stack* p) { return (p->top == MAX_SIZE - 1); }

int is_empty(Stack* p) { return (p->top == -1); }

void push(Stack* p, Mouse data)
{
	if (is_full(p))
	{
		printf("스택이 꽉찼습니다\n");
		return;
	}
	else
	{
		p->top++;
		p->data[p->top].x = data.x;
		p->data[p->top].y = data.y;
	}
}

Mouse pop(Stack* p)
{
	if (is_empty(p))
	{
		printf("스택이 비어있습니다\n");
		exit(1);
	}
	return p->data[(p->top)--];
}

void FindWay(Stack* s, int x, int y)
{
	if (x < 0 || y < 0 || x > MAZE_SIZE || y > MAZE_SIZE) return;
	if (maze[x][y] != '1' && maze[x][y] != '.')
	{
		Mouse tmp;
		tmp.x = x;
		tmp.y = y;
		push(s, tmp);
	}
}

int main() {
	Stack s;
	Mouse m;
	int i, j, x, y;

	m.x = 0;
	m.y = 0;

	init(&s);

	FILE* fp;
	fopen_s(&fp, "Maze.txt", "r");
	char c;

	printf("미로\n");
	while ((c = getc(fp)) != EOF) {
		putchar(c);

		for (i = 0; i < MAZE_SIZE + 1; i++)
		{
			for (j = 0; j < MAZE_SIZE; j++)
			{
				fscanf_s(fp, "%c", &maze[i][j]);
				printf("%c", maze[i][j]);
				/*if (maze[i][j] == '0') {
					printf("□");
				}
				else if (maze[i][j] == '1') {
					printf("■");
				}
				else {
					printf("%c", maze[i][j]);
				}*/
			}
		}

		// 시작점 탐색 
		for (i = 0; i < MAZE_SIZE; i++)
		{
			for (j = 0; j < MAZE_SIZE; j++)
			{
				if (maze[i][j] == 'e')
				{
					m.x = i;
					m.y = j;
				}
			}
		}
		printf("\n");

		printf("\n이동 경로\n");
		printf("시작 (%d,%d) -> ", m.x, m.y);

		while (maze[m.x][m.y] != 'x')
		{
			x = m.x;
			y = m.y;
			maze[x][y] = '.'; // 방문한 곳을 표시 

			// 이동 가능한 곳을 탐색
			FindWay(&s, x + 1, y);
			FindWay(&s, x - 1, y);
			FindWay(&s, x, y + 1);
			FindWay(&s, x, y - 1);

			if (is_empty(&s))
			{
				printf("이동경로를 찾을 수 없습니다. 실패 \n");
				return 0;
			}
			else
			{
				m = pop(&s); // 현재 좌표를 변경
				printf("(%d,%d) -> ", m.x, m.y);
			}
		}
		printf("도착\n");
		printf("탐색 성공\n");

		fclose(fp);
		return 0;
	}

	if (!fp) // 읽을 파일이 없는 경우
	{
		printf("there is no input file\n");
		fclose(fp);
		return -1;
	}
}
