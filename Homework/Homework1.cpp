#include "TXLib.h"
#include "../include/DerMeisterLib.h"

const int WindowWidth  = 1400,
          WindowHeight = 700,
          SleepTime    = 10;

void MoveMadam (int* x, int* y);
void MoveBall (int* x1, int* y1, int r, int* vx, int* vy, int dt);

int main ()
    {
    txCreateWindow (WindowWidth, WindowHeight);
    txClear ();

    int x = 100, x1 = 100, vx = 5,
        y = 600, y1 = 100, vy = 3;

    txBegin ();
    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        txClear ();
        BackgroundBeach (20);
        MnogoTravi (480, 0);
        ZadniiPlan (40);

        MoveMadam (&x, &y);
        MoveBall (&x1, &y1, 20, &vx, &vy, 3);

        txSleep (SleepTime);
        }
    txEnd ();
    }

void MoveMadam (int* x, int* y)
    {
    if (*x > WindowWidth - 20)   *x = WindowWidth - 20;
    if (*x < 20)                 *x = 20;
    if (*y > WindowHeight - 100) *y = WindowHeight - 100;
    if (*y < 300)                *y = 300;

    if ((! txGetAsyncKeyState (VK_DOWN )) && (! txGetAsyncKeyState (VK_UP  )) &&
        (! txGetAsyncKeyState (VK_RIGHT)) && (! txGetAsyncKeyState (VK_LEFT)))
        {
        MadamDraw (*x, *y, 1, 1, 2, 1, 1, 0, 0, 1, 1, 0, 0, 1);
        }

    if (txGetAsyncKeyState (VK_RIGHT))
        {
        MadamDrawProfil (*x, *y, TX_BLUE, 0, 0, 0 + ((*x + *y) / 10) % 2, 1 - ((*x + *y) / 10) % 2, 1, 1);
        *x += 3;
        }

    if (txGetAsyncKeyState (VK_LEFT))
        {
        MadamDrawProfil (*x, *y, TX_BLUE, 0, 0, 0 + ((*x + *y) / 10) % 2, 1 - ((*x + *y) / 10) % 2, 1, -1);
        *x -= 3;
        }

    if (txGetAsyncKeyState (VK_UP))
        {
        MadamDraw (*x, *y, 0, 1, 1, 1, 1, 0, 0, 0 + ((*x + *y) / 10) % 2, 1 - ((*x + *y) / 10) % 2, 0, 0, 1);
        *y -= 3;
        }

    if (txGetAsyncKeyState (VK_DOWN))
        {
        MadamDraw (*x, *y, 1, 1, 2, 1, 1, 0, 0, 0 + ((*x + *y) / 10) % 2, 1 - ((*x + *y) / 10) % 2, 0, 0, 1);
        *y += 3 ;
        }

    if (txGetAsyncKeyState (VK_SPACE))
        {
        *y -= 10;
        }
    }

void MoveBall (int* x1, int* y1, int r, int* vx, int* vy, int dt)
    {
    txSetColor (RGB (*x1, *x1 % 250, 0), 3);
    txSetFillColor (RGB (*y1, *y1 % 250, 0));

    txCircle (*x1, *y1, r);
    *x1 += *vx * dt;
    *y1 += *vy * dt;

    if (*x1 > WindowWidth  - r)
        {
        *vx = - *vx;
        *x1 = *x1 - 2 * (*x1 - WindowWidth  + r);
        }
    if (*x1 < 0 + r)
        {
        *vx = - *vx;
        *x1 = *x1 - 2 * (*x1 - r);
        }
    if (*y1 > WindowHeight  - r)
        {
        *vy = - *vy;
        *y1 = *y1 - 2 * (*y1 - WindowHeight  + r);
        }
    if (*y1 < 0 + r)
        {
        *vy = - *vy;
        *y1 = *y1 - 2 * (*y1 - r);
        }
    }
