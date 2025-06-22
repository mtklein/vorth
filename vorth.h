#pragma once

#define V 8

typedef unsigned vorth_mask;

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
void* vorth_load_f16(void*, const _Float16*);
void* vorth_load_f32(void*, const float*);
void* vorth_load_mask_f16(void*, const _Float16*, vorth_mask);
void* vorth_load_mask_f32(void*, const float*, vorth_mask);
void* vorth_store_mask_f16(void*, _Float16*, vorth_mask);
void* vorth_store_mask_f32(void*, float*, vorth_mask);

void* vorth_imm_s8(void*, signed char);
void* vorth_pop_s8(void*, signed char[V]);
void* vorth_load_s8(void*, const signed char*);
void* vorth_load_mask_s8(void*, const signed char*, vorth_mask);
void* vorth_store_mask_s8(void*, signed char*, vorth_mask);

void* vorth_imm_s16(void*, short);
void* vorth_pop_s16(void*, short[V]);
void* vorth_load_s16(void*, const short*);
void* vorth_load_mask_s16(void*, const short*, vorth_mask);
void* vorth_store_mask_s16(void*, short*, vorth_mask);

void* vorth_imm_s32(void*, int);
void* vorth_pop_s32(void*, int[V]);
void* vorth_load_s32(void*, const int*);
void* vorth_load_mask_s32(void*, const int*, vorth_mask);
void* vorth_store_mask_s32(void*, int*, vorth_mask);

void* vorth_imm_u8(void*, unsigned char);
void* vorth_pop_u8(void*, unsigned char[V]);
void* vorth_load_u8(void*, const unsigned char*);
void* vorth_load_mask_u8(void*, const unsigned char*, vorth_mask);
void* vorth_store_mask_u8(void*, unsigned char*, vorth_mask);

void* vorth_imm_u16(void*, unsigned short);
void* vorth_pop_u16(void*, unsigned short[V]);
void* vorth_load_u16(void*, const unsigned short*);
void* vorth_load_mask_u16(void*, const unsigned short*, vorth_mask);
void* vorth_store_mask_u16(void*, unsigned short*, vorth_mask);

void* vorth_imm_u32(void*, unsigned int);
void* vorth_pop_u32(void*, unsigned int[V]);
void* vorth_load_u32(void*, const unsigned int*);
void* vorth_load_mask_u32(void*, const unsigned int*, vorth_mask);
void* vorth_store_mask_u32(void*, unsigned int*, vorth_mask);

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
