#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "snake.h"

void snakeMove(int dir, positition Snake[], int realSnakeLength)
{
    Snake[0].x0 = Snake[0].x;
	Snake[0].y0 = Snake[0].y;
	Snake[0].x += Direct[dir].x;
	Snake[0].y += Direct[dir].y;
	for (int i = 1; i < realSnakeLength; ++i) {
		Snake[i].x0 = Snake[i].x;
		Snake[i].y0 = Snake[i].y;
		Snake[i].x = Snake[i - 1].x0;
		Snake[i].y = Snake[i - 1].y0;
	}
    //If Snake through over the wall
    if (Snake[0].x + Snake[0].width > Arena.x + Arena.w ) Snake[0].x = Arena.x;
    else if (Snake[0].x < Arena.x) Snake[0].x = Arena.x + Arena.w - Snake[0].width;
    if (Snake[0].y  + Snake[0].height > Arena.y + Arena.h ) Snake[0].y = Arena.y;
    else if (Snake[0].y < Arena.y) Snake[0].y = Arena.y + Arena.h  - Snake[0].height;

    SDL_Delay(speed);
}

void moveA()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP])
    {
        if(preDirectionA != DOWN && preDirectionA != UP)
        {
            directionA = UP;
            preDirectionA = UP;
        }
    }
    else if (state[SDL_SCANCODE_DOWN])
    {
        if(preDirectionA != DOWN && preDirectionA != UP)
        {
            directionA = DOWN;
            preDirectionA = DOWN;
        }
    }
    else if (state[SDL_SCANCODE_RIGHT])
    {
        if(preDirectionA != RIGHT && preDirectionA != LEFT)
        {
            directionA = RIGHT;
            preDirectionA = RIGHT;
        }
    }
    else if (state[SDL_SCANCODE_LEFT])
    {
        if(preDirectionA != RIGHT && preDirectionA != LEFT)
        {
            directionA = LEFT;
            preDirectionA = LEFT;
        }
    }
    snakeMove(directionA, SnakeA, realSnakeLengthA);
}

void moveB()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W])
    {
        if(preDirectionB != DOWN && preDirectionB != UP)
        {
            directionB = UP;
            preDirectionB = UP;
        }
    }
    else if (state[SDL_SCANCODE_S])
    {
        if(preDirectionB != UP && preDirectionB != DOWN)
        {
            directionB = DOWN;
            preDirectionB = DOWN;
        }
    }
    else if (state[SDL_SCANCODE_D])
    {
        if(preDirectionB != RIGHT && preDirectionB != LEFT)
        {
            directionB = RIGHT;
            preDirectionB = RIGHT;
        }
    }
    else if (state[SDL_SCANCODE_A])
    {
        if(preDirectionB != RIGHT && preDirectionB != LEFT)
        {
            directionB = LEFT;
            preDirectionB = LEFT;
        }
    }
    snakeMove(directionB, SnakeB, realSnakeLengthB);
}

void increaseSnakeA(int n)
{
    for(int i = 0; i < n; i++)
    {
        SnakeA[displaySnakeLengthA].x = SnakeA[displaySnakeLengthA - 1].x0;
        SnakeA[displaySnakeLengthA].y = SnakeA[displaySnakeLengthA - 1].y0;
        displaySnakeLengthA += 1;
        realSnakeLengthA += 1;
    }
}

void decreaseSnakeA(int n)
{
    displaySnakeLengthA -= n;
}

void increaseSnakeB(int n)
{
    for(int i = 0; i < n; i++)
	{
	    SnakeB[displaySnakeLengthB].x = SnakeB[displaySnakeLengthB - 1].x0;
        SnakeB[displaySnakeLengthB].y = SnakeB[displaySnakeLengthB - 1].y0;
        displaySnakeLengthB += 1;
        realSnakeLengthB += 1;
	}
}

void decreaseSnakeB(int n)
{
    displaySnakeLengthB -= n;
}

void eatBomb()
{
    for(int i = 0; i < bombB_num; i++)
    {
        if(SnakeA[0].x == bombRectB[i].x && SnakeA[0].y == bombRectB[i].y && bombBStatus[i] == true)
        {
            decreaseSnakeA(1);
            if(scoreA >= 5) scoreA -= 5;
            else scoreA = 0;
            bombBStatus[i] = false;
        }
    }
    for(int i = 0; i < bombA_num; i++)
    {
        if(SnakeB[0].x == bombRectA[i].x && SnakeB[0].y == bombRectA[i].y && bombAStatus[i] == true)
        {
            decreaseSnakeB(1);
            if(scoreB >= 5) scoreB -= 5;
            else scoreB = 0;
            bombAStatus[i] = false;
        }
    }
}

void makeFoodA()
{
    foodA.x = rand()%((Arena.w)/size) * size + Arena.x;
    foodA.y = rand()%((Arena.h)/size) * size + Arena.y;
}

void makeFoodB()
{
    foodB.x = rand()%(Arena.w/size) * size + Arena.x;
    foodB.y = rand()%(Arena.h/size) * size + Arena.y;
}

void eatFoodA()
{
    if(SnakeA[0].x == foodA.x && SnakeA[0].y == foodA.y)
    {
        if(displaySnakeLengthA <= 9) increaseSnakeA(1);
        scoreA ++;
        makeFoodA();
    }
    else if(SnakeB[0].x == foodA.x && SnakeB[0].y == foodA.y)
    {
        if(displaySnakeLengthB <= 9) increaseSnakeB(1);
        scoreB ++;
        makeFoodA();
    }
}

void eatFoodB()
{
    if(SnakeA[0].x == foodB.x && SnakeA[0].y == foodB.y)
    {
        if(displaySnakeLengthA <= 9) increaseSnakeA(1);
        scoreA ++;
        makeFoodB();
    }
    else if(SnakeB[0].x == foodB.x && SnakeB[0].y == foodB.y)
    {
        if(displaySnakeLengthB <= 9) increaseSnakeB(1);
        scoreB++;
        makeFoodB();
    }
}

void dropBombA()
{
    bombRectA[bombA_num].x = SnakeA[displaySnakeLengthA - 1].x;
    bombRectA[bombA_num].y = SnakeA[displaySnakeLengthA - 1].y;
    bombRectA[bombA_num].w = SnakeA[displaySnakeLengthA - 1].width;
    bombRectA[bombA_num].h = SnakeA[displaySnakeLengthA - 1].height;
    bombAStatus[bombA_num] = true;
    bombA_num++;
}

void dropBombB()
{
    bombRectB[bombB_num].x = SnakeB[displaySnakeLengthB - 1].x;
    bombRectB[bombB_num].y = SnakeB[displaySnakeLengthB - 1].y;
    bombRectB[bombB_num].w = SnakeB[displaySnakeLengthB - 1].width;
    bombRectB[bombB_num].h = SnakeB[displaySnakeLengthB - 1].height;
    bombBStatus[bombB_num] = true;
    bombB_num++;
}

void throughBomb()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_RSHIFT])
    {
        if(displaySnakeLengthA != 2)
        {
            decreaseSnakeA(1);
            dropBombA();
        }
    }

    if (state[SDL_SCANCODE_SPACE])
    {
        if(displaySnakeLengthB != 2)
        {
            decreaseSnakeB(1);
            dropBombB();
        }
    }
}
