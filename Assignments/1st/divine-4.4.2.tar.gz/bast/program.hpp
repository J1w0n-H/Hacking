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
#include <vector>

namespace bast
{
    struct program;
    struct iterator;

    struct span
    {
        int begin, end;
        span( int s, int e ) : begin( s ), end( e ) {}
    };

    struct block
    {
        const program &p;
        span s;

        block( const program &p, span s ) : p( p ), s( s ) {}

        iterator begin() const;
        iterator end() const;
    };

    struct program
    {
        std::vector< word > code;
        std::vector< span > label;

        bast::block block( word label_id ) const
        {
            return bast::block( *this, label[ label_id ] );
        }

        iterator begin() const;
        iterator end() const;
    };

    struct iterator
    {
        span s;
        const program &p;

        iterator( const program &p, int b, int e ) : p( p ), s( b, e ) {}
        word operator*() { return p.code[ s.begin ]; }
        iterator &operator++() { ++ s.begin; return *this; }
        bool operator==( iterator o ) const { return s.begin == o.s.begin; }
        bool operator!=( iterator o ) const { return !( *this == o ); }
    };

    iterator program::begin() const { return iterator( *this, 0, code.size() ); }
    iterator program::end()   const { return iterator( *this, code.size(), code.size() ); }

    iterator block::begin() const { return iterator( p, s.begin, s.end ); }
    iterator block::end()   const { return iterator( p, s.end,   s.end ); }
}
