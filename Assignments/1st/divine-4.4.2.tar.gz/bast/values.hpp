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
#include "opcodes.hpp"
#include "types.hpp"

namespace bast
{
    struct value_stack
    {
        std::vector< word > data; /* TODO dyads */

        void push_half( half h ) { data.push_back( h ); }
        void push_word( word w ) { data.push_back( w ); }
        bool operator==( const value_stack &o ) const { return data == o.data; }
        bool operator< ( const value_stack &o ) const { return data <  o.data; }

        word pop()
        {
            word w = data.back();
            data.pop_back();
            return w;
        }

        value_stack() = default;
        value_stack( std::initializer_list< word > il ) : data( il ) {}

        friend brq::string_builder &operator<<( brq::string_builder &b, const value_stack &s )
        {
            return b << s.data;
        }
    };

    template< builtin_type > struct bitvec_type : std::false_type {};
    template<> struct bitvec_type< builtin_type::byte > : std::true_type { using type = byte; };
    template<> struct bitvec_type< builtin_type::half > : std::true_type { using type = half; };
    template<> struct bitvec_type< builtin_type::word > : std::true_type { using type = word; };
    template<> struct bitvec_type< builtin_type::dyad > : std::true_type { using type = dyad; };

    template< builtin_type > struct signed_type : std::false_type {};
    template<> struct signed_type< builtin_type::byte > : std::true_type { using type = int8_t; };
    template<> struct signed_type< builtin_type::half > : std::true_type { using type = int16_t; };
    template<> struct signed_type< builtin_type::word > : std::true_type { using type = int32_t; };
    template<> struct signed_type< builtin_type::dyad > : std::true_type { using type = int64_t; };

    template< builtin_type t >
    struct op< std::enable_if_t< bitvec_type< t >::value, value_stack >, t >
    {
        using value_t  = typename bitvec_type< t >::type;
        using signed_t = typename signed_type< t >::type;

        template< typename impl_t >
        static step binary( value_stack &s, impl_t impl )
        {
            word a = s.pop(),
                 b = s.pop();
            s.push_word( impl( a, b ) );
            return next;
        }

        static step apply( value_stack &s, word opcode )
        {
            using namespace bast::opcodes;

            switch ( opcode )
            {
                case op_add:
                    return binary( s, []( value_t a, value_t b ) { return a + b; } );
                case op_sub:
                    return binary( s, []( value_t a, value_t b ) { return a - b; } );
                case op_mul:
                    return binary( s, []( value_t a, value_t b ) { return a * b; } );
                case op_udiv:
                    return binary( s, []( value_t a, value_t b ) { return a / b; } );
                case op_urem:
                    return binary( s, []( value_t a, value_t b ) { return a % b; } );
                case op_sdiv:
                    return binary( s, []( signed_t a, signed_t b ) { return a / b; } );
                case op_srem:
                    return binary( s, []( signed_t a, signed_t b ) { return a % b; } );

                case op_and:
                    return binary( s, []( value_t a, value_t b ) { return a & b; } );
                case op_or:
                    return binary( s, []( value_t a, value_t b ) { return a | b; } );
                case op_xor:
                    return binary( s, []( value_t a, value_t b ) { return a ^ b; } );
                case op_neg:
                    s.push_word( ~s.pop() );
                    return next;

                case op_dup:
                {
                    word x = s.pop();
                    s.push_word( x );
                    s.push_word( x );
                    return next;
                }

                case op_const:
                    return next;

                case guard_tt:
                    return s.pop() ? next : stop;
                case guard_ff:
                    return s.pop() ? stop : next;
                case guard_eq:
                    return s.pop() == s.pop() ? next : stop;

                default:
                    NOT_IMPLEMENTED();
            }
        }
    };
}
