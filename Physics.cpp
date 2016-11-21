#include "Math//VectorNew.hpp"
#include "TXLib.h"

class Ball
{
    public:
        Ball ();
        Ball (const Math::PointD2& set_coords, const Math::VectorD2& set_speed, double set_mass, COLORREF set_color);

        void draw ();
        void move ();

        Math::PointD2& coords ();
        Math::VectorD2& speed ();

    private:
        Math::PointD2 coords_;
        Math::VectorD2 speed_;

        double mass_;

        COLORREF color_;
};

Ball::Ball ():
    coords_ (),
    speed_  (),
    mass_   (100),
    color_  (TX_WHITE)
{
}

Ball::Ball (const Math::PointD2& set_coords, const Math::VectorD2& set_speed, double set_mass, COLORREF set_color):
    coords_ (set_coords),
    speed_  (set_speed),
    mass_   (set_mass),
    color_  (set_color)
{
    speed_[0] = 0;
    speed_[1] = 0;
}

void Ball::draw ()
{
    txSetColor (color_);
    txSetFillColor (color_);

    txCircle (coords_[0], coords_[1], mass_);
}

void Ball::move ()
{
    for (size_t i = 0; i < coords_.coords ().size (); i++)
        coords_[i] += speed_[i];
}

Math::PointD2& Ball::coords ()
{
    return coords_;
}

Math::VectorD2& Ball::speed ()
{
    return speed_;
}

int main ()
{
    txCreateWindow (800, 600);

    Math::VectorD2 n, m, p, q;
    n[0] = 0, n[1] = +10;
    m[0] = 0, m[1] = -10;
    p[0] = +10, p[1] = 0;
    q[0] = -10, q[1] = 0;

    std::map <int, Math::VectorD2> check = { {    VK_UP, n },
                                             {  VK_DOWN, m },
                                             { VK_RIGHT, p },
                                             {  VK_LEFT, q } };

    Math::PointD2 a;
    std::cin >> a;

    for (auto it = check.begin (); it != check.end (); it++)
    {
        $c;

        std::cout << (*it).second[0] << "\n";
    }

    Ball ball (a, Math::VectorD2 (), 100, TX_YELLOW);

    while (!GetAsyncKeyState (VK_ESCAPE))
    {
        for (auto it = check.begin (); it != check.end (); it++)
        {
            if (GetAsyncKeyState ((*it).first))
            {
                ball.speed () += (*it).second;

                $c;

                std::cout << (*it).second << "\n";
            }
        }

        txSetColor (TX_BLACK);
        txSetFillColor (TX_BLACK);

        txClear ();

        ball.draw ();
        ball.move ();

        txSleep (500);
    }

    return 0;
}
