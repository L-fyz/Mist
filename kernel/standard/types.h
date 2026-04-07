#pragma once
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
typedef u64                usize;
typedef unsigned char b8;
#define true  1
#define false 0
#define NULL  ((void*)0)
#define offset_of(type, member) ((usize)&((type*)0)->member)
