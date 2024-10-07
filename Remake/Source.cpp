#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

#define MAGIC_KEY 224   // �����¿� Ű
#define SPACE 32        // �����̽� Ű
#define LIFE 3          // ���� Ƚ��
#define KEY_NUM 4       // �Է��� �� �ִ� Ű�� ����
#define MAX_LEVEL 10    // �ְ� ���̵�

enum MENU
{
    START,              // ���� ���� ȭ��
    INFO,               // ���� ���� ȭ��
    QUIT                // ���� ���� ȭ��
};

enum KEYBOARD
{
    UP = 72,            // ��
    LEFT = 75,          // ��
    RIGHT = 77,         // �� 
    DOWN = 80           // ��
};

void SetConsoleView()
{
    system("mode con:cols=50 lines=20");    // �ܼ� â ȭ�� ũ��
}

void gotoxy(int x, int y)   // ȭ�� ��� ���� ��ǥ ����
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawReadyGame()    // ���� ���� ȭ��
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

void DrawStartGame(const int life, const int score, const string questionStr, const string answerStr)   // ���� ���� ȭ��
{                                                                                                       // ���, ����, ����, ��� ����
    system("cls");
    gotoxy(2, 1);
    cout << "*******************************************";
    gotoxy(4, 3);
    cout << "Life : " << life << " / " << LIFE;     //  ���� ��� / ��ü ���
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

void DrawGameOver(const int playTime)   // ���� ���� ȭ�� , ����� �˸�
{
    system("cls");      
    gotoxy(25, 4);
    cout << " GAME OVER !!!!!!!! ";
    gotoxy(25, 6);
    cout << " Time : " << playTime << " sec ";
    gotoxy(25, 10);
    cout << " Press SPACE! To Restart!!";

    _getch(); // ���� ȭ���� �ٷ� ������ �ʵ��� ���
}

 int ReadyGame()
 {
     int x = 0;             // �޴� ���� (0: START, 1: INFO, 2: QUIT)
     int input = 0;         // ����� �Է� ����
     while (true)
     {
         DrawReadyGame();   // ���� ���� ȭ�� �ҷ�����
         input = _getch();  // Ű �Է� ���
 
         if (input == MAGIC_KEY) // ����Ű �ĺ�
         {
             switch (_getch())   // ���� Ȯ��
             {
             case UP:
                 --x;
                 if (x < 0) x = 0; // �޴� ���� ��Ż ����
                 break;
             case DOWN:
                 ++x;
                 if (x > 2) x = 2; // �޴� ���� ��Ż ����
                 break;
             }
         }
         else if (input == SPACE)  // �����̽��� ������ �޴� ����
         {
             switch (x)
             {
             case 0:
                 return START; // ���� ���� ȭ��(�ʱ�)
             case 1:
                 return INFO;  // ���� ���� ȭ��
             case 2:
                 return QUIT;  // ���� ���� ȭ��
             }
         }
     }
 }

void InfoGame()
{
   system("pause>null");       // �Ͻ�����, ȭ���� �Ѿ�� �ʰ� ����
}

void SetQuestion(vector<int>& questionVec, int level)  // ������ ���̵� ����
{
    if (level > MAX_LEVEL)     // ���̵��� MAX LEVEL �Ѿ�� �ִ� ���̵��� ����
    {
        level = MAX_LEVEL;
    }
     
    int num = 0;
    srand((unsigned int)time(NULL)); 
    for (int i = 0; i < level; ++i)         // level�� ��ŭ ���� ����
    {
        num = rand() % KEY_NUM;             // ���� ���� ���� (����Ű)
        switch (num)
        {
        case 0:
            questionVec.push_back(UP);      // 0�� �� �� ����Ű
            break;
        case 1:
            questionVec.push_back(RIGHT);   // 1�� �� ������ ����Ű
            break;
        case 2:
            questionVec.push_back(LEFT);    // 2�� �� ���� ����Ű
            break;
        case 3:
            questionVec.push_back(DOWN);    // 3�� �� �Ʒ� ����Ű
            break;
        }
    }
}

void VectorToString(const vector<int> v, string& str)   // ���ڿ��� �ٲٱ�
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < static_cast<int>(v.size()); ++i)
    {
        switch (v[i])
        {
        case UP:
            // SetConsoleTextAttribute(hConsole, 12);
            str += "�� ";    // �� ����Ű�� "�� " �߰�
            break;
        case DOWN:
            // SetConsoleTextAttribute(hConsole, 10);
            str += "�� ";    // �Ʒ� ����Ű�� "�� " �߰�
            break;
        case LEFT:
            // SetConsoleTextAttribute(hConsole, 9);
            str += "�� ";    // ���� ����Ű�� "�� " �߰�
            break;
        case RIGHT:
            // SetConsoleTextAttribute(hConsole, 14);
            str += "�� ";    // ������ ����Ű�� "�� " �߰�
            break;
        }
    }
    // SetConsoleTextAttribute(hConsole, 7);   // ���� �������� ����
}

