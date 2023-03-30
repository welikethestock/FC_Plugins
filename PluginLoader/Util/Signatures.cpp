#include <windows.h>
#include <psapi.h>
#include <string.h>
#include "Util/Macros.hpp"

static 
size_t GetModuleSize(HMODULE Module)
{
    MODULEINFO Info;
    GetModuleInformation(GetCurrentProcess(), Module, &Info, sizeof(MODULEINFO));

    return Info.SizeOfImage;
}

EXPORT_C
SDK_FUNCTION(void *, Signature, Find, HMODULE Module, const char *Signature, const char *Mask)
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
        for(size_t Index = 0; Index < SignatureLength; ++Index)
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

extern "C"
{
#include "nmd/assembly/nmd_assembly.h"
}

#define _LOG_HACK
#include "Util/Log.hpp"

#include <string>

EXPORT_C
SDK_FUNCTION(size_t, Signature, Create, void *Address, int Length, char *SignatureBuffer, char *MaskBuffer)
{
    size_t              SignatureLength = 0;
    char                *Buffer         = (char *)(Address);
    nmd_x86_instruction Instruction;

    std::string Pattern = "";
    std::string Mask = "";
    
    while(Length > 0 && nmd_x86_decode(Buffer, Length, &Instruction, NMD_X86_MODE_64, NMD_X86_DECODER_FLAGS_ALL) && Length > SignatureLength)
    {
        int OpCodeIndex = 0;

        for(int Index = 0; Index < Instruction.opcode_size; ++Index)
        {
            char ByteBuffer[8];
            snprintf(ByteBuffer, sizeof(ByteBuffer), "\\x%02X", ((uint64_t)(Instruction.buffer[OpCodeIndex]) & 0xFF));

            Mask += "x";
            Pattern += ByteBuffer;

            ++OpCodeIndex;
        }

        int InstructionLength = Instruction.length - Instruction.opcode_size;
        for(int Index = 0; (Index < Instruction.num_operands) && (InstructionLength > 0); ++Index)
        {
            auto &Operand = Instruction.operands[Index];
            switch(Operand.type)
            {
                case NMD_X86_OPERAND_TYPE_MEMORY:
                {
                    int _InstructionLength = InstructionLength;
                    for(int Index = 0; Index < (_InstructionLength > 5 ? 5 : _InstructionLength); ++Index)
                    {
                        Mask += '?';
                        Pattern += "\\x00";

                        --InstructionLength;
                        ++OpCodeIndex;
                    }

                    break;
                }

                case NMD_X86_OPERAND_TYPE_IMMEDIATE:
                {
                    int _InstructionLength = InstructionLength;
                    for(int Index = 0; Index < _InstructionLength; ++Index)
                    {
                        Mask += '?';
                        Pattern += "\\x00";

                        --InstructionLength;
                        ++OpCodeIndex;
                    }

                    break;
                }

                default:
                {
                    char ByteBuffer[8];
                    snprintf(ByteBuffer, sizeof(ByteBuffer), "\\x%02X", ((uint64_t)(Instruction.buffer[OpCodeIndex]) & 0xFF));

                    Mask += 'x';
                    Pattern += ByteBuffer;

                    --InstructionLength;
                    ++OpCodeIndex;

                    break;
                }
            }
        }

        Buffer += Instruction.length;
        SignatureLength += Instruction.length;
        Length -= Instruction.length;
    }

    SDK::Log::Message("%s %s\n", Pattern.c_str(), Mask.c_str());

    SignatureBuffer[SignatureLength] = MaskBuffer[SignatureLength] = '\0';
    return SignatureLength;
}