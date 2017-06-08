#include <bits/stdc++.h>

class LongDigit
{
    public:
        LongDigit ();
        LongDigit (const int from);
        LongDigit (const LongDigit& from);

        LongDigit& operator = (const LongDigit& from);

        LongDigit& operator += (const LongDigit& from);
        LongDigit& operator -= (const LongDigit& from);
        LongDigit& operator *= (const LongDigit& from);
        LongDigit& operator /= (const LongDigit& from);

        const std::vector <int>& data () const;

    private:
        std::vector <int> data_;
};

LongDigit::LongDigit ():
    data_ ()
{
}

LongDigit::LongDigit (const int from):
    data_ ()
{
    (*this) = from;
}

LongDigit::LongDigit (const LongDigit& from):
    data_ ()
{
    (*this) = from;
}

LongDigit& LongDigit::operator = (const int from)
{
    data_.resize ((int) log10 (from) + 1);

    for (int i = 0, value = from; value > 0; value /= 10, i++)
        data_[i] = from % 10;

    return (*this);
}

LongDigit& LongDigit::operator = (const LongDigit& from)
{
    data_.resize (from.data_.size ());

    for (int i = 0; i < (int) from.data_.size (); i++)
        data_[i] = from.data_[i];

    return (*this);
}

LongDigit& LongDigit::operator += (const LongDigit& from)
{
    data_.resize (std::max (data_.size (), from.data_.size ()));

    int buffer = 0;

    for (int i = 0; (i < std::min (data_.size (), from.data_.size ())) || (buffer == 1); i++)
    {
        if (i == data_.size ())
            data_.push_back (0);

        data_[i] += buffer + (i < from.data_.size ()? from.data_[i] : 0);

        buffer = (data_[i] >= 10? 1 : 0);

        if (buffer == 1)
            data_[i] -= 10;
    }

    return (*this);
}

LongDigit& LongDigit::operator -= (const LongDigit& from)
{
    return (*this);
}

LongDigit& LongDigit::operator *= (const LongDigit& from)
{
    return (*this);
}

LongDigit& LongDigit::operator /= (const LongDigit& from)
{
    return (*this);
}

const std::vector <int>& LongDigit::data () const
{
    return data_;
}
