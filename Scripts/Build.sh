BIN=/home/razor/msvc/bin/x64 . /home/razor/msvc-wine/msvcenv-native.sh

echo "Compiling dbdata.dll..."

clang   --target=x86_64-windows-msvc -Wl,/subsystem:windows,/DLL -O3 -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined \
        -fuse-ld=lld -o dbdata.dll \
        -D_USRDLL -D_WINDLL \
        ../Proxy/DBData.cpp

echo "Compiling PluginLoader.dll..."

clang   --target=x86_64-windows-msvc -Wl,/subsystem:windows,/DLL -O3 -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined -Wno-format-security -Wno-return-type-c-linkage \
        -I./../SDK \
        -fuse-ld=lld -o PluginLoader.dll \
        -D_USRDLL -D_WINDLL \
        ../PluginLoader/DllMain.cpp ../PluginLoader/Plugins.cpp \
        ../PluginLoader/Util/Signatures.cpp ../PluginLoader/Util/Stubs.cpp ../PluginLoader/Util/Log.cpp \
        ../PluginLoader/Game/Command.cpp

echo "Compiling HighPingKickFix.dll..."

clang   --target=x86_64-windows-msvc -Wl,/subsystem:windows,/DLL -O3 -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined \
        -I./../SDK \
        -fuse-ld=lld -o HighPingKickFix.dll \
        -D_USRDLL -D_WINDLL \
        ../Plugins/Universal/HighPingKickFix/Entry.cpp

echo "Done compiling..."

rm "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/bin/PluginLoader.dll"
rm "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/plugins/HighPingKickFix.dll"

cp "./PluginLoader.dll" "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/bin/PluginLoader.dll"
cp "./HighPingKickFix.dll" "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/plugins/HighPingKickFix.dll"
