#include <vector>
#include <iostream>
#include <cmath>

class SegmentTree
{
    public:
        SegmentTree ();
        SegmentTree (const size_t size);

    private:
        std::vector <int> data_;
};

SegmentTree::SegmentTree ():
    data_ ()
{
}

SegmentTree::SegmentTree (const size_t size):
    data_ ((size_t) ceil (log2 (size)))
{
}
