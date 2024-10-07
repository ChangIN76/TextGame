#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <conio.h>
#include <WinUser.h>

#define MAGIC_KEY 224   // 상하좌우 키
#define SPACE 32        // 스페이스 키
#define LIFE 3          // 남은 횟수
#define KEY_NUM 4       // 입력할 수 있는 키의 개수
#define MAX_LEVEL 11    // 최고 레벨

// const int UP = 72;
// const int RIGHT = 77;
// const int LEFT = 75;
// const int DOWN = 80;
// const int KEY_NUM = 4;
// const int MAX_LEVEL = 11;

enum MENU
{
    GAMESTART = 0,
    INFO,
    QUIT
};

enum KEYBOARD
{
    UP = 72,    // ↑
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
        DrawUserCursor(y);
        input = _getch(); 

        if (input == MAGIC_KEY)
        {
            switch (_getch())
            {
            case UP:
                if (y > 0) --y;
                break;
            case DOWN:
                if (y < 2) ++y;
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

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    std::vector<int> questionVec;
    int level = 5;
}

void SetQuestion(std::vector<int>& questionVec, int level)
{
    if (level > MAX_LEVEL)
    {
        level = MAX_LEVEL;
    }
    
    questionVec.clear();

      for (int i = 0; i < level; ++i) 
      {
           int num = rand() % KEY_NUM; 
           questionVec.push_back(num + 72); 
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



void VectorToString(const std::vector<int>& v, std::string& str)
{
    for (const int& direction : v)
    {
        switch (direction)
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

bool CheckAnswer(const std::vector<int>& questionVec, const std::vector<int>& answerVec)
{
    /
    return questionVec == answerVec; 
}

void StartGame()
{
    std::vector<int> questionVec;
    std::string questionStr = "";
    std::vector<int> answerVec;
    std::string answerStr = "";

    while (1)
    {
        int level = 1;

        SetQuestion(questionVec, level);  
        VectorToString(questionVec, questionStr);  

        
        while (1)
        {
            
            DrawStartGame(3, 0, questionStr, answerStr);

            int firstInput = _getch(); 
            if (firstInput == MAGIC_KEY)
            {
                int secondInput = _getch();
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
                if (CheckAnswer(questionVec, answerVec)) 
                    std::cout << "정답입니다!" << std::endl;
                else
                    std::cout << "틀렸습니다." << std::endl;

                break; 
            }
            
            questionVec.clear();
            questionStr = "";
            answerVec.clear();
            answerStr = "";
        }
    }
}

int main(void)
{
    srand((unsigned int)time(NULL));
