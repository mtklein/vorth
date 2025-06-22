#include "vorth.h"

void* vorth_imm_f16(void* sp, _Float16 x) {
    F16* stack = sp;
    *stack++ = splat(F16, x);
    return stack;
}

void* vorth_add_f16(void* sp) {
    F16* stack = sp;
    F16 b = *--stack;
    F16 a = *--stack;
    *stack++ = a + b;
    return stack;
}

void* vorth_sub_f16(void* sp) {
    F16* stack = sp;
    F16 b = *--stack;
    F16 a = *--stack;
    *stack++ = a - b;
    return stack;
}

void* vorth_mul_f16(void* sp) {
    F16* stack = sp;
    F16 b = *--stack;
    F16 a = *--stack;
    *stack++ = a * b;
    return stack;
}

void* vorth_div_f16(void* sp) {
    F16* stack = sp;
    F16 b = *--stack;
    F16 a = *--stack;
    *stack++ = a / b;
    return stack;
}

void* vorth_mad_f16(void* sp) {
    F16* stack = sp;
    F16 c = *--stack;
    F16 b = *--stack;
    F16 a = *--stack;
    *stack++ = a * b + c;
    return stack;
}

void* vorth_imm_f32(void* sp, float x) {
    F32* stack = sp;
    *stack++ = splat(F32, x);
    return stack;
}

void* vorth_add_f32(void* sp) {
    F32* stack = sp;
    F32 b = *--stack;
    F32 a = *--stack;
    *stack++ = a + b;
    return stack;
}

void* vorth_sub_f32(void* sp) {
    F32* stack = sp;
    F32 b = *--stack;
    F32 a = *--stack;
    *stack++ = a - b;
    return stack;
}

void* vorth_mul_f32(void* sp) {
    F32* stack = sp;
    F32 b = *--stack;
    F32 a = *--stack;
    *stack++ = a * b;
    return stack;
}

void* vorth_div_f32(void* sp) {
    F32* stack = sp;
    F32 b = *--stack;
    F32 a = *--stack;
    *stack++ = a / b;
    return stack;
}

void* vorth_mad_f32(void* sp) {
    F32* stack = sp;
    F32 c = *--stack;
    F32 b = *--stack;
    F32 a = *--stack;
    *stack++ = a * b + c;
    return stack;
}
