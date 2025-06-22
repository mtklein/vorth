#include "vorth.h"

typedef _Float16 F16 __attribute__((vector_size(sizeof(_Float16) * V)));
typedef float    F32 __attribute__((vector_size(sizeof(float) * V)));

#define splat(T, x) ((T){0} + 1) * (x)

void* vorth_imm_f16(void* sp, _Float16 x) {
    F16* stack = sp;
    *stack++ = splat(F16, x);
    return stack;
}

void* vorth_add_f16(void* sp) {
    F16* stack = sp;
    F16 const b = *--stack,
              a = *--stack;
    *stack++ = a + b;
    return stack;
}

void* vorth_sub_f16(void* sp) {
    F16* stack = sp;
    F16 const b = *--stack,
              a = *--stack;
    *stack++ = a - b;
    return stack;
}

void* vorth_mul_f16(void* sp) {
    F16* stack = sp;
    F16 const b = *--stack,
              a = *--stack;
    *stack++ = a * b;
    return stack;
}

void* vorth_div_f16(void* sp) {
    F16* stack = sp;
    F16 const b = *--stack,
              a = *--stack;
    *stack++ = a / b;
    return stack;
}

void* vorth_mad_f16(void* sp) {
    F16* stack = sp;
    F16 const c = *--stack,
              b = *--stack,
              a = *--stack;
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
    F32 const b = *--stack,
              a = *--stack;
    *stack++ = a + b;
    return stack;
}

void* vorth_sub_f32(void* sp) {
    F32* stack = sp;
    F32 const b = *--stack,
              a = *--stack;
    *stack++ = a - b;
    return stack;
}

void* vorth_mul_f32(void* sp) {
    F32* stack = sp;
    F32 const b = *--stack,
              a = *--stack;
    *stack++ = a * b;
    return stack;
}

void* vorth_div_f32(void* sp) {
    F32* stack = sp;
    F32 const b = *--stack,
              a = *--stack;
    *stack++ = a / b;
    return stack;
}

void* vorth_mad_f32(void* sp) {
    F32* stack = sp;
    F32 const c = *--stack,
              b = *--stack,
              a = *--stack;
    *stack++ = a * b + c;
    return stack;
}

void* vorth_pop_f16(void* sp, _Float16 out[V]) {
    F16* stack = sp;
    F16 x = *--stack;
    for (int i = 0; i < V; i++) {
        out[i] = x[i];
    }
    return stack;
}

void* vorth_pop_f32(void* sp, float out[V]) {
    F32* stack = sp;
    F32 x = *--stack;
    for (int i = 0; i < V; i++) {
        out[i] = x[i];
    }
    return stack;
}
