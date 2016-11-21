template <typename Type = std::vector <int>>
class LongDigit
{
    public:
        LongDigit (const std::string from = "");
        LongDigit (const LongDigit& from);

        LongDigit& operator + (const int digit);

    private:
        Type data_;
};

LongDigit::LongDigit (const std::string from):
    data_ (from.size ())
{
    std::copy (from.begin (), from.end (), data_);
}

LongDigit::LongDigit (const LongDigit& from):
    data_ (from.data_.size ())
{
    std::copy (from.data_.begin (), from.data_.end (), data_);
}

LongDigit& LongDigit::operator + (const int digit)
{
    int buffer = 0;

    for (int i = data_.size () - 1; i >= 0; i--)
    {
    }
}
