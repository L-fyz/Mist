# Mistd
This is small bare-metal standard library for C. Now it have many features that I will explain now

## Tools
Now mistd have tools to work with:
- Screen
- Memory
- Strings

### Screen tools
They are in screen.c file:

|Name                                         |What it does                                                                  |
|:-------------------------------------------:|:-----------------------------------------------------------------------------|
|`clear()`                                    |Clears the screen and moves cursor to left up of screen                       |
|`putchar(char c)`                            |Insert c to the cursor place and move cursor right (Down if screen width ends)|
|`print_str(const char* str)`                 |Just print... You know                                                        |
|`print_num(u64 i, base)`                     |Printing a number with `base` notation                                        |
|`void delchar(void)`                         |Delete last char from screen and moves cursor back                            |
|`void cursor_upd(int x, int y)`              |Set up cursor to (x; y) position                                              |

### Memory tools
They are in memory.c file:

|Name                                         |What it does                                                                  |
|:-------------------------------------------:|:-----------------------------------------------------------------------------|
|`copy(void* dst, void* src, usize n)`        |Clone n bytes from cd to ab                                                   |
|`copyfb(void* dst, void src, usize n)`       |Same as copy(), but from the back                                             |
|`fill(void* dst, void* src, usize n)`        |Fill ab with c n times                                                        |
|`iseq(const void* a, const void* b, usize n)`|Check the equality of ab and cd (True - ab==cd; False - ab!=cd)               |

### String tools
They are in string.c:

|Name                                         |What it does                                                                  |
|:-------------------------------------------:|:-----------------------------------------------------------------------------|
|`u2s(u64 val, char* buf, u8 base)`           |Convert number with selected base to string                                   |
|`strlen(const char* str)`                    |Returns length of given string                                                |
|`isstreq(const char* a, const char* b)`      |Returns 1 if a>b, -1 if a<b, 0 if a=b and 2 if a=NULL or b=NULL               |
|`strcopy(const char* a, char* b)`            |Copy a string to b with '\0' at and. Safe copy                                |
