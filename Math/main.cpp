#include "C:/Users/Artem/Desktop/TX/TXLibNew.h"
#include "Vector.hpp"

const int size_x = 800, size_y = 600;

struct Piston
{
    Math::VectorD2 left, right, speed;

    double mass;

    COLORREF color;

    Piston ();

    void render ();
    void move ();
    void control ();
};

Piston::Piston ():
    left  ({ 100, size_y }),
    right ({ 130, 0 }),
    speed ({ 10, 0 }),
    mass  (1000),
    color (TX_GRAY)
{
}

void Piston::render ()
{
    txSetColor (color);
    txSetFillColor (color);

    txRectangle (left[0], left[1], right[0], right[1]);
}

void Piston::move ()
{
    left += speed;
    right += speed;

    if (left[0] < 0)
    {
        right[0] += (0 - left[0]);
        left[0] = 0;

        speed = -speed;
    }

    if (right[0] > size_x)
    {
        left[0] -= (right[0] - size_x);
        right[0] = size_x;

        speed = -speed;
    }
}

void Piston::control ()
{
    if (GetAsyncKeyState (VK_UP))   speed[0] += 0.5;
    if (GetAsyncKeyState (VK_DOWN)) speed[0] -= 0.5;
}

struct Ball
{
    Ball ();
    Ball (double x, double y);
    Ball (Math::VectorD2& place);

    void render ();
    void move ();
    void control ();
    void crash (Piston& from);

    Math::VectorD2 coords_;
    Math::VectorD2 speed_;

    double radius_, mass_;

    COLORREF color_;
};

Ball::Ball ():
    coords_ (),
    speed_  (),
    radius_ (),
    mass_   (),
    color_  ()
{
    radius_ = random (2, 50);
    mass_   = random (2, 50);
    color_  = RGB (random (0, 255), random (0, 255), random (0, 255));
    coords_ = { random (0 + radius_, size_x - radius_), random (0 + radius_, size_y - radius_) };
    speed_  = { random (0, 5), random (0, 5) };
}

Ball::Ball (double x, double y):
    coords_ ({ x, y }),
    speed_  (),
    radius_ (),
    mass_   (),
    color_  ()
{
}

Ball::Ball (Math::VectorD2& place):
    coords_ ({ place[0], place[1] }),
    speed_  (),
    radius_ (),
    mass_   (),
    color_  ()
{
}

void Ball::render ()
{
    //COLORREF old_color = txGetColor ();

    txSetColor (color_);
    txSetFillColor (color_);

    txCircle (coords_[0], coords_[1], radius_);

    //txSetColor (old_color);
}

void Ball::move ()
{
    coords_ += speed_;

    if (coords_[0] - radius_ < 0)
    {
        coords_[0] = radius_;
         speed_[0] = -speed_[0];
    }

    if (coords_[1] - radius_ < 0)
    {
        coords_[1] = radius_;
         speed_[1] = -speed_[1];
    }

    if (coords_[0] + radius_ > size_x)
    {
        coords_[0] = size_x - radius_;
         speed_[0] = -speed_[0];
    }

    if (coords_[1] + radius_ > size_y)
    {
        coords_[1] = size_y - radius_;
         speed_[1] = -speed_[1];
    }
}

void Ball::crash (Piston& from)
{
    if (coords_[0] + radius_ < from.left[0])
        return;

    if (coords_[0] + radius_ > from.right[0])
        return;

    if (coords_[0] < from.left[0])
        coords_[0] = from.left[0] - radius_;

    else
        coords_[0] = from.right[0] + radius_;

    speed_ = -speed_;
}

void Ball::control ()
{
    Math::VectorD2 up    ({ 0, -0.1 }),
                   down  ({ 0, +0.1 }),
                   left  ({ -0.1, 0 }),
                   right ({ +0.1, 0 });

    if (GetAsyncKeyState (VK_UP))    speed_ += up;
    if (GetAsyncKeyState (VK_DOWN))  speed_ += down;
    if (GetAsyncKeyState (VK_LEFT))  speed_ += left;
    if (GetAsyncKeyState (VK_RIGHT)) speed_ += right;
}

void Init ();

int main ()
{
    Init ();

    std::vector <Ball> data (20);

    Piston from;

    while (!GetAsyncKeyState (VK_ESCAPE))
    {
        txSetColor (TX_BLACK);
        txSetFillColor (TX_BLACK);

        txClear ();

        from.render ();

        for (int i = 0; i < data.size (); i++)
            data[i].render ();

        from.control ();

        from.move ();

        for (int i = 0; i < data.size (); i++)
            data[i].crash (from);

        for (int i = 0; i < data.size (); i++)
            data[i].move ();

        txSleep (25);
    }

    return 0;
}

void Init ()
{
    srand (time (nullptr));

    txCreateWindow (size_x, size_y);
    SetWindowText (txWindow (), "Moleculs");

    //_txExit = true;
}
