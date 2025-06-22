#include "vorth.h"

#define V 8

typedef _Float16 v_f16 __attribute__((vector_size(sizeof(_Float16) * V)));
typedef float    v_f32 __attribute__((vector_size(sizeof(float) * V)));

#define SPLAT_F16(x) ((v_f16){x, x, x, x, x, x, x, x})
#define SPLAT_F32(x) ((v_f32){x, x, x, x, x, x, x, x})

void* vorth_imm_f16(void* sp, _Float16 x) {
    v_f16* stack = sp;
    stack[0] = SPLAT_F16(x);
    return stack + 1;
}

void* vorth_add_f16(void* sp) {
    v_f16* stack = sp;
    v_f16 b = stack[-1];
    v_f16 a = stack[-2];
    stack[-2] = a + b;
    return stack - 1;
}

void* vorth_sub_f16(void* sp) {
    v_f16* stack = sp;
    v_f16 b = stack[-1];
    v_f16 a = stack[-2];
    stack[-2] = a - b;
    return stack - 1;
}

void* vorth_mul_f16(void* sp) {
    v_f16* stack = sp;
    v_f16 b = stack[-1];
    v_f16 a = stack[-2];
    stack[-2] = a * b;
    return stack - 1;
}

void* vorth_div_f16(void* sp) {
    v_f16* stack = sp;
    v_f16 b = stack[-1];
    v_f16 a = stack[-2];
    stack[-2] = a / b;
    return stack - 1;
}

void* vorth_mad_f16(void* sp) {
    v_f16* stack = sp;
    v_f16 c = stack[-1];
    v_f16 b = stack[-2];
    v_f16 a = stack[-3];
    stack[-3] = a * b + c;
    return stack - 2;
}

void* vorth_imm_f32(void* sp, float x) {
    v_f32* stack = sp;
    stack[0] = SPLAT_F32(x);
    return stack + 1;
}

void* vorth_add_f32(void* sp) {
    v_f32* stack = sp;
    v_f32 b = stack[-1];
    v_f32 a = stack[-2];
    stack[-2] = a + b;
    return stack - 1;
}

void* vorth_sub_f32(void* sp) {
    v_f32* stack = sp;
    v_f32 b = stack[-1];
    v_f32 a = stack[-2];
    stack[-2] = a - b;
    return stack - 1;
}

void* vorth_mul_f32(void* sp) {
    v_f32* stack = sp;
    v_f32 b = stack[-1];
    v_f32 a = stack[-2];
    stack[-2] = a * b;
    return stack - 1;
}

void* vorth_div_f32(void* sp) {
    v_f32* stack = sp;
    v_f32 b = stack[-1];
    v_f32 a = stack[-2];
    stack[-2] = a / b;
    return stack - 1;
}

void* vorth_mad_f32(void* sp) {
    v_f32* stack = sp;
    v_f32 c = stack[-1];
    v_f32 b = stack[-2];
    v_f32 a = stack[-3];
    stack[-3] = a * b + c;
    return stack - 2;
}
