BIN=/home/razor/msvc/bin/x64 . /home/razor/msvc-wine/msvcenv-native.sh

echo "Compiling dbdata.dll..."

clang   --target=x86_64-windows-msvc -Wl,/subsystem:windows,/DLL -O3 \
        -Wno-inline-new-delete -Wno-implicit-exception-spec-mismatch -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined \
        -I./../SDK \
        -flto -fuse-ld=lld -o dbdata.dll \
        -D_USRDLL -D_WINDLL \
        ../Proxy/DBData.cpp

echo "Compiling PluginLoader.dll..."

clang   --target=x86_64-windows-msvc -Wl,/subsystem:windows,/DLL -O3 \
        -Wno-inline-new-delete -Wno-implicit-exception-spec-mismatch -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined -Wno-format-security -Wno-return-type-c-linkage -Wno-writable-strings -Wno-format \
        -I./../SDK -I./.. \
        -flto -fuse-ld=lld -o PluginLoader.dll \
        -D_USRDLL -D_WINDLL \
        ../PluginLoader/DllMain.cpp ../PluginLoader/Plugins.cpp \
        ../PluginLoader/Util/Log.cpp ../PluginLoader/Util/Signatures.cpp \
        ../nmd/assembly/nmd_common.c ../nmd/assembly/nmd_x86_assembler.c ../nmd/assembly/nmd_x86_decoder.c \
        ../nmd/assembly/nmd_x86_formatter.c ../nmd/assembly/nmd_x86_ldisasm.c ../PluginLoader/Util/Disasm.cpp \
        ../PluginLoader/Util/Bytepatch.cpp ../PluginLoader/Util/Stubs.cpp ../PluginLoader/Util/Detours.cpp \
        ../PluginLoader/Game/Command.cpp

echo "Compiling HighPingKickFix.dll..."

clang   --target=x86_64-windows-msvc -Wl,/subsystem:windows,/DLL -O3 \
        -Wno-inline-new-delete -Wno-implicit-exception-spec-mismatch -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined \
        -I./../SDK \
        -flto -fuse-ld=lld -o HighPingKickFix.dll \
        -D_USRDLL -D_WINDLL \
        ../Plugins/Universal/HighPingKickFix/Entry.cpp

echo "Compiling Lua.dll..."

clang   --target=x86_64-windows-msvc -Wl,/subsystem:windows,/DLL -O3 \
        -Wno-inline-new-delete -Wno-implicit-exception-spec-mismatch -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined \
        -I./../SDK \
        -flto -fuse-ld=lld -o Lua.dll \
        -D_USRDLL -D_WINDLL \
        ../Plugins/Universal/Lua/Entry.cpp

echo "Compiling Playground5.dll..."

clang   --target=x86_64-windows-msvc -Wl,/subsystem:windows,/DLL -O3 \
        -Wno-inline-new-delete -Wno-implicit-exception-spec-mismatch -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined \
        -I./../SDK \
        -flto -fuse-ld=lld -o Playground5.dll \
        -D_USRDLL -D_WINDLL \
        ../Plugins/5/Playground/Entry.cpp

echo "Done compiling..."

rm "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/bin/PluginLoader.dll"
rm "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/plugins/HighPingKickFix.dll"
rm "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/plugins/Lua.dll"
rm "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/plugins/Playground5.dll"

cp "./PluginLoader.dll" "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/bin/PluginLoader.dll"
cp "./HighPingKickFix.dll" "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/plugins/HighPingKickFix.dll"
cp "./Lua.dll" "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/plugins/Lua.dll"
cp "./Playground5.dll" "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/plugins/Playground5.dll"