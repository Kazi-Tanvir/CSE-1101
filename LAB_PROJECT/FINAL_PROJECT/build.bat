@echo off
setlocal

echo ====================================================
echo   Building Image Manipulation Software (Win64)
echo ====================================================
taskkill /F /IM ImageEditor.exe >nul 2>nul

gcc src\main.c src\gui.c src\image.c src\filter.c src\ucrt_compat.c ^
    -o ImageEditor.exe ^
    -I./include -L./lib ^
    -liup -lgdi32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -luxtheme ^
    -Wall -Wextra

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [SUCCESS] ImageEditor.exe built successfully!
    echo Launching ImageEditor.exe...
    .\ImageEditor.exe
) else (
    echo.
    echo [ERROR] Build failed! Please review compiler errors above.
)

pause