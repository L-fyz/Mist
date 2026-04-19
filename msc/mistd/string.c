#include "mist.h"

usize strlen(const char* str) {
    if (str == NULL) {
        return 0;
    }
    usize i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

int isstreq(const char* a, const char* b) {
    if (a == NULL || b == NULL) {
        return 2;
    }
    usize i = 0; 
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] > b[i]) {
            return 1;
        }
        if (a[i] < b[i]) {
            return -1;
        }
        i++;
    }

    if (a[i] == '\0' && b[i] != '\0') {
        return -1;
    }
    if (a[i] != '\0' && b[i] == '\0') {
        return 1;
    }

    return 0;
}

void strcopy(const char* a, char* b) {
    if (a == NULL || b == NULL) {
        return;
    }
    usize len = 0;
    usize i = 0;
    while (b[i] != '\0' && a[i] != '\0') {
        len++;
        i++;
    }

    for (usize n = 0; n < len; n++) {
        b[n] = a[n];
    }
    b[len] = '\0';
}

char* u2s(u64 val, char* buf, u8 base) {
    static const char digits[] = "0123456789ABCDEF";
    char* p = buf;
    if (base < 2 || base > 16) {
        buf[0] = '\0';
        return buf;
    }
    
    do {
        *p++ = digits[val % base];
    } while (val /= base);
    
    *p = '\0';
    for (char *l = buf, *r = p - 1; l < r; l++, r--) { char t = *l; *l = *r; *r = t; }
    return buf;
}
