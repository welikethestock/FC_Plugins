// todo: walk command list.

#include "Util/Macros.hpp"
#include "Game/Command.hpp"

struct CommandDescriptor
{
    void                *VMT;           // 0x00
    unsigned int        Unk1;           // 0x08
    char                Pad1[4];        // 0x0C
    const char          *Description;   // 0x10
    const char          *MaybePrefix;   // 0x18
};

struct Command
{
    void                *VMT;           // 0x00 
    char                Pad[0x18];      // 0x08
    CommandDescriptor   *Descriptor;    // 0x20
    SDK::Command::Value Value;          // 0x28
};

EXPORT_C
SDK_FUNCTION(Command *, Command, GetCommand, const char *Name)
{
    return NULL;
}

EXPORT_C
SDK_FUNCTION(const char *, Command, GetDescription, Command *Cmd)
{
    return Cmd->Descriptor->Description;
}

EXPORT_C
SDK_FUNCTION(SDK::Command::Value &, Command, GetValue, Command *Cmd)
{
    return Cmd->Value;
}