bool CheckAnswer(const vector<int> questionVec, const vector<int> answerVec)    // ���� �˻� �Լ�
{
    if (questionVec.size() != answerVec.size())     // �� ���� ũ�Ⱑ �ٸ���
    {
        return false;       // ���� ó��. false ��ȯ
    }
    for (int i = 0; i < static_cast<int>(questionVec.size()); ++i)
    {
        if (questionVec[i] != answerVec[i])         // �� ������ i���� �ٸ���
        {
            return false;   // ���� ó��. false ��ȯ
        }
    }
    return true;            // ��� ��� ������ true ��ȯ
}

void StartGame()    // ���� ����
{
    int life = LIFE;                     // ��� ����
    int score = 0;                       // ���� ����
    clock_t startTime, endTime;          // ���� ���� �ð��� ���� �ð� ���
    startTime = clock();

    vector<int> questionVec;             // ���� ����
    string questionStr = "";             // ������ ���ڿ��� ��ȯ

    vector<int> answerVec;               // �÷��̾� ���
    string answerStr = "";               // �÷��̾� ����� ���ڿ��� ��ȯ

    int firstInput = 0;                  // ù ��° �Է� (����Ű)
    int secondInput = 0;                 // �� ��° �Է� (MEGIC KEY)

    while (true)                         // ���� �������(false�� �ɶ�����) �ݺ�
    {
        int level = (score / 30) + 1;    // ������ �������� ���� ���

        SetQuestion(questionVec, level);            //���� ����
        VectorToString(questionVec, questionStr);   //���� ���ڿ��� �����ֱ�

        while (true)       // �� ������ ���� ������
        {
            DrawStartGame(life, score, questionStr, answerStr); // ���� ���� ȭ�� ���

            if (life == 0) // ����� 0�� �Ǹ� ���� ����
            {
                endTime = clock(); // ���� ���� �ð� ���
                int playTime = static_cast<int>((endTime - startTime) / CLOCKS_PER_SEC); // �� �ɸ� �ð� ���

                DrawGameOver(playTime); // ���� ���� ȭ�� ���
                return;
            }

            firstInput = _getch();                 // Ű �Է� �޾��� ��
            if (firstInput == MAGIC_KEY)           // �װ� ����Ű�� ���
            {
                secondInput = _getch();
                answerVec.push_back(secondInput); // ����Ű�� ���Ϳ� �߰�
                switch (secondInput)              // ���ڿ��� ��ȯ 
                {
                case UP:
                    answerStr += "�� ";
                    break;
                case DOWN:
                    answerStr += "�� ";
                    break;
                case LEFT:
                    answerStr += "�� ";
                    break;
                case RIGHT:
                    answerStr += "�� ";
                    break;
                }
            }
            else if (firstInput == SPACE)   // �����̽��� ������ ���� �����ϴ� �Լ�
            {
                if (CheckAnswer(questionVec, answerVec)) // ���� ��ġ�ϸ�
                {
                    score += 10;     // 10�� �߰� (���� �ö󰥼��� ���̵� ����)
                }
                else                 // Ʋ������
                {
                    --life;          // ��� �ϳ� ����
                    score -= 5;      // 5�� ����
                    if (score < 0)   // ������ 0�� ������ �������� �ʰ� ����
                    {
                        score = 0;
                    }
                }

                questionVec.clear(); // ���� ������ ���ο� ������ ���� �ʱ�ȭ
                questionStr = "";
                answerVec.clear();   // ��ȵ� �ʱ�ȭ
                answerStr = "";
                break;
            }
        }
    }
}

int main()
{
    SetConsoleView();  // �ܼ� â ũ��
    while (true)       // ���ѷ���
    {
        switch (ReadyGame()) // �޴� ����
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
