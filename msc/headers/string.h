#pragma once

static char* str;

usize strlen(const char* str);
int isstreq(const char* a, const char* b);
void strcopy(const char* a, char* b);
char* u2s(u64 val, char* buf, u8 base);
