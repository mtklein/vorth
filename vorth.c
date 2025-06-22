#include "vorth.h"

typedef _Float16 f16 __attribute__((vector_size(V * sizeof(_Float16))));
typedef float    f32 __attribute__((vector_size(V * sizeof(float))));

typedef signed char       s8  __attribute__((vector_size(V * sizeof(signed char))));
typedef unsigned char     u8  __attribute__((vector_size(V * sizeof(unsigned char))));
typedef short             s16 __attribute__((vector_size(V * sizeof(short))));
typedef unsigned short    u16 __attribute__((vector_size(V * sizeof(unsigned short))));
typedef int               s32 __attribute__((vector_size(V * sizeof(int))));
typedef unsigned int      u32 __attribute__((vector_size(V * sizeof(unsigned int))));

typedef u8  i8;
typedef u16 i16;
typedef u32 i32;

#define splat(T, x) ((T){0} + 1) * (x)

#define DEFINE_IMM(T, suf, ctype)                  \
    void* vorth_imm_##suf(void* sp, ctype x) {     \
        T* stack = sp;                             \
        *stack++ = splat(T, x);                    \
        return stack;                              \
    }

#define DEFINE_ARITH(T, suf)                       \
    void* vorth_add_##suf(void* sp) {              \
        T* stack = sp;                             \
        const T b = *--stack, a = *--stack;        \
        *stack++ = a + b;                          \
        return stack;                              \
    }                                              \
    void* vorth_sub_##suf(void* sp) {              \
        T* stack = sp;                             \
        const T b = *--stack, a = *--stack;        \
        *stack++ = a - b;                          \
        return stack;                              \
    }                                              \
    void* vorth_mul_##suf(void* sp) {              \
        T* stack = sp;                             \
        const T b = *--stack, a = *--stack;        \
        *stack++ = a * b;                          \
        return stack;                              \
    }

#define DEFINE_POP(T, suf, ctype)                  \
    void* vorth_pop_##suf(void* sp, ctype out[V]) { \
        T* stack = sp;                             \
        const T x = *--stack;                      \
        __builtin_memcpy(out, &x, sizeof x);       \
        return stack;                              \
    }


#define DEFINE_BITWISE(T, suf)                      \
    void* vorth_and_##suf(void* sp) {               \
        T* stack = sp;                              \
        const T b = *--stack, a = *--stack;         \
        *stack++ = a & b;                           \
        return stack;                               \
    }                                               \
    void* vorth_or_##suf(void* sp) {                \
        T* stack = sp;                              \
        const T b = *--stack, a = *--stack;         \
        *stack++ = a | b;                           \
        return stack;                               \
    }                                               \
    void* vorth_xor_##suf(void* sp) {               \
        T* stack = sp;                              \
        const T b = *--stack, a = *--stack;         \
        *stack++ = a ^ b;                           \
        return stack;                               \
    }                                               \
    void* vorth_not_##suf(void* sp) {               \
        T* stack = sp;                              \
        const T a = *--stack;                       \
        *stack++ = ~a;                              \
        return stack;                               \
    }


#define DEFINE_DIV(T, suf)                          \
    void* vorth_div_##suf(void* sp) {              \
        T* stack = sp;                             \
        const T b = *--stack, a = *--stack;        \
        *stack++ = a / b;                          \
        return stack;                              \
    }

#define DEFINE_MAD(T, suf)                          \
    void* vorth_mad_##suf(void* sp) {              \
        T* stack = sp;                             \
        const T c = *--stack,                      \
                  b = *--stack,                    \
                  a = *--stack;                    \
        *stack++ = a * b + c;                      \
        return stack;                              \
    }

DEFINE_IMM(f16, f16, _Float16)
DEFINE_POP(f16, f16, _Float16)
DEFINE_ARITH(f16, f16)
DEFINE_DIV(f16, f16)
DEFINE_MAD(f16, f16)

DEFINE_IMM(f32, f32, float)
DEFINE_POP(f32, f32, float)
DEFINE_ARITH(f32, f32)
DEFINE_DIV(f32, f32)
DEFINE_MAD(f32, f32)

DEFINE_IMM(s8,  s8,  signed char)
DEFINE_POP(s8,  s8,  signed char)
DEFINE_IMM(s16, s16, short)
DEFINE_POP(s16, s16, short)
DEFINE_IMM(s32, s32, int)
DEFINE_POP(s32, s32, int)

DEFINE_IMM(u8,  u8,  unsigned char)
DEFINE_POP(u8,  u8,  unsigned char)
DEFINE_IMM(u16, u16, unsigned short)
DEFINE_POP(u16, u16, unsigned short)
DEFINE_IMM(u32, u32, unsigned int)
DEFINE_POP(u32, u32, unsigned int)

DEFINE_ARITH(i8,  i8)
DEFINE_ARITH(i16, i16)
DEFINE_ARITH(i32, i32)

DEFINE_BITWISE(i8,  i8)
DEFINE_BITWISE(i16, i16)
DEFINE_BITWISE(i32, i32)
