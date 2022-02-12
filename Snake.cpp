#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>
using namespace std;
//Snake game

bool gameOver;
int width = 50;
int height = 20;
// x->x axis  y->y axis
int x, y;            // position of snake head
int fruitx, fruity; // position of fruit
int score;
char pressed;
vector<pair<int,int>>body; //snake

void Setup()
{
    gameOver = false;
    score = 0;
    // Places the snake in the middle
    x = width / 2;
    y = height / 2;
    body.push_back({x, y});

    //Spawns the fruit in random places
    fruitx = rand()%width;
    fruity = rand()%height;
}

void Draw()
{
    system("cls");
    for(int i=0; i<width+2; ++i)
    cout<<"#";

    cout<<endl;

    for(int i=0; i<height; ++i)
    {
        for(int j=0; j<width+2; ++j)
        {
            if(j == 0)
            cout<<"#";
            else if(i == y && j == x)
            cout<<"O";
            else if(i == fruity && j == fruitx)
            cout<<"F";
            else if(j == width+1)
            cout<<"#"<<endl;
            else
            {
                bool r = false;
                for(int k=1; k<body.size(); ++k)
                {
                    if(j == body[k].first && i == body[k].second)
                    {
                        cout<<"o";
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
    if(y == height || y < 0 || x == width+1 || x == 0)gameOver = true;

    /*//Can Go through wall
    if(y == height+1)y = 1;
    else if(y < 1)y = height;

    if(x == width+2)x = 1;
    else if(x == 1)x = width+1;*/
}

void Input ()
{
    if(_kbhit())
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

void ifFruitEaten()
{
    if(x == fruitx && y == fruity)
    {
        ++score;
        body.push_back({body[body.size()-1].first, body[body.size()-1].second});

        fruitx = rand()%(width-2);
        fruity = rand()%(height-2);
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
    --y;
    else if(pressed == 's')
    ++y;
    else if(pressed == 'a')
    --x;
    else if(pressed == 'd')
    ++x;

    body[0].first = x;
    body[0].second = y;

    //Check if snake ate fruit
    ifFruitEaten();

    //Check if game is over
    isOver();
}

int main()
{

    Setup();

    while(gameOver == false)
    {
        Draw();

        Input();

        Action();

        Sleep(20); //controls speed of snake
    };

    return 0;
}
