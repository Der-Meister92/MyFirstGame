#include "TXLib.h"

const int WindowWidth  = 1280,
          WindowHeight = 720,
          SleepTime    = 1;

const HDC MainMenu = txLoadImage ("Pictures/Main_menu.bmp");
const HDC Buttons = txLoadImage ("Pictures/Buttons.bmp");
const HDC Control  = txLoadImage ("Pictures/Control.bmp");
const HDC Score  = txLoadImage ("Pictures/Background&Score.bmp");
const HDC Background  = txLoadImage ("Pictures/Background.bmp");
const HDC BackToMenu  = txLoadImage ("Pictures/PressSpace.bmp");
const HDC Cat = txLoadImage ("Pictures/Cat.bmp");

void MenuButtons (double CenterX, double CenterY, double ButtonsX, double ButtonsY, double MinXButtons,
                  double MaxXButtons, double MinYNewGame, double MaxYNewGame, double MaxYControl,
                  double MaxYExitGame);
void Menu ();
//struct Coordinates
//    {
//    int x, y;
//    };
//struct Physics
//    {
//    int vx, vy, dt;
//    };
struct Ball
    {
//    Coordinates Rectangle;
//    Coordinates Circle;
//    Physics ball;
    int x,  y,
         x1, y1,
         vx, vy,
         dt, r,
         k;

    void MoveBall ();
    void Rectangle ();
    void Score ();
    };

void GameOverText ();
void MiniGame ();

int main ()
    {
    txCreateWindow (WindowWidth, WindowHeight);
    txClear ();

    Menu ();
    return 0;
    }

