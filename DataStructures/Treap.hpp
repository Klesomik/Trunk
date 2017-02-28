//namespace Trunk
template <typename Data_T>
class Treap
{
    public:
        Treap ();
        Treap (const Data_T& setX, const Data_T& setY);

        void merge ();
        void split (const Data_T& cut);

        Data_T& x ();
        Data_T& y ();

        Treap* left ();
        Treap* right ();

    private:
        Data_T x_, y_;

        Treap* left_;
        Treap* right_;
};

template <typename Data_T>
Treap <Data_T>::Treap ():
    x_     (),
    y_     (),
    left_  (nullptr),
    right_ (nullptr)
{
}

template <typename Data_T>
Treap <Data_T>::Treap (const Data_T& setX, const Data_T& setY):
    x_     (setX),
    y_     (setY),
    left_  (nullptr),
    right_ (nullptr)
{
}

template <typename Data_T>
void Treap <Data_T>::merge ()
{
}

template <typename Data_T>
void Treap <Data_T>::split (const Data_T& cut)
{
}

template <typename Data_T>
Data_T& Treap <Data_T>::x ()
{
    return x_;
}

template <typename Data_T>
Data_T& Treap <Data_T>::y ()
{
    return y_;
}

template <typename Data_T>
Treap <Data_T>* Treap <Data_T>::left ()
{
    return left_;
}

template <typename Data_T>
Treap <Data_T>* Treap <Data_T>::right ()
{
    return right_;
}
