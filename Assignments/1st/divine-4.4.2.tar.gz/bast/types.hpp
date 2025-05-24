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
#include <map>
#include <vector>
#include <variant>
#include <cstdint>
#include <brick-assert>

namespace bast
{
    using byte = uint8_t;
    using half = uint16_t;
    using word = uint32_t;
    using dyad = uint64_t;

    struct stop_t { bool operator==( stop_t ) const { return true; } };
    struct next_t { bool operator==( next_t ) const { return true; } };
    struct jump
    {
        word label;
        bool operator==( jump ) const { UNREACHABLE( "jumps cannot be compared" ); }
    };

    using step = std::variant< stop_t, next_t, jump >;

    const constexpr step next = next_t();
    const constexpr step stop = stop_t();

    enum class builtin_type : word
    {
        byte,
        half,
        word,
        dyad,
        type,
        cont,
        dict,

        _count_
    };

    inline brq::string_builder &operator<<( brq::string_builder &b, builtin_type t )
    {
        switch ( t )
        {
            case builtin_type::byte: return b << "byte";
            case builtin_type::half: return b << "half";
            case builtin_type::word: return b << "word";
            case builtin_type::dyad: return b << "dyad";
            case builtin_type::type: return b << "type";
            case builtin_type::cont: return b << "cont";
            case builtin_type::dict: return b << "dict";
            default: return b << "type( " << word( t ) << " )";
        }
    }

    template< typename state_t, builtin_type type >
    struct op
    {
        static step apply( state_t &state, word opcode )
        {
            UNREACHABLE( "not implemented", typeid( state_t ).name(), type );
        }
    };

    struct type
    {
        std::vector< type > arg;
    };

    struct typemap
    {
        std::vector< type >   id_to_type;
        std::map< type, int > type_to_id;

        type get( int );
        int  get( type ); /* adds the type as needed */
    };
}
