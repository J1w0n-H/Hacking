/*
 * (c) 2022 Petr Ročkai <code@fixp.eu>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#pragma once
#include "types.hpp"

namespace bast::opcodes
{
    const constexpr word data_prefix    = 0xaa800000;
    const constexpr word push_half      = 0xaa000000; /* | 16 bits (the half) */
    const constexpr word push_upper     = 0xaa010000; /* | 16 bits (the half) */
    const constexpr word block_label    = 0xaa200000; /* | 20 bits of id */
    const constexpr word block_next     = 0xaa300000; /* | 20 bits of id */
    const constexpr word shuffle_prefix = 0xaa400000;

    /* shuffles */

    const constexpr word shf2_prefix = 0xaa410000;
    const constexpr word shf3_prefix = 0xaa420000;
    const constexpr word shf4_prefix = 0xaa430000;
    const constexpr word shf5_prefix = 0xaa440000;
    const constexpr word shf6_prefix = 0xaa450000;
    const constexpr word shf7_prefix = 0xaa460000;
    const constexpr word shf8_prefix = 0xaa470000;

    const constexpr word swap        = shf2_prefix | 1;
    const constexpr word rot3        = shf3_prefix | 4;
    const constexpr word rev3        = shf3_prefix | 5;
    const constexpr word rot4        = shf4_prefix | 18;
    const constexpr word rev4        = shf4_prefix | 23;
    const constexpr word drop        = shuffle_prefix | 1;
    const constexpr word drop2       = shuffle_prefix | 2;
    const constexpr word drop3       = shuffle_prefix | 2;

    /* type codes (bits 14-23) */

    const constexpr word type_byte = word( builtin_type::byte ) << 13;
    const constexpr word type_half = word( builtin_type::half ) << 13;
    const constexpr word type_word = word( builtin_type::word ) << 13;
    const constexpr word type_dyad = word( builtin_type::dyad ) << 13;
    const constexpr word type_type = word( builtin_type::type ) << 13;
    const constexpr word type_cont = word( builtin_type::cont ) << 13;
    const constexpr word type_dict = word( builtin_type::dict ) << 13;

    /* operation codes (bits 0-13) */

    const constexpr word op_typeid  = 0x00; // ø → type
    const constexpr word op_const   = 0x01; // word → x
    const constexpr word op_zero    = 0x02; // type → x
    const constexpr word op_dup     = 0x03; // x → x x

    const constexpr word op_add     = 0x10;
    const constexpr word op_sub     = 0x11;

    const constexpr word op_mul     = 0x12;
    const constexpr word op_sdiv    = 0x13;
    const constexpr word op_udiv    = 0x14;
    const constexpr word op_srem    = 0x15;
    const constexpr word op_urem    = 0x16;

    const constexpr word op_and     = 0x20;
    const constexpr word op_or      = 0x21;
    const constexpr word op_xor     = 0x22;
    const constexpr word op_neg     = 0x23;

    const constexpr word op_shl     = 0x23;
    const constexpr word op_lshr    = 0x24;
    const constexpr word op_ashr    = 0x25;

    const constexpr word op_eq      = 0x30;
    const constexpr word op_neq     = 0x31;
    const constexpr word op_ule     = 0x32;
    const constexpr word op_ult     = 0x33;
    const constexpr word op_ugt     = 0x34;
    const constexpr word op_uge     = 0x35;
    const constexpr word op_sle     = 0x36;
    const constexpr word op_slt     = 0x37;
    const constexpr word op_sgt     = 0x38;
    const constexpr word op_sge     = 0x39;

    const constexpr word guard_ff   = 0x40; /* top of the stack is 0  */
    const constexpr word guard_tt   = 0x41; /* top of the stack is !0 */
    const constexpr word guard_eq   = 0x42; /* top 2 items are equal  */

    const constexpr word op_zext_1  = 0x50; // byte → half, half → word, word → dyad
    const constexpr word op_zext_2  = 0x51; // byte → word, half → dyad
    const constexpr word op_zext_3  = 0x52; // byte → dyad
    const constexpr word op_sext_1  = 0x53; // byte → half, half → word, word → dyad
    const constexpr word op_sext_2  = 0x54; // byte → word, half → dyad
    const constexpr word op_sext_3  = 0x55; // byte → dyad
    const constexpr word op_trunc_1 = 0x56;
    const constexpr word op_trunc_2 = 0x57;
    const constexpr word op_trunc_3 = 0x58;

    /* byte (8 bit) operations */

    const constexpr word byte_typeid  = data_prefix | type_byte | op_typeid;
    const constexpr word byte_const   = data_prefix | type_byte | op_const;
    const constexpr word byte_zero    = data_prefix | type_byte | op_zero;
    const constexpr word byte_dup     = data_prefix | type_byte | op_dup;

    const constexpr word byte_zext_1  = data_prefix | type_byte | op_zext_1;
    const constexpr word byte_zext_2  = data_prefix | type_byte | op_zext_2;
    const constexpr word byte_zext_3  = data_prefix | type_byte | op_zext_3;
    const constexpr word byte_sext_1  = data_prefix | type_byte | op_sext_1;
    const constexpr word byte_sext_2  = data_prefix | type_byte | op_sext_2;
    const constexpr word byte_sext_3  = data_prefix | type_byte | op_sext_3;

    const constexpr word byte_add     = data_prefix | type_byte | op_add;
    const constexpr word byte_sub     = data_prefix | type_byte | op_sub;

    const constexpr word byte_mul     = data_prefix | type_byte | op_mul;
    const constexpr word byte_sdiv    = data_prefix | type_byte | op_sdiv;
    const constexpr word byte_udiv    = data_prefix | type_byte | op_udiv;
    const constexpr word byte_srem    = data_prefix | type_byte | op_srem;
    const constexpr word byte_urem    = data_prefix | type_byte | op_urem;

    const constexpr word byte_and     = data_prefix | type_byte | op_and;
    const constexpr word byte_or      = data_prefix | type_byte | op_or;
    const constexpr word byte_xor     = data_prefix | type_byte | op_xor;
    const constexpr word byte_neg     = data_prefix | type_byte | op_neg;

    const constexpr word byte_shl     = data_prefix | type_byte | op_shl;
    const constexpr word byte_lshr    = data_prefix | type_byte | op_lshr;
    const constexpr word byte_ashr    = data_prefix | type_byte | op_ashr;

    const constexpr word byte_eq      = data_prefix | type_byte | op_eq;
    const constexpr word byte_neq     = data_prefix | type_byte | op_neq;
    const constexpr word byte_ule     = data_prefix | type_byte | op_ule;
    const constexpr word byte_ult     = data_prefix | type_byte | op_ult;
    const constexpr word byte_ugt     = data_prefix | type_byte | op_ugt;
    const constexpr word byte_uge     = data_prefix | type_byte | op_uge;
    const constexpr word byte_sle     = data_prefix | type_byte | op_sle;
    const constexpr word byte_slt     = data_prefix | type_byte | op_slt;
    const constexpr word byte_sgt     = data_prefix | type_byte | op_sgt;
    const constexpr word byte_sge     = data_prefix | type_byte | op_sge;

    const constexpr word byte_g_ff    = data_prefix | type_byte | guard_ff;
    const constexpr word byte_g_tt    = data_prefix | type_byte | guard_tt;
    const constexpr word byte_g_eq    = data_prefix | type_byte | guard_eq;

    /* half (16 bit) operations */

    const constexpr word half_typeid  = data_prefix | type_half | op_typeid;
    const constexpr word half_const   = data_prefix | type_half | op_const;
    const constexpr word half_zero    = data_prefix | type_half | op_zero;
    const constexpr word half_dup     = data_prefix | type_half | op_dup;

    const constexpr word half_zext_1  = data_prefix | type_half | op_zext_1;
    const constexpr word half_zext_2  = data_prefix | type_half | op_zext_2;
    const constexpr word half_sext_1  = data_prefix | type_half | op_sext_1;
    const constexpr word half_sext_2  = data_prefix | type_half | op_sext_2;
    const constexpr word half_trunc_1 = data_prefix | type_half | op_trunc_1;

    const constexpr word half_add     = data_prefix | type_half | op_add;
    const constexpr word half_sub     = data_prefix | type_half | op_sub;

    const constexpr word half_mul     = data_prefix | type_half | op_mul;
    const constexpr word half_sdiv    = data_prefix | type_half | op_sdiv;
    const constexpr word half_udiv    = data_prefix | type_half | op_udiv;
    const constexpr word half_srem    = data_prefix | type_half | op_srem;
    const constexpr word half_urem    = data_prefix | type_half | op_urem;

    const constexpr word half_and     = data_prefix | type_half | op_and;
    const constexpr word half_or      = data_prefix | type_half | op_or;
    const constexpr word half_xor     = data_prefix | type_half | op_xor;
    const constexpr word half_neg     = data_prefix | type_half | op_neg;

    const constexpr word half_shl     = data_prefix | type_half | op_shl;
    const constexpr word half_lshr    = data_prefix | type_half | op_lshr;
    const constexpr word half_ashr    = data_prefix | type_half | op_ashr;

    const constexpr word half_eq      = data_prefix | type_half | op_eq;
    const constexpr word half_neq     = data_prefix | type_half | op_neq;
    const constexpr word half_ule     = data_prefix | type_half | op_ule;
    const constexpr word half_ult     = data_prefix | type_half | op_ult;
    const constexpr word half_ugt     = data_prefix | type_half | op_ugt;
    const constexpr word half_uge     = data_prefix | type_half | op_uge;
    const constexpr word half_sle     = data_prefix | type_half | op_sle;
    const constexpr word half_slt     = data_prefix | type_half | op_slt;
    const constexpr word half_sgt     = data_prefix | type_half | op_sgt;
    const constexpr word half_sge     = data_prefix | type_half | op_sge;

    const constexpr word half_g_ff    = data_prefix | type_half | guard_ff;
    const constexpr word half_g_tt    = data_prefix | type_half | guard_tt;
    const constexpr word half_g_eq    = data_prefix | type_half | guard_eq;

    /* word (32 bit) operations */

    const constexpr word word_typeid  = data_prefix | type_word | op_typeid;
    const constexpr word word_const   = data_prefix | type_word | op_const;
    const constexpr word word_zero    = data_prefix | type_word | op_zero;
    const constexpr word word_dup     = data_prefix | type_word | op_dup;

    const constexpr word word_zext_1  = data_prefix | type_word | op_zext_1;
    const constexpr word word_sext_1  = data_prefix | type_word | op_sext_1;
    const constexpr word word_trunc_1 = data_prefix | type_word | op_trunc_1;
    const constexpr word word_trunc_2 = data_prefix | type_word | op_trunc_2;

    const constexpr word word_add     = data_prefix | type_word | op_add;
    const constexpr word word_sub     = data_prefix | type_word | op_sub;

    const constexpr word word_mul     = data_prefix | type_word | op_mul;
    const constexpr word word_sdiv    = data_prefix | type_word | op_sdiv;
    const constexpr word word_udiv    = data_prefix | type_word | op_udiv;
    const constexpr word word_srem    = data_prefix | type_word | op_srem;
    const constexpr word word_urem    = data_prefix | type_word | op_urem;

    const constexpr word word_and     = data_prefix | type_word | op_and;
    const constexpr word word_or      = data_prefix | type_word | op_or;
    const constexpr word word_xor     = data_prefix | type_word | op_xor;
    const constexpr word word_neg     = data_prefix | type_word | op_neg;

    const constexpr word word_shl     = data_prefix | type_word | op_shl;
    const constexpr word word_lshr    = data_prefix | type_word | op_lshr;
    const constexpr word word_ashr    = data_prefix | type_word | op_ashr;

    const constexpr word word_eq      = data_prefix | type_word | op_eq;
    const constexpr word word_neq     = data_prefix | type_word | op_neq;
    const constexpr word word_ule     = data_prefix | type_word | op_ule;
    const constexpr word word_ult     = data_prefix | type_word | op_ult;
    const constexpr word word_ugt     = data_prefix | type_word | op_ugt;
    const constexpr word word_uge     = data_prefix | type_word | op_uge;
    const constexpr word word_sle     = data_prefix | type_word | op_sle;
    const constexpr word word_slt     = data_prefix | type_word | op_slt;
    const constexpr word word_sgt     = data_prefix | type_word | op_sgt;
    const constexpr word word_sge     = data_prefix | type_word | op_sge;

    const constexpr word word_g_ff    = data_prefix | type_word | guard_ff;
    const constexpr word word_g_tt    = data_prefix | type_word | guard_tt;
    const constexpr word word_g_eq    = data_prefix | type_word | guard_eq;

    /* dyad (64 bit) operations */

    const constexpr word dyad_typeid  = data_prefix | type_dyad | op_typeid;
    const constexpr word dyad_const   = data_prefix | type_dyad | op_const;
    const constexpr word dyad_zero    = data_prefix | type_dyad | op_zero;
    const constexpr word dyad_dup     = data_prefix | type_dyad | op_dup;

    const constexpr word dyad_trunc_1 = data_prefix | type_dyad | op_trunc_1;
    const constexpr word dyad_trunc_2 = data_prefix | type_dyad | op_trunc_2;
    const constexpr word dyad_trunc_3 = data_prefix | type_dyad | op_trunc_3;

    const constexpr word dyad_add     = data_prefix | type_dyad | op_add;
    const constexpr word dyad_sub     = data_prefix | type_dyad | op_sub;

    const constexpr word dyad_mul     = data_prefix | type_dyad | op_mul;
    const constexpr word dyad_sdiv    = data_prefix | type_dyad | op_sdiv;
    const constexpr word dyad_udiv    = data_prefix | type_dyad | op_udiv;
    const constexpr word dyad_srem    = data_prefix | type_dyad | op_srem;
    const constexpr word dyad_urem    = data_prefix | type_dyad | op_urem;

    const constexpr word dyad_and     = data_prefix | type_dyad | op_and;
    const constexpr word dyad_or      = data_prefix | type_dyad | op_or;
    const constexpr word dyad_xor     = data_prefix | type_dyad | op_xor;
    const constexpr word dyad_neg     = data_prefix | type_dyad | op_neg;

    const constexpr word dyad_shl     = data_prefix | type_dyad | op_shl;
    const constexpr word dyad_lshr    = data_prefix | type_dyad | op_lshr;
    const constexpr word dyad_ashr    = data_prefix | type_dyad | op_ashr;

    const constexpr word dyad_eq      = data_prefix | type_dyad | op_eq;
    const constexpr word dyad_neq     = data_prefix | type_dyad | op_neq;
    const constexpr word dyad_ule     = data_prefix | type_dyad | op_ule;
    const constexpr word dyad_ult     = data_prefix | type_dyad | op_ult;
    const constexpr word dyad_ugt     = data_prefix | type_dyad | op_ugt;
    const constexpr word dyad_uge     = data_prefix | type_dyad | op_uge;
    const constexpr word dyad_sle     = data_prefix | type_dyad | op_sle;
    const constexpr word dyad_slt     = data_prefix | type_dyad | op_slt;
    const constexpr word dyad_sgt     = data_prefix | type_dyad | op_sgt;
    const constexpr word dyad_sge     = data_prefix | type_dyad | op_sge;

    const constexpr word dyad_g_ff    = data_prefix | type_dyad | guard_ff;
    const constexpr word dyad_g_tt    = data_prefix | type_dyad | guard_tt;
    const constexpr word dyad_g_eq    = data_prefix | type_dyad | guard_eq;
}