void MenuButtons (double CenterX, double CenterY, double ButtonsX, double ButtonsY, double MinXButtons,
           double MaxXButtons, double MinYNewGame, double MaxYNewGame, double MaxYControl,
           double MaxYExitGame)
    {
    txPlaySound ("Audio/MainMenu/Sound.wav");
    int t = 0;
    int exit = 0;
    txBegin ();
    while (exit < 1)
        {
        txClear ();
        txBitBlt (txDC (), 0, 0, 0, 0, MainMenu, 0, 0);

        int CatX = txGetExtentX (Cat)/4,
            CatY = txGetExtentY (Cat)/8;

        if (MinXButtons <= txMouseX () && txMouseX () <= MaxXButtons &&
            MinYNewGame <= txMouseY () && txMouseY () <= MaxYNewGame)
            {
            txTransparentBlt (txDC (), CenterX - ButtonsX/2, CenterY - ButtonsY*1.5, ButtonsX, ButtonsY,
                              Buttons, ButtonsX, 0, RGB (250, 249, 244));
            if (txMouseButtons () == 1)
                {
                    MiniGame ();
                }
            }

        else txTransparentBlt (txDC (), CenterX - ButtonsX/2, CenterY - ButtonsY*1.5, ButtonsX, ButtonsY,
                               Buttons, 0, 0, RGB (250, 249, 244));

        if (MinXButtons <= txMouseX () && txMouseX () <= MaxXButtons &&
            MaxYNewGame <= txMouseY () && txMouseY () <= MaxYControl)
            {
            txTransparentBlt (txDC (), CenterX - ButtonsX/2, CenterY - ButtonsY/2, ButtonsX, ButtonsY,
                              Buttons, ButtonsX, ButtonsY, RGB (250, 249, 244));
            if (txMouseButtons () == 1)
                {
                t = 0;
                while (! txGetAsyncKeyState (VK_ESCAPE))
                    {
                    txBitBlt (txDC (), 0, 0, 0, 0, Control, 0, 0);

                    if (t <= 179)
                        txTransparentBlt (txDC (), 900, -30 + t*3, CatX, CatY, Cat,
                                          CatX * (((t / 10) % 2) + 2),   0,        RGB (255, 255, 255));

                    if (179 < t && t <= 259)
                        txTransparentBlt (txDC (), 900, 530,       CatX, CatY, Cat,
                                          CatX * (((t - 180) / 20) % 2), 0,        RGB (255, 255, 255));

                    if (259 < t && t <= 299)
                        txTransparentBlt (txDC (), 900, 530,       CatX, CatY, Cat,
                                          CatX * (((t - 260) / 10) % 4), CatY * 4, RGB (255, 255, 255));

                    if (299 < t && t <= 379)
                        txTransparentBlt (txDC (), 900, 530,       CatX, CatY, Cat,
                                          CatX * (((t - 300) / 10) % 4), CatY * 5, RGB (255, 255, 255));

                    if (379 < t && t <= 449)
                        txTransparentBlt (txDC (), 900, 530,       CatX, CatY, Cat,
                                          CatX * 2,                      CatY * 4, RGB (255, 255, 255));

                    if (449 < t && t <= 649)
                        txTransparentBlt (txDC (), 900, 530 - (t - 449)*3, CatX, CatY, Cat,
                                          CatX * ((((t - 450) / 10) % 2) + 2), CatY * 2, RGB (255, 255, 255));

                    if (t == 700) t = 0;

                    t++;
                    txSleep (SleepTime);
                    }
                }
            }

        else txTransparentBlt (txDC (), CenterX - ButtonsX/2, CenterY - ButtonsY/2, ButtonsX, ButtonsY,
                               Buttons, 0, ButtonsY, RGB (250, 249, 244));

        if (MinXButtons <= txMouseX () && txMouseX () <= MaxXButtons &&
            MaxYControl <= txMouseY () && txMouseY () <= MaxYExitGame)
            {
            txTransparentBlt (txDC (), CenterX - ButtonsX/2, CenterY + ButtonsY/2, ButtonsX, ButtonsY,
                              Buttons, ButtonsX, ButtonsY*2, RGB (250, 249, 244));
            if (txMouseButtons () == 1)
                {
                exit = 1;
                }
            }

        else txTransparentBlt (txDC (), CenterX - ButtonsX/2, CenterY + ButtonsY/2, ButtonsX, ButtonsY,
                               Buttons, 0, ButtonsY*2, RGB (250, 249, 244));

        if (t <= 149)
            txTransparentBlt (txDC (), 0 + t, 540, CatX, CatY, Cat,
                              CatX * (((t / 10) % 2) + 2), CatY,     RGB (255, 255, 255));

        if (149 < t && t <= 189)
            txTransparentBlt (txDC (), 149,   540, CatX, CatY, Cat, CatX * (((t - 150) / 10) % 4),
                              CatY * 6, RGB (255, 255, 255));

        if (189 < t && t <= 199)
            txTransparentBlt (txDC (), 149,   540, CatX, CatY, Cat, CatX * 3,
                              CatY * 6, RGB (255, 255, 255));

        if (199 < t && t <= 399)
            txTransparentBlt (txDC (), 149,   540, CatX, CatY, Cat, CatX * ((((t - 200) / 20) % 2) + 2),
                              CatY * 6, RGB (255, 255, 255));

        if (399 < t && t <= 479)
            txTransparentBlt (txDC (), 149,   540, CatX, CatY, Cat, CatX * (((t - 400) / 10) % 4),
                              CatY * 5, RGB (255, 255, 255));

        if (479 < t && t <= 509)
            txTransparentBlt (txDC (), 149, 540, CatX, CatY, Cat, CatX * 2,
                              CatY * 4, RGB (255, 255, 255));

        if (509 < t && t <= 809)
            txTransparentBlt (txDC (), 149 - (t - 509), 540, CatX, CatY, Cat,
                              CatX * ((((t - 510) / 10) % 2) + 2), CatY * 3, RGB (255, 255, 255));

        if (t == 860) t = 0;

        t++;
        txSleep (SleepTime);
        }
    txEnd ();
    txPlaySound (NULL);
    }

void Menu ()
    {
    double CenterX = WindowWidth/2,
           CenterY = WindowHeight/2;

    double ButtonsX = txGetExtentX (Buttons) / 2,
           ButtonsY = txGetExtentY (Buttons) / 3;

    double MinXButtons  = CenterX - ButtonsX/2,
           MaxXButtons  = CenterX + ButtonsX/2;

    double MinYNewGame  = CenterY - ButtonsY*1.5,
           MaxYNewGame  = CenterY - ButtonsY/2,
           MaxYControl  = CenterY + ButtonsY/2,
           MaxYExitGame = CenterY + ButtonsY*1.5;

    MenuButtons (CenterX, CenterY, ButtonsX, ButtonsY, MinXButtons, MaxXButtons, MinYNewGame,
                 MaxYNewGame, MaxYControl, MaxYExitGame);

    txDeleteDC (MainMenu);
    txDeleteDC (Buttons);
    txDeleteDC (Background);
    txDeleteDC (Cat);
    }

