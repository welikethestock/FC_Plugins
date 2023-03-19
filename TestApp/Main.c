#include <windows.h>
#include <stdio.h>

int main()
{
    printf("hi\n");

    LoadLibraryA("Loader.dll");

    while(1)
    {
        Sleep(1);
    }

    return 0;
}