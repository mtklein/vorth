#include "vorth.h"
#include <assert.h>



static inline int equiv_f16(_Float16 x, _Float16 y) {
    return (x <= y && y <= x) || (x != x && y != y);
}

static inline int equiv_f32(float x, float y) {
    return (x <= y && y <= x) || (x != x && y != y);
}

#define DEFINE_TEST_INT(name, stype, utype, suf, imm_s, pop_s, imm_u, pop_u) \
static void name(void) {                                                    \
    stype stack[8 * V] __attribute__((aligned(sizeof(stype) * V)));         \
    void* sp = stack;                                                       \
    sp = imm_s(sp, 1);                                                      \
    sp = imm_s(sp, 2);                                                      \
    sp = vorth_add_##suf(sp);                                               \
    stype sres[V];                                                          \
    sp = pop_s(sp, sres);                                                   \
    for (int i = 0; i < V; i++)                                             \
        assert(sres[i] == 3);                                              \
    sp = stack;                                                             \
    sp = imm_s(sp, 5);                                                      \
    sp = imm_s(sp, 3);                                                      \
    sp = vorth_sub_##suf(sp);                                               \
    sp = pop_s(sp, sres);                                                   \
    for (int i = 0; i < V; i++)                                             \
        assert(sres[i] == 2);                                              \
    sp = stack;                                                             \
    sp = imm_s(sp, 2);                                                      \
    sp = imm_s(sp, 3);                                                      \
    sp = vorth_mul_##suf(sp);                                               \
    sp = pop_s(sp, sres);                                                   \
    for (int i = 0; i < V; i++)                                             \
        assert(sres[i] == 6);                                              \
    utype ures[V];                                                          \
    sp = stack;                                                             \
    sp = imm_u(sp, 0xaa);                                                   \
    sp = imm_u(sp, 0xcc);                                                   \
    sp = vorth_and_##suf(sp);                                               \
    sp = pop_u(sp, ures);                                                   \
    for (int i = 0; i < V; i++)                                             \
        assert(ures[i] == (utype)(0xaa & 0xcc));                            \
    sp = stack;                                                             \
    sp = imm_u(sp, 0xaa);                                                   \
    sp = imm_u(sp, 0xcc);                                                   \
    sp = vorth_or_##suf(sp);                                                \
    sp = pop_u(sp, ures);                                                   \
    for (int i = 0; i < V; i++)                                             \
        assert(ures[i] == (utype)(0xaa | 0xcc));                            \
    sp = stack;                                                             \
    sp = imm_u(sp, 0xaa);                                                   \
    sp = imm_u(sp, 0xcc);                                                   \
    sp = vorth_xor_##suf(sp);                                               \
    sp = pop_u(sp, ures);                                                   \
    for (int i = 0; i < V; i++)                                             \
        assert(ures[i] == (utype)(0xaa ^ 0xcc));                            \
    sp = stack;                                                             \
    sp = imm_u(sp, 0xaa);                                                   \
    sp = vorth_not_##suf(sp);                                               \
    sp = pop_u(sp, ures);                                                   \
    for (int i = 0; i < V; i++)                                             \
        assert(ures[i] == (utype)(~0xaa));                                  \
}

DEFINE_TEST_INT(test_i8,  signed char,      unsigned char,      i8,  vorth_imm_s8,  vorth_pop_s8,  vorth_imm_u8,  vorth_pop_u8)
DEFINE_TEST_INT(test_i16, short,            unsigned short,     i16, vorth_imm_s16, vorth_pop_s16, vorth_imm_u16, vorth_pop_u16)
DEFINE_TEST_INT(test_i32, int,              unsigned int,       i32, vorth_imm_s32, vorth_pop_s32, vorth_imm_u32, vorth_pop_u32)

static void test_f16(void) {
    _Float16 stack[8 * V] __attribute__((aligned(sizeof(_Float16) * V)));
    void* sp = stack;

    sp = vorth_imm_f16(sp, 1);
    sp = vorth_imm_f16(sp, 2);
    sp = vorth_add_f16(sp);
    _Float16 res[V];
    sp = vorth_pop_f16(sp, res);
    for (int i = 0; i < V; i++) {
        assert(equiv_f16(res[i], 3));
    }

    sp = stack;
    sp = vorth_imm_f16(sp, 5);
    sp = vorth_imm_f16(sp, 3);
    sp = vorth_sub_f16(sp);
    sp = vorth_pop_f16(sp, res);
    for (int i = 0; i < V; i++) {
        assert(equiv_f16(res[i], 2));
    }

    sp = stack;
    sp = vorth_imm_f16(sp, 2);
    sp = vorth_imm_f16(sp, 3);
    sp = vorth_mul_f16(sp);
    sp = vorth_pop_f16(sp, res);
    for (int i = 0; i < V; i++) {
        assert(equiv_f16(res[i], 6));
    }

    sp = stack;
    sp = vorth_imm_f16(sp, 6);
    sp = vorth_imm_f16(sp, 2);
    sp = vorth_div_f16(sp);
    sp = vorth_pop_f16(sp, res);
    for (int i = 0; i < V; i++) {
        assert(equiv_f16(res[i], 3));
    }

    sp = stack;
    sp = vorth_imm_f16(sp, 2);
    sp = vorth_imm_f16(sp, 3);
    sp = vorth_imm_f16(sp, 4);
    sp = vorth_mad_f16(sp);
    sp = vorth_pop_f16(sp, res);
    for (int i = 0; i < V; i++) {
        assert(equiv_f16(res[i], 10));
    }
}

static void test_f32(void) {
    float stack[8 * V] __attribute__((aligned(sizeof(float) * V)));
    void* sp = stack;

    sp = vorth_imm_f32(sp, 1);
    sp = vorth_imm_f32(sp, 2);
    sp = vorth_add_f32(sp);
    float res[V];
    sp = vorth_pop_f32(sp, res);
    for (int i = 0; i < V; i++) {
        assert(equiv_f32(res[i], 3));
    }

    sp = stack;
    sp = vorth_imm_f32(sp, 5);
    sp = vorth_imm_f32(sp, 3);
    sp = vorth_sub_f32(sp);
    sp = vorth_pop_f32(sp, res);
    for (int i = 0; i < V; i++) {
        assert(equiv_f32(res[i], 2));
    }

    sp = stack;
    sp = vorth_imm_f32(sp, 2);
    sp = vorth_imm_f32(sp, 3);
    sp = vorth_mul_f32(sp);
    sp = vorth_pop_f32(sp, res);
    for (int i = 0; i < V; i++) {
        assert(equiv_f32(res[i], 6));
    }

    sp = stack;
    sp = vorth_imm_f32(sp, 6);
    sp = vorth_imm_f32(sp, 2);
    sp = vorth_div_f32(sp);
    sp = vorth_pop_f32(sp, res);
    for (int i = 0; i < V; i++) {
        assert(equiv_f32(res[i], 3));
    }

    sp = stack;
    sp = vorth_imm_f32(sp, 2);
    sp = vorth_imm_f32(sp, 3);
    sp = vorth_imm_f32(sp, 4);
    sp = vorth_mad_f32(sp);
    sp = vorth_pop_f32(sp, res);
    for (int i = 0; i < V; i++) {
        assert(equiv_f32(res[i], 10));
    }
}

int main(void) {
    test_i8();
    test_i16();
    test_i32();
    test_f16();
    test_f32();
    return 0;
}
