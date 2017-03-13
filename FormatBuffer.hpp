#ifndef FormatBuffer_hpp

#define FormatBuffer_hpp

#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdarg>

class FormatBuffer
{
    public:
        FormatBuffer ();
        FormatBuffer (int set_indent, int set_space);

        ~FormatBuffer ();

        void increase ();
        void decrease ();

        void print (const char* cmd, ...);

		void to_file (const std::string& name);

        char* buffer ();
        int& indent ();
        int& space ();

    private:
        char* buffer_;

        int indent_;
        int space_;

        int pointer_;

        FormatBuffer (const FormatBuffer& from);
        FormatBuffer& operator = (const FormatBuffer& from);
};

FormatBuffer::FormatBuffer ():
    buffer_  (new char[1000]),
    indent_  (0),
    space_   (4),
    pointer_ (0)
{
}

FormatBuffer::FormatBuffer (int set_indent, int set_space):
    buffer_  (new char[1000]),
    indent_  (set_indent),
    space_   (set_space),
    pointer_ (0)
{
}

FormatBuffer::~FormatBuffer ()
{
	delete[] buffer_;
}

void FormatBuffer::increase ()
{
    indent_ += space_;
}

void FormatBuffer::decrease ()
{
    indent_ -= space_;
}

void FormatBuffer::print (const char* cmd, ...)
{
    std::string tmp (indent_, ' ');

    pointer_ += sprintf (buffer_ + pointer_, "%s", tmp.c_str ());

    va_list args;

    va_start (args, cmd);

    pointer_ += vsprintf (buffer_ + pointer_, cmd, args);

    va_end (args);
}

void FormatBuffer::to_file (const std::string& name)
{
    std::ofstream out (name);

	assert (out);

	out << buffer_;
}

char* FormatBuffer::buffer ()
{
    return buffer_;
}

int& FormatBuffer::indent ()
{
    return indent_;
}

int& FormatBuffer::space ()
{
    return space_;
}

#endif /* FormatBuffer_hpp */