void Ball::MoveBall ()
    {
    txSetColor (RGB (223, 192, 110));
    txSetFillColor (RGB (223, 192, 110));

    txCircle (x1, y1, r);

    x1 += vx * dt;
    y1 -= vy * dt;

    if (x1 > WindowWidth - 202  - r)
        {
        vx = - vx;
        x1 = x1 - 2 * (x1 - WindowWidth + 202  + r);

        txPlaySound ("Audio/Game/Wall.wav");
        }

    if (x1 < 0 + 202 + r)
        {
        vx = - vx;
        x1 = x1 - 2 * (x1 - 202 - r);

        txPlaySound ("Audio/Game/Wall.wav");
        }

    if (x1 <= x + 140 && x <= x1 && y - r <= y1 && y1 <= y + 8)
        {
        vy = - vy;
        y1 = y  - r;
        k+=dt-2;

        txPlaySound ("Audio/Game/Point.wav");
        }

    if (y1 < 0 + r)
        {
        vy = - vy;
        y1 = y1 - 2 * (y1 - r);

        txPlaySound ("Audio/Game/Wall.wav");
        }

    if (txGetAsyncKeyState ('1'))
        {
        dt = 3;
        r = 50;
        }

    if (txGetAsyncKeyState ('2'))
        {
        dt = 4;
        r = 40;
        }

    if (txGetAsyncKeyState ('3'))
        {
        dt = 5;
        r = 30;
        }
    }

void Ball::Rectangle ()
    {
    txSetColor (RGB (223, 192, 110));
    txSetFillColor (RGB (223, 192, 110));

    txRectangle (x, y, x + 140, y + 40);

    if (x + 140 > WindowWidth - 202) x = WindowWidth - 140 - 202;
    if (x < 0 + 202) x = 0 + 202;

    if (txGetAsyncKeyState (VK_RIGHT)) x += 30;
    if (txGetAsyncKeyState (VK_LEFT))  x -= 30;
    }

void Ball::Score ()
    {
    txSetTextAlign (TA_CENTER);
    txSelectFont ("Arial Black", 100);

    char score [5] = "";
    sprintf (score, "%d", k);

    txSetColor (TX_WHITE);
    txSetFillColor (TX_WHITE);
    txRectangle (32, 210, 170, 285);

    txSetColor (RGB (139, 109, 31));
    txDrawText (32, 210, 170, 285, score);
    }

void GameOverText ()
    {
    txSetTextAlign (TA_CENTER);
    txSelectFont ("Arial Black", 180);

    int CenterX = WindowWidth/2,
        CenterY = WindowHeight/2;

    int textSizeX = txGetTextExtentX ("GAME OVER"),
        textSizeY = txGetTextExtentY ("GAME OVER");

    txSetColor (TX_RED);

    txDrawText (CenterX - textSizeX/2, CenterY - textSizeY/2,
                CenterX + textSizeX/2, CenterY + textSizeY/2, "GAME OVER");
    }

void MiniGame ()
    {
    Ball ball1 = {0, 600, 600, 200, 5, 3, 3, 50, 0};

    txBegin ();
    while (ball1.y1 <= WindowHeight + ball1.r)
        {
        if (txGetAsyncKeyState (VK_ESCAPE))
            {
            if (txMessageBox ("Если выйдешь из игры, то весь прогресс коту под хвост!") == IDOK)
                {
                break;
                }
            }

        txSetFillColor (TX_WHITE);
        txClear ();

        txBitBlt  (txDC(), 0, 0, WindowWidth, WindowHeight, Score, 0, 0);

        ball1.MoveBall ();
        ball1.Rectangle ();
        ball1.Score ();

        txSleep (SleepTime);
        }

        txPlaySound ("Audio/Game/GameOver.wav");
        int t = 0;
        while (t <= 10)
            {
            txBitBlt  (txDC(), 0, 0, WindowWidth, WindowHeight, Background, 0, 0);
            GameOverText ();
            t++;
            txSleep (SleepTime);
            }
            txSetFillColor (TX_BLACK);

        double CenterX = WindowWidth/2,
               CenterY = WindowHeight/2;

        while (t<=12)
            {
            txTransparentBlt (txDC (), CenterX - 226, CenterY + 100, 0, 0,
                               BackToMenu, 0, 0, RGB (255, 255, 255));
            t++;
            txSleep (SleepTime);
            }
        while (! txGetAsyncKeyState (VK_SPACE))
            {
            txRectangle (600, 350, 680, 370);
            txBitBlt (txDC (), 0, 0, 0, 0, MainMenu, 0, 0);
            }

       txPlaySound ("Audio/MainMenu/Sound.wav");

    txEnd ();
    }
