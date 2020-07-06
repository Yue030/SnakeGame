#include <conio.h>
#include <iostream>

#define end '\n'

using namespace std;

//Border Width
#define WIDTH 22
//Border Height
#define HEIGHT 17

//is GameOver or not
bool gameover;

//Posistion and the player score
int x, y, fruitX, fruitY, score;

//Snake Coordinates
int tailX[100], tailY[100];

//Tail
int nTail;

enum eDirection
{
    STOP,
    LEFT,
    RIGHT,
    UP,
    DOWN
}; //Direction Control

void setFruit()
{
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
}

eDirection dir;

void setup()
{
    //Not Gameover
    gameover = false;

    //Set the control stop
    dir = STOP;

    //Set the default position
    x = WIDTH / 2;
    y = HEIGHT / 2;

    //Display Fruit in random place
    setFruit();

    //Init Score
    score = 0;
}

void draw()
{
    system("cls");

    //Width Border
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << end;

    //Height Border
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0)
                cout << "#"; //Walls

            if (i == y and j == x)
                cout << "*"; //Snake Tail
            else if (i == fruitY and j == fruitX)
                cout << "%"; //Change it to change the fruit
            else
            {
                bool print = false;

                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j and tailY[k] == i)
                    {
                        cout << "*";
                        print = true;
                    }
                }

                if (!print)
                    cout << " ";
            }

            if (j == WIDTH - 1)
                cout << "#";
        }
        cout << end;
    }

    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";

    cout << end;

    cout << "Score: " << score << end;

    cout << "Code By: Yue" << end;
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;

        case 'A':
            dir = LEFT;
            break;

        case 'w':
            dir = UP;
            break;

        case 'W':
            dir = UP;
            break;

        case 's':
            dir = DOWN;
            break;

        case 'S':
            dir = DOWN;
            break;

        case 'd':
            dir = RIGHT;
            break;

        case 'D':
            dir = RIGHT;
            break;

        case 'x':
            gameover = true;
            break;

        case 'X':
            gameover = true;
            break;
        }
    }
}

void algorithm()
{
    int prevX = tailX[0];
    int prevY = tailY[0];

    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;

    case RIGHT:
        x++;
        break;

    case UP:
        y--;
        break;

    case DOWN:
        y++;
        break;

    default:
        break;
    }

    if (x >= WIDTH)
        x = 0;
    else if (x < 0)
        x = WIDTH - 1;

    if (y >= HEIGHT)
        y = 0;
    else if (y < 0)
        y = HEIGHT - 1;

    for (int i = 1; i < nTail; i++)
        if(tailX[i] == x and tailY[i] == y)
            gameover = true;

    if (x == fruitX and y == fruitY)
    {
            score += 10;

            setFruit();

            nTail++;
    }
}

int main()
{
    setup();

    while (!gameover)
    {

        draw();

        input();

        algorithm();
    }

    system("cls");

    cout << "Game Over!!!" << end;
    cout << "Final Score: " << score << end;
    cout << "Thank For Playing" << end;

    system("pause");
    return 0;
}
