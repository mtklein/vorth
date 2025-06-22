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


#define DEFINE_DIV(T, suf)                        \
    void* vorth_div_##suf(void* sp) {            \
        T* stack = sp;                           \
        T const b = *--stack, a = *--stack;      \
        *stack++ = a / b;                        \
        return stack;                            \
    }

#define DEFINE_MAD(T, suf)                        \
    void* vorth_mad_##suf(void* sp) {            \
        T* stack = sp;                           \
        T const c = *--stack,                   \
                  b = *--stack,                 \
                  a = *--stack;                 \
        *stack++ = a * b + c;                   \
        return stack;                           \
    }

DEFINE_IMM(F16, f16, _Float16)
DEFINE_POP(F16, f16, _Float16)
DEFINE_ARITH(F16, f16)
DEFINE_DIV(F16, f16)
DEFINE_MAD(F16, f16)

DEFINE_IMM(F32, f32, float)
DEFINE_POP(F32, f32, float)
DEFINE_ARITH(F32, f32)
DEFINE_DIV(F32, f32)
DEFINE_MAD(F32, f32)

DEFINE_IMM(S8,  s8,  signed char)
DEFINE_POP(S8,  s8,  signed char)
DEFINE_IMM(S16, s16, short)
DEFINE_POP(S16, s16, short)
DEFINE_IMM(S32, s32, int)
DEFINE_POP(S32, s32, int)

DEFINE_IMM(U8,  u8,  unsigned char)
DEFINE_POP(U8,  u8,  unsigned char)
DEFINE_IMM(U16, u16, unsigned short)
DEFINE_POP(U16, u16, unsigned short)
DEFINE_IMM(U32, u32, unsigned int)
DEFINE_POP(U32, u32, unsigned int)

DEFINE_ARITH(I8,  i8)
DEFINE_ARITH(I16, i16)
DEFINE_ARITH(I32, i32)

DEFINE_BITWISE(I8,  i8)
DEFINE_BITWISE(I16, i16)
DEFINE_BITWISE(I32, i32)
