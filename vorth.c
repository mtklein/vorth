#include "vorth.h"

typedef _Float16 F16 __attribute__((vector_size(sizeof(_Float16) * V)));
typedef float    F32 __attribute__((vector_size(sizeof(float) * V)));

typedef signed char       S8  __attribute__((vector_size(sizeof(signed char) * V)));
typedef unsigned char     U8  __attribute__((vector_size(sizeof(unsigned char) * V)));
typedef short             S16 __attribute__((vector_size(sizeof(short) * V)));
typedef unsigned short    U16 __attribute__((vector_size(sizeof(unsigned short) * V)));
typedef int               S32 __attribute__((vector_size(sizeof(int) * V)));
typedef unsigned int      U32 __attribute__((vector_size(sizeof(unsigned int) * V)));

typedef U8  I8;
typedef U16 I16;
typedef U32 I32;

#define splat(T, x) ((T){0} + 1) * (x)

#define DEFINE_IMM(T, suf, ctype)                 \
    void* vorth_imm_##suf(void* sp, ctype x) {    \
        T* stack = sp;                            \
        *stack++ = splat(T, x);                   \
        return stack;                             \
    }

#define DEFINE_ARITH(T, suf)                      \
    void* vorth_add_##suf(void* sp) {             \
        T* stack = sp;                            \
        T const b = *--stack, a = *--stack;       \
        *stack++ = a + b;                         \
        return stack;                             \
    }                                             \
    void* vorth_sub_##suf(void* sp) {             \
        T* stack = sp;                            \
        T const b = *--stack, a = *--stack;       \
        *stack++ = a - b;                         \
        return stack;                             \
    }                                             \
    void* vorth_mul_##suf(void* sp) {             \
        T* stack = sp;                            \
        T const b = *--stack, a = *--stack;       \
        *stack++ = a * b;                         \
        return stack;                             \
    }

#define DEFINE_POP(T, suf, ctype)                 \
    void* vorth_pop_##suf(void* sp, ctype out[V]) {\
        T* stack = sp;                            \
        T x = *--stack;                           \
        __builtin_memcpy(out, &x, sizeof x);      \
        return stack;                             \
    }


#define DEFINE_BITWISE(T, suf)                    \
    void* vorth_and_##suf(void* sp) {             \
        T* stack = sp;                            \
        T const b = *--stack, a = *--stack;       \
        *stack++ = a & b;                         \
        return stack;                             \
    }                                             \
    void* vorth_or_##suf(void* sp) {              \
        T* stack = sp;                            \
        T const b = *--stack, a = *--stack;       \
        *stack++ = a | b;                         \
        return stack;                             \
    }                                             \
    void* vorth_xor_##suf(void* sp) {             \
        T* stack = sp;                            \
        T const b = *--stack, a = *--stack;       \
        *stack++ = a ^ b;                         \
        return stack;                             \
    }                                             \
    void* vorth_not_##suf(void* sp) {             \
        T* stack = sp;                            \
        T const a = *--stack;                     \
        *stack++ = ~a;                            \
        return stack;                             \
    }

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
    __builtin_memcpy(out, &x, sizeof x);
    return stack;
}

void* vorth_pop_f32(void* sp, float out[V]) {
    F32* stack = sp;
    F32 x = *--stack;
    __builtin_memcpy(out, &x, sizeof x);
    return stack;
}

// Signed integer immediates and pop
DEFINE_IMM(S8,  s8,  signed char)
DEFINE_POP(S8,  s8,  signed char)
DEFINE_IMM(S16, s16, short)
DEFINE_POP(S16, s16, short)
DEFINE_IMM(S32, s32, int)
DEFINE_POP(S32, s32, int)

// Unsigned integer immediates and pop
DEFINE_IMM(U8,  u8,  unsigned char)
DEFINE_POP(U8,  u8,  unsigned char)
DEFINE_IMM(U16, u16, unsigned short)
DEFINE_POP(U16, u16, unsigned short)
DEFINE_IMM(U32, u32, unsigned int)
DEFINE_POP(U32, u32, unsigned int)

// Integer arithmetic
DEFINE_ARITH(I8,  i8)
DEFINE_ARITH(I16, i16)
DEFINE_ARITH(I32, i32)

// Bitwise operations
DEFINE_BITWISE(I8,  i8)
DEFINE_BITWISE(I16, i16)
DEFINE_BITWISE(I32, i32)
