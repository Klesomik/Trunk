#include "TXLib.h"
#include "TXAddition.hpp"
#include "Vector.hpp"

void DrawVector (Math::VectorD2& car, Math::VectorD2& next);

int main ()
{
    txCreateWindow (800, 600);

    Math::VectorD2 car ({ 100, 50 });

    //txSetCursor (false);

    Math::VectorD2 up    ({   0, -50 }),
                   down  ({   0, +50 }),
                   left  ({ -50,   0 }),
                   right ({ +50,   0 }),
                   start ({   0,   0 });

    while (true)
    {
        txBegin ();

        Math::VectorD2 path;

        txSetColor (TX_BLACK);
        txSetFillColor (TX_BLACK);

        txClear ();

        if (GetAsyncKeyState (VK_UP))
        {
            car[1] -= 1;

            path += up;
        }

        if (GetAsyncKeyState (VK_DOWN))
        {
            car[1] += 1;

            path += down;
        }

        if (GetAsyncKeyState (VK_LEFT))
        {
            car[0] -= 1;

            path += left;
        }

        if (GetAsyncKeyState (VK_RIGHT))
        {
            car[0] += 1;

            path += right;
        }

        if (GetAsyncKeyState (VK_SHIFT))
        {
            DrawVector (start, car);
        }

        DrawVector (car, path);

        txSetColor (TX_WHITE);

        adTextOut (600, 550, "%lg", sqrt (car[0] * car[0] + car[1] * car[1]));

        txSetColor (TX_GREEN);
        txSetFillColor (TX_GREEN);

        txCircle (car[0], car[1], 5);

        txEnd ();
    }

    return 0;
}

void DrawVector (Math::VectorD2& car, Math::VectorD2& next)
{
    txSetColor (TX_YELLOW);

    txLine (car[0], car[1], car[0] + next[0], car[1] + next[1]);
}
