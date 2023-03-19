#include <windows.h>
#include <psapi.h>
#include <string.h>

static 
size_t GetModuleSize(HMODULE Module)
{
    MODULEINFO Info;
    GetModuleInformation(GetCurrentProcess(), Module, &Info, sizeof(MODULEINFO));

    return Info.SizeOfImage;
}

extern "C" __declspec(dllexport)
void *SDK_Util_FindSignature(HMODULE Module, const char *Signature, const char *Mask)
{
    if(Module == NULL)
    {
        return NULL;
    }

    size_t SignatureLength  = strlen(Mask);
    size_t ModuleSize       = GetModuleSize(Module);
    char *Address           = (char *)(Module);

    do
    {
        for(int Index = 0; Index < SignatureLength; ++Index)
        {
            if(Mask[Index] == '?')
            {
                continue;
            }

            if(*(Address + Index) != Signature[Index])
            {
                break;
            }

            if(Index == (SignatureLength - 1))
            {
                return (void *)(Address);
            }
        }

        ++Address;
    } while(--ModuleSize);

    return NULL;
}