@echo off
setlocal

echo ====================================================
echo   Building IUP 3.32 Test Program (Windows 64-bit)
echo ====================================================

gcc test_iup.c src\ucrt_compat.c -o test_iup.exe ^
    -I./include -L./lib ^
    -liup -lgdi32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -luxtheme

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [SUCCESS] test_iup.exe built successfully!
    echo Launching test_iup.exe...
    .\test_iup.exe
) else (
    echo.
    echo [ERROR] Build failed! Check compiler output above.
)

pause
