mkdir build-arm64
cd build-arm64
cmake .. -G "Visual Studio 17 2022" -A arm64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_CXX_FLAGS="/DUSE_SOFT_INTRINSICS /DPOPCNT64=__popcnt64 " -DENABLE_SSE=OFF -DUseInternalLibs=OFF -DBuildDiscordRichPresence=OFF
cmake --build . --config Release
pause