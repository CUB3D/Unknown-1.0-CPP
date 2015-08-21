@echo off

rmdir /S /Q Unknown++

mkdir Unknown++
cd Unknown++
mkdir include
mkdir lib
mkdir src
cd lib
mkdir x86

cd ..
cd ..

xcopy "Unknown 1.0++\*.h" "Unknown++\include" /Y

xcopy "Unknown 1.0++\*.cpp" "Unknown++\src" /Y

copy "Debug\Unknown 1.0++.lib" "Unknown++\lib\x86\Unknown++ - Debug.lib"
copy "release\Unknown 1.0++.lib" "Unknown++\lib\x86\Unknown++.lib"