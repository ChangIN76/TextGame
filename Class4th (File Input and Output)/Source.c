#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> 
#include <windows.h>

#define MAX_ARROWS 5
#define SCREEN_HEIGHT 20

typedef struct {
    int x;
    int active;
} Arrow;

Arrow arrows[MAX_ARROWS];
int score = 0;

void initArrows() {
    for (int i = 0; i < MAX_ARROWS; i++) {
        arrows[i].x = -1; // ��Ȱ��ȭ ���¿����� ��ġ
        arrows[i].active = 0; // ��Ȱ��ȭ ����
    }
}

void generateArrow() {
    for (int i = 0; i < MAX_ARROWS; i++) {
        if (!arrows[i].active) {
            arrows[i].x = rand() % 80; // ���ο� ���� ��ġ ����
            arrows[i].active = 1; // Ȱ��ȭ
            break; // �ϳ��� ����
        }
    }
}

void render() {
    system("cls"); // �ܼ� ȭ�� �����
    for (int i = 0; i < MAX_ARROWS; i++) {
        if (arrows[i].active) {
            for (int j = 0; j < SCREEN_HEIGHT; j++) printf("\n");
            for (int j = 0; j < arrows[i].x; j++) printf(" ");
            printf("��\n"); // ȭ��ǥ ǥ��
        }
    }
    printf("Score: %d\n", score);
}

void checkInput() {
    if (_kbhit()) { // Ű�� ���ȴ��� üũ
        char ch = _getch(); // ���� Ű ��������
        for (int i = 0; i < MAX_ARROWS; i++) {
            if (arrows[i].active) {
                // ��Ȯ�� �Է��� ���
                if (ch == 'a' && arrows[i].x < 40) { // ���� ȭ��ǥ
                    score++;
                    arrows[i].active = 0; // ��Ȱ��ȭ
                }
                else if (ch == 'd' && arrows[i].x >= 40) { // ������ ȭ��ǥ
                    score++;
                    arrows[i].active = 0; // ��Ȱ��ȭ
                }
            }
        }
    }
}

int main() {
    srand(time(NULL)); // ���� �õ� ����
    initArrows(); // ȭ��ǥ �ʱ�ȭ

    while (1) {
        generateArrow(); // �� ȭ��ǥ ����
        render(); // ȭ�� ���
        checkInput(); // Ű �Է� ó��

        Sleep(1000); // 1�� ���

        // ���� ����: ��� ȭ��ǥ�� ��Ȱ��ȭ ���°� �Ǹ� ����
        int allInactive = 1;
        for (int i = 0; i < MAX_ARROWS; i++) {
            if (arrows[i].active) {
                allInactive = 0; // �ϳ��� Ȱ��ȭ�� ȭ��ǥ�� ������ ��Ȱ��ȭ �ƴ�
                break;
            }
        }
        if (allInactive) {
            break;
        }

        // ���� ����: Esc Ű ������ ����
        if (_kbhit() && _getch() == 27) { // 27�� Esc Ű
            break;
        }
    }

    printf("Game Over! Final Score: %d\n", score);
    return 0;


}
