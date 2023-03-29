call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildsTools\VC\Auxiliary\Build\vcvars64.bat" x64

echo "Compiling dbdata.dll..."

clang   -Wl,/subsystem:windows,/machine:X64,/DLL -O3 -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined ^
        -I./../SDK ^
        -o ./dbdata.dll ^
        -D_USRDLL -D_WINDLL ^
        ../Proxy/DBData.cpp

echo "Compiling PluginLoader.dll..."

clang   -Wl,/subsystem:windows,/machine:X64,/DLL -O3 -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined -Wno-format-security -Wno-return-type-c-linkage -Wno-writable-strings -Wno-format ^
        -I./../SDK ^
        -o ./PluginLoader.dll ^
        -D_USRDLL -D_WINDLL ^
        ../PluginLoader/DllMain.cpp ../PluginLoader/Plugins.cpp ^
        ../PluginLoader/Util/Log.cpp ../PluginLoader/Util/Signatures.cpp ../PluginLoader/Util/Disasm.cpp ^
        ../PluginLoader/Util/Bytepatch.cpp ../PluginLoader/Util/Stubs.cpp ../PluginLoader/Util/Detours.cpp ^
        ../PluginLoader/Game/Command.cpp

echo "Compiling HighPingKickFix.dll..."

clang   -Wl,/subsystem:windows,/machine:X64,/DLL -O3 -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined ^
        -I./../SDK ^
        -o ./HighPingKickFix.dll ^
        -D_USRDLL -D_WINDLL ^
        ../Plugins/Universal/HighPingKickFix/Entry.cpp

echo "Compiling Playground5.dll..."

clang   -Wl,/subsystem:windows,/machine:X64,/DLL -O3 -Wno-deprecated-declarations -Wno-pragma-pack -Wno-macro-redefined ^
        -I./../SDK ^
        -o ./Playground5.dll ^
        -D_USRDLL -D_WINDLL ^
        ../Plugins/5/Playground/Entry.cpp

echo "Done compiling..."