#include <stdio.h>
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
	{ '1','0','0','1','1','1','0','1','0','2','1' },
	{ '1','1','0','1','1','0','1','0','1','0','1' },
	{ '1','0','0','0','1','1','1','0','0','0','1' },
	{ '1','0','1','0','1','1','1','0','0','0','1' },
	{ '1','0','1','1','1','1','0','0','1','0','1' },
	{ '1','0','0','1','0','1','0','0','1','0','1' },
	{ '1','0','0','0','0','0','0','0','0','0','1' },
	{ '1','1','0','1','1','1','0','1','1','0','1' },
	{ '1','0','0','1','1','1','0','0','0','0','1' },
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
				printf("��");
			}
			else if (maze[i][j] == '2')
			{
				printf("��");
			}

		}
		printf("\n");
	}
}

int main()
{
	Charactor charactor = { 1,1,"��" };

	Render();

	return 0;
}