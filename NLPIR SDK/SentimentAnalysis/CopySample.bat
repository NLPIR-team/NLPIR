@echo off
xcopy ".\project\C#\*.cs" ".\sample\C#\" /y
xcopy ".\project\C#\*.config" ".\sample\C#\" /y
xcopy ".\project\C++\*.cpp" ".\sample\C++\" /y
xcopy ".\project\C++\*.c" ".\sample\C++\" /y
xcopy ".\project\C++\*.h" ".\sample\C++\" /y
xcopy ".\project\C++\*.hpp" ".\sample\C++\" /y