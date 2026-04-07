#include "types.h"

void copy(void* dst, const void* src, usize n) {
    u8 *d = (u8*)dst;
    const u8 *s = (const u8*)src;
    for (usize i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

void copyfb(void* dst, const void* src, usize n) {
    u8 *d = (u8*)dst;
    const u8 *s = (const u8*)src;
    for (usize i = n; i > 0; i--) {
        d[i-1] = s[i-1];
    }
}

void fill(void* dst, int val, usize n) {
    u8 *d = (u8*)dst;
    for (usize i = 0; i < n; i++) {
        d[i] = (u8)val;
    }
}

bool iseq(const void* a, const void* b, usize n) {
    const u8 *first = (const u8*)a;
    const u8 *second = (const u8*)b;
    for (usize i = 0; i < n; i++) {
        if (first[i] != second[i]) {
            return false;
        }
    }
    return true;
}
