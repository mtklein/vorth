#pragma once

#define V 8

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

void* vorth_pop_f16(void*, _Float16[V]);
void* vorth_pop_f32(void*, float[V]);

void* vorth_imm_s8(void*, signed char);
void* vorth_pop_s8(void*, signed char[V]);

void* vorth_imm_s16(void*, short);
void* vorth_pop_s16(void*, short[V]);

void* vorth_imm_s32(void*, int);
void* vorth_pop_s32(void*, int[V]);

void* vorth_imm_u8(void*, unsigned char);
void* vorth_pop_u8(void*, unsigned char[V]);

void* vorth_imm_u16(void*, unsigned short);
void* vorth_pop_u16(void*, unsigned short[V]);

void* vorth_imm_u32(void*, unsigned int);
void* vorth_pop_u32(void*, unsigned int[V]);

void* vorth_add_i8(void*);
void* vorth_sub_i8(void*);
void* vorth_mul_i8(void*);

void* vorth_add_i16(void*);
void* vorth_sub_i16(void*);
void* vorth_mul_i16(void*);

void* vorth_add_i32(void*);
void* vorth_sub_i32(void*);
void* vorth_mul_i32(void*);

void* vorth_and_i8(void*);
void* vorth_or_i8(void*);
void* vorth_xor_i8(void*);
void* vorth_not_i8(void*);

void* vorth_and_i16(void*);
void* vorth_or_i16(void*);
void* vorth_xor_i16(void*);
void* vorth_not_i16(void*);

void* vorth_and_i32(void*);
void* vorth_or_i32(void*);
void* vorth_xor_i32(void*);
void* vorth_not_i32(void*);
