#include <stdio.h>

extern "C" __declspec(dllexport)
void SDK_Util_Log(const char *Message)
{
    printf(Message);
}