/* ucrt_compat.c
 * Compatibility shim for linking IUP 3.32 static libraries with modern
 * MinGW / UCRT on Windows. IUP's iupwindows_main.o references
 * __imp___argc and __imp___argv (old MSVCRT-style import symbols).
 * Modern GCC/UCRT no longer exposes __argc/__argv as linkable externals,
 * so we provide the symbols ourselves with harmless zero/null defaults.
 * IupOpen() receives the real argc/argv from our main() call anyway.
 */
static int    _compat_argc = 0;
static char  *_compat_argv_buf = "";
static char **_compat_argv = &_compat_argv_buf;

int    *__imp___argc = &_compat_argc;
char ***__imp___argv = (char ***)&_compat_argv;
