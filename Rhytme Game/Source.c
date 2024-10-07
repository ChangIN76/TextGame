#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <WinUser.h>

#define MAGIC_KEY 224   // 상하좌우 키
#define SPACE 32        // 스페이스 키
#define KEY_NUM 4       // 입력할 수 있는 키의 개수
#define LIFE 3          // 남은 횟수
#define MAX_LEVEL 11    // 최고 레벨

enum MENU
{
    GAMESTART = 0,
    INFO,
    QUIT
};

enum KEYBOARD
{
    UP = 72,    //↑
    LEFT = 75,  // ←
    RIGHT = 77, // → 
    DOWN = 80   // ↓
};

typedef struct
{
    int x;
    int y;
    int MENU;
} Arrow;

void DrawUserCursor(int y) // 커서 움직이는 것 출력 대신 선택 숫자를 출력
{
    if (y <= 0)
    {
        y = 0;
    }
    else if (y >= 2)
    {
        y = 2;
    }
}

void ReadyGame()
{
    int y = 0;
    int input = 0;
    while (1)
    {
        DrawReadyGame();
        DrawUserCursor(y);
        input = std::cin.get()

        if (input == MAGIC_KEY)
        {
            switch (std::cin.get())
            {
            case UP:
                --y;
                break;
            case DOWN:
                ++y;
                break;
            }
        }
        else if (input == SPACE)
        {
            switch (y)
            {
            case 0:
                return GAMESTART;
            case 1:
                return INFO;
            case 2:
                return QUIT;
            }
        }
    }
}


void SetQuestion(std::vector<int>& questionVec, int level)
{
    if (level > MAX_LEVEL)
    {
        level = MAX_LEVEL;
    }

    int num = 0;


    srand((unsigned int)time(NULL));

    for (int i = 0; i < level; ++i) //화살표의 개수 (문제 난이도)
    {
        num = rand() % KEY_NUM; //화살표 종류.
        switch (num)
        {
        case 0:
            questionVec.push_back(UP);
            break;
        case 1:
            questionVec.push_back(RIGHT);
            break;
        case 2:
            questionVec.push_back(LEFT);
            break;
        case 3:
            questionVec.push_back(DOWN);
            break;
        }
    }
}

void VectorToString(const std::vector<int> v, std::string& str)
{
    for (int i = 0; i < static_cast<int>(v.size()); ++i)
    {
        switch (i)
        {
        case UP:
            str += "↑ ";
            break;
        case DOWN:
            str += "↓ ";
            break;
        case LEFT:
            str += "← ";
            break;
        case RIGHT:
            str += "→ ";
            break;
        }
    }
}


void StartGame()
{
    std::vector<int> questionVec;
    std::string questionStr = "";
    std::vector<int> answerVec;
    std::string answerStr = "";

    int firstInput = 0;
    int secondInput = 0;
    while (1)
    {
        int level = 1; // 예시로 간단히 설정

        SetQuestion(questionVec, level);  //문제를 세팅

        VectorToString(questionVec, questionStr);  //문제를 보여주기
        while (1)
        {

            DrawStartGame(3, 0, questionStr, answerStr); //문제를 가지고 문제를 푼다.


            firstInput = std::cin.get();   //정답 하나씩 입력.
            if (firstInput == MAGIC_KEY)
            {
                secondInput = std::cin.get();
                answerVec.push_back(secondInput);
                switch (secondInput)
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
            else if (firstInput == SPACE)
            {

                if (CheckAnswer(questionVec, answerVec))   //답안 제출

                    std::cout << "정답입니다!" << std::endl;
            }
            else
            {
                std::cout << "틀렸습니다." << std::endl;
            }

            questionVec.clear();
            questionStr = "";
            answerVec.clear();
            answerStr = "";
            break;
        }
    }
}


int main(void)
{
    while (1)
    {
        switch (ReadyGame())
        {
        case GAMESTART:
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
