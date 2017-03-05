#include <bits/stdc++.h>

int Mod (int a, int b);
int GCD (int a, int b);
int LCM (int a, int b);

int Mod (int a, int b)
{
    return (a % b + b) % b;
}

int GCD (int a, int b)
{
    while (b != 0)
    {
        int tmp1 = b,
            tmp2 = Mod (a, b);

        a = tmp1;
        b = tmp2;
    }

    return abs (a);
}

int LCM (int a, int b)
{
    return a / GCD (a, b) * b;
}
