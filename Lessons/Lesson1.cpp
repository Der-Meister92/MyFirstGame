#include "TXLib.h"

void MoveBall ();

int main ()
    {
    txCreateWindow (800, 600);
    txClear ();

    MoveBall ();
    }

 void MoveBall ()
    {
    int x  = 100,  y = 100,
    vx = 5,  vy = 3;

    int dt = 1;

    txSetColor (TX_LIGHTGREEN, 3);
    txSetFillColor (TX_GREEN);

    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        txCircle (x, y, 20);
        x += vx * dt;
        y += vy * dt;

        if (x > 800)
            {
            vx = -vx;
            x = x-2*(x-800);
            }

        if (x < 0)
            {
            vx = -vx;
            x = x-2*x;
            }

        if (y > 600)
            {
            vy = -vy;
            y = y-2*(y-600);
            }

        if (y < 0)
            {
            vy = -vy;
            y = y-2*y;
            }

        if (txGetAsyncKeyState (VK_RIGHT)) x+=5;
        if (txGetAsyncKeyState (VK_LEFT)) x-=5;
        if (txGetAsyncKeyState (VK_UP)) y-=5;
        if (txGetAsyncKeyState (VK_DOWN)) y+=5;

        txSleep (1);
        }
    }

