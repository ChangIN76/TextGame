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
        arrows[i].x = -1; // 비활성화 상태에서의 위치
        arrows[i].active = 0; // 비활성화 상태
    }
}

void generateArrow() {
    for (int i = 0; i < MAX_ARROWS; i++) {
        if (!arrows[i].active) {
            arrows[i].x = rand() % 80; // 새로운 랜덤 위치 설정
            arrows[i].active = 1; // 활성화
            break; // 하나만 생성
        }
    }
}

void render() {
    system("cls"); // 콘솔 화면 지우기
    for (int i = 0; i < MAX_ARROWS; i++) {
        if (arrows[i].active) {
            for (int j = 0; j < SCREEN_HEIGHT; j++) printf("\n");
            for (int j = 0; j < arrows[i].x; j++) printf(" ");
            printf("↑\n"); // 화살표 표시
        }
    }
    printf("Score: %d\n", score);
}

void checkInput() {
    if (_kbhit()) { // 키가 눌렸는지 체크
        char ch = _getch(); // 누른 키 가져오기
        for (int i = 0; i < MAX_ARROWS; i++) {
            if (arrows[i].active) {
                // 정확한 입력일 경우
                if (ch == 'a' && arrows[i].x < 40) { // 왼쪽 화살표
                    score++;
                    arrows[i].active = 0; // 비활성화
                }
                else if (ch == 'd' && arrows[i].x >= 40) { // 오른쪽 화살표
                    score++;
                    arrows[i].active = 0; // 비활성화
                }
            }
        }
    }
}

int main() {
    srand(time(NULL)); // 랜덤 시드 설정
    initArrows(); // 화살표 초기화

    while (1) {
        generateArrow(); // 새 화살표 생성
        render(); // 화면 출력
        checkInput(); // 키 입력 처리

        Sleep(1000); // 1초 대기

        // 종료 조건: 모든 화살표가 비활성화 상태가 되면 종료
        int allInactive = 1;
        for (int i = 0; i < MAX_ARROWS; i++) {
            if (arrows[i].active) {
                allInactive = 0; // 하나라도 활성화된 화살표가 있으면 비활성화 아님
                break;
            }
        }
        if (allInactive) {
            break;
        }

        // 종료 조건: Esc 키 누르면 종료
        if (_kbhit() && _getch() == 27) { // 27은 Esc 키
            break;
        }
    }

    printf("Game Over! Final Score: %d\n", score);
    return 0;


}
