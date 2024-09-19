#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define WIDTH 11
#define HEIGHT 11

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

typedef struct Charactor
{
	int x;
	int y;
	const char* shape;
}Charactor;

char maze[HEIGHT][WIDTH] =
{
	{ '1','1','1','1','1','1','1','1','1','1','1' },
	{ '1','0','0','1','1','1','1','1','0','2','1' },
	{ '1','0','0','1','1','1','1','1','0','0','1' },
	{ '1','0','0','1','1','1','1','1','0','0','1' },
	{ '1','0','0','1','1','1','1','1','0','0','1' },
	{ '1','0','0','0','0','0','0','0','0','0','1' },
	{ '1','0','0','0','0','0','0','0','0','0','1' },
	{ '1','0','0','0','0','0','0','0','0','0','1' },
	{ '1','1','1','1','0','0','0','0','0','0','1' },
	{ '1','1','1','1','0','0','0','0','0','0','1' },
	{ '1','1','1','1','1','1','1','1','1','1','1' },
};

void Render()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (maze[i][j] == '0')
			{
				printf(" ");
			}
			else if (maze[i][j] == '1')
			{
				printf("■");
			}
			else if (maze[i][j] == '2')
			{
				printf("☆");
			}

		}
		printf("\n");
	}
}

void Position(int x, int y)
{
	// x와 y축을 설정하는 구조체입니다.
	COORD position = { x ,y };

	// 콘솔 커서의 좌표를 설정하는 함수입니다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int main()
{
	Charactor charactor = { 2,1,"★" };

	char key = 0;

	Render();

	while (1)
	{
		if (_kbhit())
		{
			key = _getch();

			if (key == -32)
			{
				key = _getch();
			}

			switch (key)
			{
			case UP		: 
				if (maze[charactor.y - 1][charactor.x / 2] != '1')
				{
					charactor.y--;
				}
				break;
			case LEFT	: 
				if (maze[charactor.y][charactor.x / 2 - 1] != '1')
				{
					charactor.x -= 2;
				}			
				break;
			case RIGHT	:
				if (maze[charactor.y][charactor.x / 2 + 1] != '1')
				{
					charactor.x += 2;
				}	
				break;
			case DOWN	: 
				if (maze[charactor.y + 1][charactor.x / 2] != '1')
				{
					charactor.y++;
				}	
				break;
			}



			system("cls");

			Render();
		}

		Position(charactor.x, charactor.y);
		printf("%s", charactor.shape);

	}

	return 0;
}