#include <stdio.h>
#include "SDK.hpp"

int main()
{
    constexpr auto Hash = SDK::Hash::Fnv1a32("ab"_CCS);

    switch(FNV1A32("hello"))
    {
        case SDK::Hash::Fnv1a32("hello"_CCS):
        {
            printf("epic\n");

            break;
        }
    }

    printf("Hello %s %p\n", 
        ("hello"_CCS).Get(), 
        Hash
    );

    return 0;
}