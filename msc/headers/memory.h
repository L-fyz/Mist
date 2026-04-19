#pragma once

void copy(void* dst, void* src, usize n);
void copyfb(void* dst, void* src, usize n);
void fill(void* dst, int val, usize n);
bool iseq(const void* a, const void* b, usize n);
