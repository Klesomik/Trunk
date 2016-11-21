#include <iostream>
#include <cmath>
#include <array>

//TODO: two constructs (TypeOfData, Iterators)

namespace Math
{
    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    class Point
    {
        public:
            Point ();
            Point (const Point <Data_T, Measurements>& from);

            template <typename Iterator_T>
            Point (const Iterator_T& begin, const Iterator_T& end);

            bool ok ();
            void dump ();

            Data_T& operator [] (const size_t place);
            Point& operator = (const Point <Data_T, Measurements>& from);

            Container_T& coords ();

        protected:
            Container_T coords_;
    };

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    double_t distance (const Math::Point <Data_T, Measurements>& from, const Math::Point <Data_T, Measurements>& to);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    void swap (Math::Point <Data_T, Measurements>& from, Math::Point <Data_T, Measurements>& to);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    bool operator == (const Math::Point <Data_T, Measurements>& from, const Math::Point <Data_T, Measurements>& to);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    bool operator != (const Math::Point <Data_T, Measurements>& from, const Math::Point <Data_T, Measurements>& to);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    std::istream& operator >> (std::istream& in, Math::Point <Data_T, Measurements>& value);

    template <typename Data_T, size_t Measurements, typename Container_T = std::array <Data_T, Measurements>>
    std::ostream& operator << (std::ostream& out, Math::Point <Data_T, Measurements>& value);

    typedef Point <   int, 2> PointI2;
    typedef Point < float, 2> PointF2;
    typedef Point <double, 2> PointD2;

    typedef Point <   int, 3> PointI3;
    typedef Point < float, 3> PointF3;
    typedef Point <double, 3> PointD3;

    typedef Point <   int, 4> PointI4;
    typedef Point < float, 4> PointF4;
    typedef Point <double, 4> PointD4;
}

template <typename Data_T, size_t Measurements, typename Container_T>
Math::Point <Data_T, Measurements, Container_T>::Point ():
    coords_ ()
{
}

template <typename Data_T, size_t Measurements, typename Container_T>
Math::Point <Data_T, Measurements, Container_T>::Point (const Point <Data_T, Measurements>& from):
    coords_ ()
{
    std::copy (from.coords_.begin (), from.coords_.end (), coords_.begin ());
}

template <typename Data_T, size_t Measurements, typename Container_T>
Math::Point <Data_T, Measurements, Container_T>::Point (const Iterator_T& begin, const Iterator_T& end):
    coords_ ()
{
    std::copy (begin, end, coords_.begin ());
}

template <typename Data_T, size_t Measurements, typename Container_T>
Data_T& Math::Point <Data_T, Measurements, Container_T>::operator [] (const size_t place)
{
    return *(coords_.begin () + place);
}

template <typename Data_T, size_t Measurements, typename Container_T>
Math::Point <Data_T, Measurements, Container_T>& Math::Point <Data_T, Measurements, Container_T>::operator = (const Point <Data_T, Measurements>& from)
{
    std::copy (from.coords_.begin (), from.coords_.end (), coords_.begin ());

    return (*this);
}

template <typename Data_T, size_t Measurements, typename Container_T>
Container_T& Math::Point <Data_T, Measurements, Container_T>::coords ()
{
    return coords_;
}

template <typename Data_T, size_t Measurements, typename Container_T>
double_t Math::distance (const Math::Point <Data_T, Measurements>& from, const Math::Point <Data_T, Measurements>& to)
{
    double_t result = 0;

    for (size_t i = 0; i < Measurements; i++)
        result += pow (from[i] - to[i], 2);

    return sqrt (result);
}

template <typename Data_T, size_t Measurements, typename Container_T>
void Math::swap (Math::Point <Data_T, Measurements>& from, Math::Point <Data_T, Measurements>& to)
{
}

template <typename Data_T, size_t Measurements, typename Container_T>
bool Math::operator == (const Math::Point <Data_T, Measurements>& from, const Math::Point <Data_T, Measurements>& to)
{
    for (size_t i = 0; i < Measurements; i++)
    {
        if (from[i] != to[i])
            return false;
    }

    return true;
}

template <typename Data_T, size_t Measurements, typename Container_T>
bool Math::operator != (const Math::Point <Data_T, Measurements>& from, const Math::Point <Data_T, Measurements>& to)
{
    return !(from == to);
}

template <typename Data_T, size_t Measurements, typename Container_T>
std::istream& Math::operator >> (std::istream& in, Math::Point <Data_T, Measurements>& value)
{
    for (size_t i = 0; i < Measurements; i++)
        in >> value[i];

    return in;
}

template <typename Data_T, size_t Measurements, typename Container_T>
std::ostream& Math::operator << (std::ostream& out, Math::Point <Data_T, Measurements>& value)
{
    for (size_t i = 0; i < Measurements; i++)
        out << value[i] << " ";

    return out;
}
