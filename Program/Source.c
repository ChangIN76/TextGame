#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define SIZE 10

void shuffle(int array[], int size)
{
	//  for (int i = 0; i < size; i++)
	//  {
	//  	int seed = rand() % size;
	//  
	//  	int temporary = array[seed];
	//  
	//  	array[seed] = array[i];
	//  
	//  	array[i] = temporary;
	//  }
		
}

int main()
{

#pragma region ���� �Լ�

	//  srand(time(NULL));
	//  
	//  //  0   1   2   3   4   5   6   7   8   9
	//  // [1] [2] [3] [4] [5] [6] [7] [8] [9] [10]
	//  int list[10] = { 1,2,3,4,5,6,7,8,9,10 };
	//  
	//  int size = sizeof(list) / sizeof(int);
	//  
	//  shuffle(list, size);
	//  
	//  for (int i = 0; i < size; i++)
	//  {
	//  	printf("list�� [%d]�� �� : %d\n", i, list[i]);
	//  }

#pragma endregion

#pragma region ������ �迭
		
	//  const char* dialog[10];
	//  
	//  dialog[0] = "�ȳ��ϼ���?";
	//  dialog[1] = "�����Ű���?";
	//  dialog[2] = "Ž���Դϴ�.";
	//  dialog[3] = "���� �Ƿ����Դϴ�.";
	//  dialog[4] = "������ ����� �ִٰ� �ؼ� �Խ��ϴ�.";
	//  dialog[5] = "�� �½��ϴ�.";
	//  dialog[6] = "�� ��ǿ� ���� �ƽô� �� �ֳ���?";
	//  dialog[7] = "���� �˰� �ֽ��ϴ�";
	//  dialog[8] = "������ �ּ���";
	//  dialog[9] = "�� ..";
	//  
	//  int i = 0;
	//  
	//  while (i < SIZE)
	//  {
	//  	// 0X0000 : ������ ���� ���� ���� ȣ�� �������� �������� ���� ����
	//  
	//  	// 0X0001 : ������ ���� ���� �ְ� ȣ�� �������� �������� ���� ����
	//  
	//  	// 0X8000 : ������ ���� ���� ���� ȣ�� �������� �����ִ� ����
	//  
	//  	// 0X8001 : ������ ���� ���� �ְ� ȣ�� �������� �����ִ� ����
	//  
	//  
	//  	if (GetAsyncKeyState(VK_SPACE) & 0X0001)
	//  	{
	//  		if (i % 2 == 0)
	//  		{
	//  			printf("Ž�� : %s\n", dialog[i]);
	//  		}
	//  		else
	//  		{
	//  			printf("�Ƿ��� : %s\n", dialog[i]);
	//  		}
	//  		i++;
	//  	}
	//  	
	//  }
	//  
	//  
	//  printf("��ȭ ����");


#pragma endregion

	return 0;
}




