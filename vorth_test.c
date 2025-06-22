#include "vorth.h"
#include <assert.h>


static inline int equiv_f16(_Float16 x, _Float16 y) {
    return (x <= y && y <= x) || (x != x && y != y);
}

static inline int equiv_f32(float x, float y) {
    return (x <= y && y <= x) || (x != x && y != y);
}

static void test_s32(void) {
    int stack[8 * V] __attribute__((aligned(sizeof(int) * V)));
    void* sp = stack;

    sp = vorth_imm_s32(sp, 1);
    sp = vorth_imm_s32(sp, 2);
    sp = vorth_add_i32(sp);
    int res[V];
    sp = vorth_pop_s32(sp, res);
    for (int i = 0; i < V; i++) {
        assert(res[i] == 3);
    }

    sp = stack;
    sp = vorth_imm_s32(sp, 0);
    sp = vorth_not_i32(sp);
    sp = vorth_pop_s32(sp, res);
    for (int i = 0; i < V; i++) {
        assert(res[i] == ~0);
    }
}

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
    test_s32();
    test_f16();
    test_f32();
    return 0;
}
