BIN=/home/razor/msvc/bin/x64 . /home/razor/msvc-wine/msvcenv-native.sh

clang   --target=x86_64-windows-msvc -Wl,/subsystem:windows,/DLL -O2 -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined \
        -I./../SDK \
        -fuse-ld=lld -o Loader.dll \
        -D_USRDLL -D_WINDLL \
        ../Loader/DllMain.cpp ../Loader/Plugins.cpp

clang   --target=x86_64-windows-msvc -Wl,/subsystem:windows,/DLL -O2 -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined \
        -I./../SDK \
        -fuse-ld=lld -o HighPingKickFix.dll \
        -D_USRDLL -D_WINDLL \
        ../Plugins/Universal/HighPingKickFix/DllMain.cpp

clang   --target=x86_64-windows-msvc -Wl,/subsystem:windows,/DLL -O2 -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined \
        -fuse-ld=lld -o dbdata.dll \
        -D_USRDLL -D_WINDLL \
        ../Proxy/DBData.cpp

clang   --target=x86_64-windows-msvc -Wl,/subsystem:console -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined \
        -fuse-ld=lld -o TestApp.exe \
        ../TestApp/Main.c

rm "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/bin/PluginLoader.dll"
rm "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/plugins/HighPingKickFix.dll"

cp "./Loader.dll" "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/bin/PluginLoader.dll"
cp "./HighPingKickFix.dll" "/home/razor/.local/share/bottles/bottles/Ubisoft/drive_c/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/games/Far Cry 5/plugins/HighPingKickFix.dll"
