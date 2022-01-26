#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
int length = 20;
int width = 50;
int x, y; // position of a snake part
int fruitx, fruity; // position of fruit
int score;
char pressed;
vector<pair<int,int>>body; //snake

void Setup()
{
    gameOver = false;
    score = 0;
    // Places the snake in the middle
    x = length / 2;
    y = width / 2;
    body.push_back({x, y});

    //Spawns the fruit in random places
    fruitx = rand()%length;
    fruity = rand()%width;
}

void Draw()
{
    system("cls");
    for(int i=0; i<width+2; ++i)
    cout<<"#";

    cout<<endl;

    for(int i=0; i<length; ++i)
    {
        for(int j=0; j<width+2; ++j)
        {
            if(j == 0)
            cout<<"#";
            else if(i == x && j == y)
            cout<<"O";
            else if(i == fruitx && j == fruity)
            cout<<"F";
            else if(j == width+1)
            cout<<"#"<<endl;
            else
            {
                bool r = false;
                for(int k=1; k<body.size(); ++k)
                {
                    if(i == body[k].first && j == body[k].second)
                    {
                        cout<<"O";
                        r = true;
                    }
                }

                if(r == false)
                cout<<" ";
            }
        }
    }

    for(int i=0; i<width+2; ++i)
    cout<<"#";

    cout<<"\nScore: "<<score;
}

void isOver()
{
    //Lose if hit wall
    if(x == length || x < 0 || y == width+1 || y == 0)gameOver = true;

    /*//Can Go through wall
    if(x == length+1)x = 1;
    else if(x < 1)x = length;

    if(y == width+2)y = 1;
    else if(y == 1)y = width+1;*/
}

void Input ()
{
    if(_kbhit ())
    {
        switch(_getch())
        {
            case 'a':
            pressed = 'a';
            break;

            case 'd':
            pressed = 'd';
            break;

            case 'w':
            pressed = 'w';
            break;

            case 's':
            pressed = 's';
            break;

            case 'x':
            gameOver = true;
            break;
        }
    }
}

void Action()
{
    for(int i=body.size()-1; i>0; --i)
    {
        body[i].first = body[i-1].first;
        body[i].second = body[i-1].second;
    }

    if(pressed == 'w')
    --x;
    else if(pressed == 's')
    ++x;
    else if(pressed == 'a')
    --y;
    else if(pressed == 'd')
    ++y;

    body[0].first = x;
    body[0].second = y;

    if(x == fruitx && y == fruity)
    {
        ++score;
        body.push_back({body[body.size()-1].first, body[body.size()-1].second});

        fruitx = rand()%(length-2);
        fruity = rand()%(width-2);
    }

    isOver();
}

int main()
{

    Setup();

    do{
    Draw();

    Input();

    Action();

    Sleep(10);
    }while(gameOver == false);

    return 0;
}
