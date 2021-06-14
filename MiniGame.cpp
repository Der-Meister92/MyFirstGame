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

    int x = -50, x1 = 100, vx = 5,  r = 60,
        y = 600, y1 = 100, vy = 3, dt =  1;

    HDC Background  = txLoadImage ("Background.bmp");

    txBegin ();
    while (y1 <= WindowHeight + r)
        {

        txSetFillColor (TX_WHITE);
        txClear ();

        txBitBlt  (txDC(), 0, 0, WindowWidth, WindowHeight, Background, 0, 0);

        MoveBall (&x, &y, &x1, &y1, &vx, &vy, &dt, 40);
        Rectangle (&x, &y);

        txSleep (SleepTime);
        }

    txPlaySound ("GameOver.wav");
    GameOverText ();

    txEnd ();
    }

void MoveBall (int* x, int* y, int* x1, int* y1, int* vx, int* vy, int* dt, int r)
    {
    txSetColor (RGB (218, 165, 32));
    txSetFillColor (RGB (218, 165, 32));

    txCircle (*x1, *y1, r);

    *x1 += *vx * (*dt);
    *y1 -= *vy * (*dt);

    if (*x1 > WindowWidth - 300  - r)
        {
        *vx = - *vx;
        *x1 = *x1 - 2 * (*x1 - WindowWidth + 300  + r);

        txPlaySound ("Wall.wav");
        }

    if (*x1 < 0 + 300 + r)
        {
        *vx = - *vx;
        *x1 = *x1 - 2 * (*x1 - 300 - r);

        txPlaySound ("Wall.wav");
        }

    if (*x1 <= *x + 140 && *x <= *x1 && *y - r <= *y1)
        {
        *vy = - *vy;
        *y1 = *y  - r;

        txPlaySound ("Point.wav");
        }

    if (*y1 < 0 + r)
        {
        *vy = - *vy;
        *y1 = *y1 - 2 * (*y1 - r);

        txPlaySound ("Wall.wav");
        }

    if (txGetAsyncKeyState ('1')) *dt = 1;
    if (txGetAsyncKeyState ('2')) *dt = 2;
    if (txGetAsyncKeyState ('3')) *dt = 3;
    }

void Rectangle (int* x, int* y)
    {
    txSetColor (RGB (218, 165, 32));
    txSetFillColor (RGB (218, 165, 32));

    txRectangle (*x, *y, *x + 140, *y + 40);

    if (*x + 140 > WindowWidth - 300) *x = WindowWidth - 140 - 300;
    if (*x < 0 + 300) *x = 0 + 300;

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
