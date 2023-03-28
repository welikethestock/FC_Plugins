#ifndef __SDK_UTIL_INTRINSICS__
#define __SDK_UTIL_INTRINSICS__

// intellisense hack for linux
#ifndef _MSC_VER
    #define     _MSC_VER
    #undef      __STDC_HOSTED__
    #include    <intrin.h>
    #undef      _MSC_VER
    #define     __STDC_HOSTED__ 1

    #define     _ReturnAddress() (*(void**)(_AddressOfReturnAddress()))
#else
    #include    <intrin.h>
#endif

#endif