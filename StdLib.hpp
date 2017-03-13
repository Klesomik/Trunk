void System (const char* cmd, ...);

void System (const char* cmd, ...)
{
    const size_t size = 1000;

    char result[size] = "";

    va_list args;

    va_start (args, cmd);

    vsprintf (result, cmd, args);

    va_end (args);

    system (result);
}
