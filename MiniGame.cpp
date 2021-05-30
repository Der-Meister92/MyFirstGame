#include "TXLib.h"

const int WindowWidth  = 1400,
          WindowHeight = 700,
          SleepTime    = 1;

void MoveBall (int* x, int* y, int* x1, int* y1, int* vx, int* vy, int* dt, int r);
void Rectangle (int* x, int* y);
void GameOverText ();

int main ()
    {
    txCreateWindow (WindowWidth, WindowHeight);
    txClear ();

    int x = -50, x1 = 100, vx = 5,  r = 20,
        y = 600, y1 = 100, vy = 3, dt =  1;

    txBegin ();
    while (y1 <= WindowHeight + r)
        {
        txSetFillColor (TX_WHITE);
        txClear ();

        MoveBall (&x, &y, &x1, &y1, &vx, &vy, &dt, 20);
        Rectangle (&x, &y);

        txSleep (SleepTime);
        }

    GameOverText ();
    txEnd ();
    }

void MoveBall (int* x, int* y, int* x1, int* y1, int* vx, int* vy, int* dt, int r)
    {
    txSetColor (TX_BLACK);
    txSetFillColor (TX_BLACK);

    txCircle (*x1, *y1, r);

    *x1 += *vx * (*dt);
    *y1 -= *vy * (*dt);

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

    if (*x1 <= *x + 140 && *x1 >= *x && *y1 >= *y - r)
        {
        *vy = - *vy;
        *y1 = *y  - r;
        }

    if (*y1 < 0 + r)
        {
        *vy = - *vy;
        *y1 = *y1 - 2 * (*y1 - r);
        }

    if (txGetAsyncKeyState ('1')) *dt = 1;
    if (txGetAsyncKeyState ('2')) *dt = 2;
    if (txGetAsyncKeyState ('3')) *dt = 3;
    }

void Rectangle (int* x, int* y)
    {
    txSetColor (TX_BLACK);
    txSetFillColor (TX_BLACK);

    txRectangle (*x, *y, *x + 140, *y + 40);

    if (*x + 140 > WindowWidth) *x = WindowWidth - 140;
    if (*x < 0) *x = 0;

    if (txGetAsyncKeyState (VK_RIGHT)) *x += 30;
    if (txGetAsyncKeyState (VK_LEFT))  *x -= 30;
    }

void GameOverText ()
    {
    txSetTextAlign (TA_CENTER);
    txSelectFont ("Arial Black", 200);

    int CenterX = WindowWidth/2,
        CenterY = WindowHeight/2;

    int textSizeX = txGetTextExtentX ("GAME OVER"),
        textSizeY = txGetTextExtentY ("GAME OVER");

    txSetColor (TX_RED);

    txDrawText (CenterX - textSizeX/2, CenterY - textSizeY/2,
                CenterX + textSizeX/2, CenterY + textSizeY/2, "GAME OVER");
    }
