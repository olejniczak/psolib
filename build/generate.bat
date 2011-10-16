@echo off
echo Generating NMake makefiles
CMake -G "NMake Makefiles" ..
echo done.
echo Type nmake to build PSOlib library.
pause
