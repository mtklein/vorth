#include "vorth.h"

#include <stddef.h>

#define V 8

typedef _Float16 v_f16 __attribute__((vector_size(sizeof(_Float16) * V)));
typedef float    v_f32 __attribute__((vector_size(sizeof(float) * V)));

static inline v_f16 splat_f16(_Float16 x) {
    return (v_f16){x, x, x, x, x, x, x, x};
}

static inline __attribute__((target("avx"))) v_f32 splat_f32(float x) {
    return (v_f32){x, x, x, x, x, x, x, x};
}

void* vorth_imm_f16(void* sp, _Float16 x) {
    v_f16* stack = (v_f16*)sp;
    stack[0] = splat_f16(x);
    return stack + 1;
}

void* vorth_add_f16(void* sp) {
    v_f16* stack = (v_f16*)sp;
    v_f16 b = stack[-1];
    v_f16 a = stack[-2];
    stack[-2] = a + b;
    return stack - 1;
}

void* vorth_sub_f16(void* sp) {
    v_f16* stack = (v_f16*)sp;
    v_f16 b = stack[-1];
    v_f16 a = stack[-2];
    stack[-2] = a - b;
    return stack - 1;
}

void* vorth_mul_f16(void* sp) {
    v_f16* stack = (v_f16*)sp;
    v_f16 b = stack[-1];
    v_f16 a = stack[-2];
    stack[-2] = a * b;
    return stack - 1;
}

void* vorth_div_f16(void* sp) {
    v_f16* stack = (v_f16*)sp;
    v_f16 b = stack[-1];
    v_f16 a = stack[-2];
    stack[-2] = a / b;
    return stack - 1;
}

void* vorth_mad_f16(void* sp) {
    v_f16* stack = (v_f16*)sp;
    v_f16 c = stack[-1];
    v_f16 b = stack[-2];
    v_f16 a = stack[-3];
    stack[-3] = a * b + c;
    return stack - 2;
}

__attribute__((target("avx")))
void* vorth_imm_f32(void* sp, float x) {
    v_f32* stack = (v_f32*)sp;
    stack[0] = splat_f32(x);
    return stack + 1;
}

__attribute__((target("avx")))
void* vorth_add_f32(void* sp) {
    v_f32* stack = (v_f32*)sp;
    v_f32 b = stack[-1];
    v_f32 a = stack[-2];
    stack[-2] = a + b;
    return stack - 1;
}

__attribute__((target("avx")))
void* vorth_sub_f32(void* sp) {
    v_f32* stack = (v_f32*)sp;
    v_f32 b = stack[-1];
    v_f32 a = stack[-2];
    stack[-2] = a - b;
    return stack - 1;
}

__attribute__((target("avx")))
void* vorth_mul_f32(void* sp) {
    v_f32* stack = (v_f32*)sp;
    v_f32 b = stack[-1];
    v_f32 a = stack[-2];
    stack[-2] = a * b;
    return stack - 1;
}

__attribute__((target("avx")))
void* vorth_div_f32(void* sp) {
    v_f32* stack = (v_f32*)sp;
    v_f32 b = stack[-1];
    v_f32 a = stack[-2];
    stack[-2] = a / b;
    return stack - 1;
}

__attribute__((target("avx")))
void* vorth_mad_f32(void* sp) {
    v_f32* stack = (v_f32*)sp;
    v_f32 c = stack[-1];
    v_f32 b = stack[-2];
    v_f32 a = stack[-3];
    stack[-3] = a * b + c;
    return stack - 2;
}
