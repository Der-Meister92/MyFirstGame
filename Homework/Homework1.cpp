#include "TXLib.h"
#include "../include/DerMeisterLib.h"

const int WindowWidth  = 1400,
          WindowHeight = 700,
          SleepTime    = 1;

void MadamAndBall (int x, int y, int x1, int y1, int vx, int vy, int dt);

int main ()
    {
    txCreateWindow (WindowWidth, WindowHeight);
    txClear ();

    MadamAndBall (100, 600, 100, 100, 5, 3, 2);
    }

void MadamAndBall (int x, int y, int x1, int y1, int vx, int vy, int dt)
    {
    txBegin ();
    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        txClear ();
        BackgroundBeach (20);
        MnogoTravi (480, 0);
        ZadniiPlan (40);

        txSetColor (RGB (x, x % 250, 0), 3);
        txSetFillColor (RGB (y, y % 250, 0));

        txCircle (x1, y1, 20);
        x1 += vx * dt;
        y1 += vy * dt;

        if (x1 > WindowWidth)
            {
            vx = -vx;
            x1 = x1 - 2 * (x1 - WindowWidth);
            }
        if (x1 < 0)
            {
            vx = -vx;
            x1 = x1 - 2 * x1;
            }
        if (y1 > WindowHeight)
            {
            vy = -vy;
            y1 = y1 - 2 * (y1 - WindowHeight);
            }
        if (y1 < 0)
            {
            vy = -vy;
            y1 = y1 - 2 * y1;
            }

        if (x > WindowWidth - 20)   x = WindowWidth - 20;
        if (x < 20)                 x = 20;
        if (y > WindowHeight - 100) y = WindowHeight - 100;
        if (y < 300)                y = 300;

        if ((! txGetAsyncKeyState (VK_DOWN )) && (! txGetAsyncKeyState (VK_UP  )) &&
            (! txGetAsyncKeyState (VK_RIGHT)) && (! txGetAsyncKeyState (VK_LEFT)))
            {
            MadamDraw (x, y, 1, 1, 2, 1, 1, 0, 0, 1, 1, 0, 0, 1);
            }

        if (txGetAsyncKeyState (VK_RIGHT))
            {
            MadamDrawProfil (x, y, TX_BLUE, 0, 0, 0 + ((x + y) / 10) % 2, 1 - ((x + y) / 10) % 2, 1, 1);
            x += 3;
            }

        if (txGetAsyncKeyState (VK_LEFT))
            {
            MadamDrawProfil (x, y, TX_BLUE, 0, 0, 0 + ((x + y) / 10) % 2, 1 - ((x + y) / 10) % 2, 1, -1);
            x -= 3;
            }

        if (txGetAsyncKeyState (VK_UP))
            {
            MadamDraw (x, y, 0, 1, 1, 1, 1, 0, 0, 0 + ((x + y) / 10) % 2, 1 - ((x + y) / 10) % 2, 0, 0, 1);
            y -= 3;
            }

        if (txGetAsyncKeyState (VK_DOWN))
            {
            MadamDraw (x, y, 1, 1, 2, 1, 1, 0, 0, 0 + ((x + y) / 10) % 2, 1 - ((x + y) / 10) % 2, 0, 0, 1);
            y +=3 ;
            }

        if (txGetAsyncKeyState (VK_SPACE))
            {
            y -= 10;
            }

        txSleep (SleepTime);
        }

    txEnd ();
    }
