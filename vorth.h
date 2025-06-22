#pragma once

#define V 8

typedef _Float16 F16 __attribute__((vector_size(sizeof(_Float16) * V)));
typedef float    F32 __attribute__((vector_size(sizeof(float) * V)));

#define splat(T, x) ((T){0} + 1) * (x)

// vorth is a SIMT-style vectorized Forth-style language.  Its priorities:
//   - correctness
//   - efficient memory access
//   - optimized execution
//   - compact code size

// vorth methods take and return the stack pointer as first parameter.
// Suffixes indicate data size and type, e.g.
//   _f16 -> 16-bit float
//   _f32 -> 32-bit float
//   _s8  -> signed byte
//   _u16 -> unsigned short
//   _i32 -> bitwise or integer operations where signedness doesn't matter.

void* vorth_imm_f16(void*, _Float16);
void* vorth_add_f16(void*);
void* vorth_sub_f16(void*);
void* vorth_mul_f16(void*);
void* vorth_div_f16(void*);
void* vorth_mad_f16(void*);

void* vorth_imm_f32(void*, float);
void* vorth_add_f32(void*);
void* vorth_sub_f32(void*);
void* vorth_mul_f32(void*);
void* vorth_div_f32(void*);
void* vorth_mad_f32(void*);
