/* ucrt_compat.c
 * Provides __imp___argc and __imp___argv symbols that IUP's libiup.a
 * (compiled against MSVCRT) expects, when building with modern MinGW-w64
 * UCRT toolchain (GCC 12+).
 *
 * These must be actual addressable global variables (not just constructor-set
 * pointers) because IUP accesses them via .refptr relocation entries in .rdata.
 */

extern int    __argc;
extern char **__argv;

/* Define the symbols IUP references as simple aliases */
int    *__imp___argc = &__argc;
char ***__imp___argv = (char ***)&__argv;
