#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

#define MAGIC_KEY 224   // 상하좌우 키
#define SPACE 32        // 스페이스 키
#define LIFE 3          // 남은 횟수
#define KEY_NUM 4       // 입력할 수 있는 키의 개수
#define MAX_LEVEL 10    // 최고 난이도

enum MENU
{
    START,              // 게임 시작 화면
    INFO,               // 게임 진행 화면
    QUIT                // 게임 종료 화면
};

enum KEYBOARD
{
    UP = 72,            // ↑
    LEFT = 75,          // ←
    RIGHT = 77,         // → 
    DOWN = 80           // ↓
};

void SetConsoleView()
{
    system("mode con:cols=50 lines=20");    // 콘솔 창 화면 크기
}

void gotoxy(int x, int y)   // 화면 출력 문자 좌표 설절
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawReadyGame()    // 게임 시작 화면
{
    system("cls");
    gotoxy(25, 3);
    cout << "-----------------------";
    gotoxy(25, 4);
    cout << "| Rhythm Game !!!!!!! |";
    gotoxy(25, 5);
    cout << "-----------------------";
    gotoxy(25, 10);
    cout << "Press SPACE! To Start!!";
}

void DrawStartGame(const int life, const int score, const string questionStr, const string answerStr)   // 게임 진행 화면
{                                                                                                       // 목숨, 점수, 문제, 답안 설정
    system("cls");
    gotoxy(2, 1);
    cout << "*******************************************";
    gotoxy(4, 3);
    cout << "Life : " << life << " / " << LIFE;     //  남은 목숨 / 전체 목숨
    gotoxy(4, 4);
    cout << "Score : " << score;
    gotoxy(4, 8);
    cout << "Q : " << questionStr;
    gotoxy(4, 10);
    cout << "A : " << answerStr;
    gotoxy(4, 12);
    cout << "Press SPACE! After Done!!";
    gotoxy(2, 18);
    cout << "*******************************************";
}

void DrawGameOver(const int playTime)   // 게임 시작 화면 , 재시작 알림
{
    system("cls");      
    gotoxy(25, 4);
    cout << " GAME OVER !!!!!!!! ";
    gotoxy(25, 6);
    cout << " Time : " << playTime << " sec ";
    gotoxy(25, 10);
    cout << " Press SPACE! To Restart!!";

    _getch(); // 종료 화면이 바로 끝나지 않도록 대기
}

 int ReadyGame()
 {
     int x = 0;             // 메뉴 선택 (0: START, 1: INFO, 2: QUIT)
     int input = 0;         // 사용자 입력 저장
     while (true)
     {
         DrawReadyGame();   // 게임 시작 화면 불러오기
         input = _getch();  // 키 입력 대기
 
         if (input == MAGIC_KEY) // 방향키 식별
         {
             switch (_getch())   // 방향 확인
             {
             case UP:
                 --x;
                 if (x < 0) x = 0; // 메뉴 범위 이탈 방지
                 break;
             case DOWN:
                 ++x;
                 if (x > 2) x = 2; // 메뉴 범위 이탈 방지
                 break;
             }
         }
         else if (input == SPACE)  // 스페이스바 누르면 메뉴 보기
         {
             switch (x)
             {
             case 0:
                 return START; // 게임 시작 화면(초기)
             case 1:
                 return INFO;  // 게임 진행 화면
             case 2:
                 return QUIT;  // 게임 종료 화면
             }
         }
     }
 }

void InfoGame()
{
   system("pause>null");       // 일시정지, 화면이 넘어가지 않게 설정
}

void SetQuestion(vector<int>& questionVec, int level)  // 문제와 난이도 설정
{
    if (level > MAX_LEVEL)     // 난이도가 MAX LEVEL 넘어가면 최대 난이도로 고정
    {
        level = MAX_LEVEL;
    }
     
    int num = 0;
    srand((unsigned int)time(NULL)); 
    for (int i = 0; i < level; ++i)         // level수 만큼 문제 생성
    {
        num = rand() % KEY_NUM;             // 랜덤 변수 생성 (방향키)
        switch (num)
        {
        case 0:
            questionVec.push_back(UP);      // 0일 때 위 방향키
            break;
        case 1:
            questionVec.push_back(RIGHT);   // 1일 때 오른쪽 방향키
            break;
        case 2:
            questionVec.push_back(LEFT);    // 2일 때 왼쪽 방향키
            break;
        case 3:
            questionVec.push_back(DOWN);    // 3일 때 아래 방향키
            break;
        }
    }
}

