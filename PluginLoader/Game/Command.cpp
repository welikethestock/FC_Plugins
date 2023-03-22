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

SDK_FUNCTION(Command, GetCommand, Command *, const char *Name)
{
    return NULL;
}

SDK_FUNCTION(Command, GetDescription, const char *, Command *Cmd)
{
    return Cmd->Descriptor->Description;
}

SDK_FUNCTION(Command, GetValue, SDK::Command::Value &, Command *Cmd)
{
    return Cmd->Value;
}