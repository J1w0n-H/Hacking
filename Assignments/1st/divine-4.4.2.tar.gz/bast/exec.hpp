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
#include "values.hpp"
#include "eval.hpp"
#include <stack>
#include <vector>

namespace bast
{
    struct exec_visited /* unwind executions into a tree */
    {
        bool store( const bast::value_stack, bast::word ) { return true; }
    };

    struct exec_stack
    {
        using state_t = std::pair< value_stack, word >;
        using succs_t = std::pair< value_stack, std::vector< word > >;
        std::stack< succs_t > todo;

        void new_state()
        {
            todo.emplace();
        }

        void cleanup()
        {
            while ( !todo.empty() )
            {
                auto &[ data, pc ] = todo.top();

                if ( pc.empty() )
                    todo.pop();
                else
                    break;
            }
        }

        state_t pop()
        {
            cleanup();
            ASSERT( !todo.empty() );
            auto &[ data, pc ] = todo.top();

            ASSERT( !pc.empty() );
            word target = pc.back();
            pc.pop_back();

            if ( pc.empty() )
            {
                state_t rv( std::move( data ), target );
                todo.pop();
                return rv;
            }

            return { data, target };
        }

        void push( const bast::value_stack &o, bast::word w )
        {
            ASSERT( !todo.empty() );
            auto &[ data, pc ] = todo.top();

            if ( pc.empty() )
                data = o;
            else
                ASSERT_EQ( data, o );

            pc.push_back( w );
        }

        bool empty() { cleanup(); return todo.empty(); }

        word next()
        {
            cleanup();
            ASSERT( !empty() );
            auto &[ data, pc ] = todo.top();
            ASSERT( !pc.empty() );
            return pc.back();
        }
    };

    template< typename eval_t >
    using exec = visit< eval_t, exec_stack, exec_visited >;
}