void VectorToString(const vector<int> v, string& str)   // 문자열로 바꾸기
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < static_cast<int>(v.size()); ++i)
    {
        switch (v[i])
        {
        case UP:
            // SetConsoleTextAttribute(hConsole, 12);
            str += "↑ ";    // 위 방향키면 "↑ " 추가
            break;
        case DOWN:
            // SetConsoleTextAttribute(hConsole, 10);
            str += "↓ ";    // 아래 방향키면 "↓ " 추가
            break;
        case LEFT:
            // SetConsoleTextAttribute(hConsole, 9);
            str += "← ";    // 왼쪽 방향키면 "← " 추가
            break;
        case RIGHT:
            // SetConsoleTextAttribute(hConsole, 14);
            str += "→ ";    // 오른쪽 방향키면 "→ " 추가
            break;
        }
    }
    // SetConsoleTextAttribute(hConsole, 7);   // 원래 색상으로 변경
}

bool CheckAnswer(const vector<int> questionVec, const vector<int> answerVec)    // 정답 검사 함수
{
    if (questionVec.size() != answerVec.size())     // 두 벡터 크기가 다르면
    {
        return false;       // 오답 처리. false 반환
    }
    for (int i = 0; i < static_cast<int>(questionVec.size()); ++i)
    {
        if (questionVec[i] != answerVec[i])         // 두 벡터의 i값이 다르면
        {
            return false;   // 오답 처리. false 반환
        }
    }
    return true;            // 모든 요소 같으면 true 반환
}

void StartGame()    // 게임 시작
{
    int life = LIFE;                     // 목숨 설정
    int score = 0;                       // 점수 설정
    clock_t startTime, endTime;          // 게임 시작 시간과 종료 시간 기록
    startTime = clock();

    vector<int> questionVec;             // 문제 저장
    string questionStr = "";             // 문제를 문자열로 변환

    vector<int> answerVec;               // 플레이어 답안
    string answerStr = "";               // 플레이어 답안을 문자열로 변환

    int firstInput = 0;                  // 첫 번째 입력 (방향키)
    int secondInput = 0;                 // 두 번째 입력 (MEGIC KEY)

    while (true)                         // 게임 종료까지(false가 될때까지) 반복
    {
        int level = (score / 30) + 1;    // 점수가 오를수록 레벨 상승

        SetQuestion(questionVec, level);            //문제 세팅
        VectorToString(questionVec, questionStr);   //문제 문자열로 보여주기

        while (true)       // 한 문제가 끝날 때까지
        {
            DrawStartGame(life, score, questionStr, answerStr); // 게임 진행 화면 출력

            if (life == 0) // 목숨이 0이 되면 게임 오버
            {
                endTime = clock(); // 게임 종료 시간 기록
                int playTime = static_cast<int>((endTime - startTime) / CLOCKS_PER_SEC); // 총 걸린 시간 계산

                DrawGameOver(playTime); // 게임 종료 화면 출력
                return;
            }

            firstInput = _getch();                 // 키 입력 받았을 때
            if (firstInput == MAGIC_KEY)           // 그게 방향키인 경우
            {
                secondInput = _getch();
                answerVec.push_back(secondInput); // 방향키값 백터에 추가
                switch (secondInput)              // 문자열로 변환 
                {
                case UP:
                    answerStr += "↑ ";
                    break;
                case DOWN:
                    answerStr += "↓ ";
                    break;
                case LEFT:
                    answerStr += "← ";
                    break;
                case RIGHT:
                    answerStr += "→ ";
                    break;
                }
            }
            else if (firstInput == SPACE)   // 스페이스바 누르면 정답 제출하는 함수
            {
                if (CheckAnswer(questionVec, answerVec)) // 정답 일치하면
                {
                    score += 10;     // 10점 추가 (점수 올라갈수록 난이도 증가)
                }
                else                 // 틀렸으면
                {
                    --life;          // 목숨 하나 감소
                    score -= 5;      // 5점 감소
                    if (score < 0)   // 점수가 0점 밑으로 내려가지 않게 설정
                    {
                        score = 0;
                    }
                }

                questionVec.clear(); // 게임 끝나고 새로운 문제를 위해 초기화
                questionStr = "";
                answerVec.clear();   // 답안도 초기화
                answerStr = "";
                break;
            }
        }
    }
}

int main()
{
    SetConsoleView();  // 콘솔 창 크기
    while (true)       // 무한루프
    {
        switch (ReadyGame()) // 메뉴 선택
        {
        case START:
            StartGame();
            break;
        case INFO:
            InfoGame();
            break;
        case QUIT:
            return 0;
        }
    }
    return 0;
}
