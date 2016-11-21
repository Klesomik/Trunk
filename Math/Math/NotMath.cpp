#include "TXLib.h"
#include "VectorNew.hpp"

const size_t size_x = 800, size_y = 600;

class Ball
{
    public:
        Ball ();

        void draw ();
        void move ();
        void control ();

        Math::VectorD2& coords ();
        Math::VectorD2& speed ();
        double& mass ();

    private:
        Math::VectorD2 coords_;
        Math::VectorD2 speed_;

        double mass_;

        COLORREF color_;
};

Ball::Ball ():
    coords_ (),
    speed_ (),
    mass_ (),
    color_ ()
{
    coords_[0] = random (0 + mass_, size_x - mass_);
    coords_[1] = random (0 + mass_, size_y - mass_);

    mass_ = random (5, 70);

    color_ = RGB (random (0, 255), random (0, 255), random (0, 255));
}

void Ball::draw ()
{
    txSetColor (color_);
    txSetFillColor (color_);

    txCircle (coords_[0], coords_[1], mass_);
}

void Ball::move ()
{
    coords_ += speed_;

    if (coords_[0] - mass_ < 0)
    {
        coords_[0] = mass_;
         speed_[0] = -speed_[0];
    }

    if (coords_[1] - mass_ < 0)
    {
        coords_[1] = mass_;
         speed_[1] = -speed_[1];
    }

    if (coords_[0] + mass_ > size_x)
    {
        coords_[0] = size_x - mass_;
         speed_[0] = -speed_[0];
    }

    if (coords_[1] + mass_ > size_y)
    {
        coords_[1] = size_y - mass_;
         speed_[1] = -speed_[1];
    }
}

void Ball::control ()
{
    Math::VectorD2 up, down, left, right;

       up[0] = 0,    up[1] = -0.1;
     down[0] = 0,  down[1] = +0.1;
     left[0] = -0.1,  left[1] = 0;
    right[0] = +0.1, right[1] = 0;

    if (GetAsyncKeyState (VK_UP)) speed_ += up;
    if (GetAsyncKeyState (VK_DOWN)) speed_ += down;
    if (GetAsyncKeyState (VK_LEFT)) speed_ += left;
    if (GetAsyncKeyState (VK_RIGHT)) speed_ += right;
}

Math::VectorD2& Ball::coords ()
{
    return coords_;
}

Math::VectorD2& Ball::speed ()
{
    return speed_;
}

double& Ball::mass ()
{
    return mass_;
}

void Init ();
void ClearWindow (COLORREF color);
void MainWhile (std::vector <Ball>& atoms);
void Crash (Ball& from, Ball& to);

int main ()
{
    const size_t size = 5;

    Init ();

    std::vector <Ball> atoms (size);

    MainWhile (atoms);

    return 0;
}

void Init ()
{
    txCreateWindow (size_x, size_y);
    txTextCursor (false);
}

void ClearWindow (COLORREF color)
{
    txSetColor (color);
    txSetFillColor (color);

    txClear ();
}

void MainWhile (std::vector <Ball>& atoms)
{
    txBegin ();

    while (!GetAsyncKeyState (VK_ESCAPE))
    {
        ClearWindow (TX_BLACK);

        for (size_t i = 0; i < atoms.size (); i++)
        {
            atoms[i].control ();
            atoms[i].move ();

            for (size_t j = 0; j < atoms.size (); j++)
                Crash (atoms[i], atoms[j]);

            atoms[i].draw ();
        }

        txSleep (10);
    }

    txEnd ();
}

void Crash (Ball& from, Ball& to)
{
    double dist = sqrt (pow (from.coords ()[0] - to.coords ()[0], 2) + pow (from.coords ()[1] - to.coords ()[1], 2));

    if (dist < from.mass () + to.mass ())
    {
        std::swap (from.speed ()[0], to.speed ()[0]);
        std::swap (from.speed ()[1], to.speed ()[1]);
    }
}
