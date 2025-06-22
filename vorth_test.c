#include "vorth.h"
#include <assert.h>
#include <math.h>

#define V 8

static void test_f16(void) {
    _Float16 stack[8 * V] __attribute__((aligned(16)));
    void* sp = stack;

    sp = vorth_imm_f16(sp, (_Float16)1.0);
    sp = vorth_imm_f16(sp, (_Float16)2.0);
    sp = vorth_add_f16(sp);
    _Float16* res = (_Float16*)sp - V;
    for (int i = 0; i < V; i++) {
        assert(fabs((double)res[i] - 3.0) < 0.001);
    }

    sp = stack;
    sp = vorth_imm_f16(sp, (_Float16)5.0);
    sp = vorth_imm_f16(sp, (_Float16)3.0);
    sp = vorth_sub_f16(sp);
    res = (_Float16*)sp - V;
    for (int i = 0; i < V; i++) {
        assert(fabs((double)res[i] - 2.0) < 0.001);
    }

    sp = stack;
    sp = vorth_imm_f16(sp, (_Float16)2.0);
    sp = vorth_imm_f16(sp, (_Float16)3.0);
    sp = vorth_mul_f16(sp);
    res = (_Float16*)sp - V;
    for (int i = 0; i < V; i++) {
        assert(fabs((double)res[i] - 6.0) < 0.001);
    }

    sp = stack;
    sp = vorth_imm_f16(sp, (_Float16)6.0);
    sp = vorth_imm_f16(sp, (_Float16)2.0);
    sp = vorth_div_f16(sp);
    res = (_Float16*)sp - V;
    for (int i = 0; i < V; i++) {
        assert(fabs((double)res[i] - 3.0) < 0.001);
    }

    sp = stack;
    sp = vorth_imm_f16(sp, (_Float16)2.0);
    sp = vorth_imm_f16(sp, (_Float16)3.0);
    sp = vorth_imm_f16(sp, (_Float16)4.0);
    sp = vorth_mad_f16(sp);
    res = (_Float16*)sp - V;
    for (int i = 0; i < V; i++) {
        assert(fabs((double)res[i] - 10.0) < 0.001);
    }
}

static void test_f32(void) {
    float stack[8 * V] __attribute__((aligned(32)));
    void* sp = stack;

    sp = vorth_imm_f32(sp, 1.0f);
    sp = vorth_imm_f32(sp, 2.0f);
    sp = vorth_add_f32(sp);
    float* res = (float*)sp - V;
    for (int i = 0; i < V; i++) {
        assert(fabsf(res[i] - 3.0f) < 0.001f);
    }

    sp = stack;
    sp = vorth_imm_f32(sp, 5.0f);
    sp = vorth_imm_f32(sp, 3.0f);
    sp = vorth_sub_f32(sp);
    res = (float*)sp - V;
    for (int i = 0; i < V; i++) {
        assert(fabsf(res[i] - 2.0f) < 0.001f);
    }

    sp = stack;
    sp = vorth_imm_f32(sp, 2.0f);
    sp = vorth_imm_f32(sp, 3.0f);
    sp = vorth_mul_f32(sp);
    res = (float*)sp - V;
    for (int i = 0; i < V; i++) {
        assert(fabsf(res[i] - 6.0f) < 0.001f);
    }

    sp = stack;
    sp = vorth_imm_f32(sp, 6.0f);
    sp = vorth_imm_f32(sp, 2.0f);
    sp = vorth_div_f32(sp);
    res = (float*)sp - V;
    for (int i = 0; i < V; i++) {
        assert(fabsf(res[i] - 3.0f) < 0.001f);
    }

    sp = stack;
    sp = vorth_imm_f32(sp, 2.0f);
    sp = vorth_imm_f32(sp, 3.0f);
    sp = vorth_imm_f32(sp, 4.0f);
    sp = vorth_mad_f32(sp);
    res = (float*)sp - V;
    for (int i = 0; i < V; i++) {
        assert(fabsf(res[i] - 10.0f) < 0.001f);
    }
}

int main(void) {
    test_f16();
    test_f32();
    return 0;
}
