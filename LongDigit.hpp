#include <bits/stdc++.h>

class LongDigit
{
    public:
        LongDigit ();
        LongDigit (const int from);
        LongDigit (const LongDigit &from);

        LongDigit& operator = (const int from);
        LongDigit& operator = (const LongDigit &from);

        LongDigit& operator += (const LongDigit &from);
        LongDigit& operator -= (const LongDigit &from);
        LongDigit& operator *= (LongDigit &from);
        LongDigit& operator /= (const LongDigit &from);

        void normalize ();

        std::vector<int>& data ();

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

LongDigit::LongDigit (const LongDigit &from):
    data_ ()
{
    (*this) = from;
}

LongDigit& LongDigit::operator = (const int from)
{
    data_.resize ((int) log10 (from) + 1);

    for (int i = 0, value = from; value > 0; value /= 10, i++)
        data_[i] = value % 10;

    return (*this);
}

LongDigit& LongDigit::operator = (const LongDigit &from)
{
    data_.resize (from.data_.size ());

    for (int i = 0; i < (int) from.data_.size (); i++)
        data_[i] = from.data_[i];

    return (*this);
}

LongDigit& LongDigit::operator += (const LongDigit &from)
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
	int buffer = 0;

	for (int i = 0; (i < from.data_.size ()) || (buffer == 1); i++)
	{
		data_[i] -= buffer + (i < from.data_.size ()? from.data_[i] : 0);

		buffer = (data_[i] < 0);

		if (buffer)
			data_[i] += 10;
	}

	normalize ();

    return (*this);
}

LongDigit& LongDigit::operator *= (LongDigit& from)
{
	LongDigit result;

	result.data ().resize (data_.size () + from.data ().size ());

	for (int i = 0; i < from.data_.size (); i++)
	{
		int buffer = 0;

		for (int j = 0; (j < data_.size ()) || (buffer > 0); j++)
		{
			int value = result.data ()[i + j] + buffer + from.data_[i] * (j < data_.size ()? data_[j] : 0);

			result.data ()[i + j] = value % 10;

			buffer = value / 10;
		}
	}

	(*this) = result;

	normalize ();

    return (*this);
}

LongDigit& LongDigit::operator /= (const LongDigit& from)
{
    return (*this);
}

void LongDigit::normalize ()
{
	while ((!data_.empty ()) && (data_.back () == 0))
		data_.pop_back ();
}

std::vector<int>& LongDigit::data ()
{
	return data_;
}

bool operator == (LongDigit &first, LongDigit &second);
bool operator != (LongDigit &first, LongDigit &second);
bool operator < (LongDigit &first, LongDigit &second);
bool operator <= (LongDigit &first, LongDigit &second);
bool operator > (LongDigit &first, LongDigit &second);
bool operator >= (LongDigit &first, LongDigit &second);

std::ostream& operator << (std::ostream &out, LongDigit &result);
std::istream& operator >> (std::istream &in, LongDigit &result);

bool operator == (LongDigit &first, LongDigit &second)
{
	if (first.data ().size () != second.data ().size ())
		return false;

	for (int i = 0; i < first.data ().size (); i++)
		if (first.data ()[i] != second.data ()[i])
			return false;

	return true;
}

bool operator != (LongDigit &first, LongDigit &second)
{
	return !(first == second);
}

bool operator < (LongDigit &first, LongDigit &second)
{
	if (first.data ().size () != second.data ().size ())
		return first.data ().size () < second.data ().size ();

	for (int i = first.data ().size () - 1; i >= 0; i--)
		if (first.data ()[i] != second.data ()[i])
			return first.data ()[i] < second.data ()[i];

	return false;
}

bool operator <= (LongDigit &first, LongDigit &second)
{
	return (first == second) || (first < second);
}

bool operator > (LongDigit &first, LongDigit &second)
{
	return !(first <= second);
}

bool operator >= (LongDigit &first, LongDigit &second)
{
	return (first == second) || (first > second);
}

std::ostream& operator << (std::ostream &out, LongDigit &result)
{
	if (result.data ().empty ())
		out << 0;

	else
	{
		for (int i = result.data ().size () - 1; i >= 0; i--)
			out << result.data ()[i];
	}

	return out;
}

std::istream& operator >> (std::istream &in, LongDigit &result)
{
	std::string buffer;
	in >> buffer;

	std::reverse (buffer.begin (), buffer.end ());

	result.data ().clear ();
	result.data ().resize (buffer.size ());

	for (int i = 0; i < result.data ().size (); i++)
		result.data ()[i] = (buffer[i] - '0');

	return in;
}
