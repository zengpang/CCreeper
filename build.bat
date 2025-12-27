@echo off
echo Cleaning previous build...
rmdir /s /q build

echo Configuring with static linking...
cmake -B build ^
    -DCMAKE_TOOLCHAIN_FILE=H:/vcpkg/scripts/buildsystems/vcpkg.cmake ^
    -DVCPKG_TARGET_TRIPLET=x64-windows-static ^
    -DBUILD_SHARED_LIBS=OFF ^
    -DCURL_USE_STATIC_LIBS=ON

echo Building...
cmake --build build --config Release

echo Checking dependencies...
dumpbin /DEPENDENTS build\Release\CCreeper.exe

pause