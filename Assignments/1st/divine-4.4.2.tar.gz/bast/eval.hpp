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

#include "types.hpp"
#include "opcodes.hpp"
#include <optional>
#include <brick-except>

namespace bast
{
    struct invalid_opcode : brq::error { using brq::error::error; };

    template< typename state_t, word static_type = static_cast< word >( builtin_type::_count_ ) >
    step type_dispatch( word type, state_t &state, word opcode )
    {
        ASSERT( type <= static_type );

        if ( type == static_type )
            return op< state_t, builtin_type( static_type ) >::apply( state, opcode );
        else if constexpr ( static_type > 0 )
            return type_dispatch< state_t, static_type - 1 >( type, state, opcode );
        else
            __builtin_unreachable();
    }

    template< typename state_t >
    using word_ops = op< state_t, builtin_type::word >;

    template< typename state_t_, typename heap_t_ >
    struct eval
    {
        using state_t = state_t_;
        using heap_t  = heap_t_;

        program &prog;
        heap_t  &heap;

        eval( program &p, heap_t &h ) : prog( p ), heap( h ) {}

        static bool match( word op, word mask, word val )
        {
            return ( op & mask ) == val;
        }

        void shuffle( state_t &state, int count, int index )
        {
            if ( count == 1 ) /* those encode discards */
                for ( int i = 0; i < index; ++i )
                    state.pop();

            else
                NOT_IMPLEMENTED();
        }

        /* Decode and evaluate a single instruction, mutating the given state,
         * returning a label to jump to, if relevant. */

        step instruction( state_t &state, word op )
        {
            if ( !match( op, 0xff000000, 0xaa000000 ) )
            {
                state.push_word( op );
                return next;
            }

            if ( match( op, 0xff800000, opcodes::data_prefix ) )
                return type_dispatch< state_t >( ( op & 0x007fe000 ) >> 13, state, op & 0x1fff );

            switch ( op & 0xfff00000 )
            {
                case opcodes::push_half:
                    state.push_half( op & 0xffff );
                    return next;
                case opcodes::push_upper:
                    word_ops< state_t >::apply( state, opcodes::op_zext_1 );
                    state.push_word( ( op & 0xffff ) << 16 );
                    return word_ops< state_t >::apply( state, opcodes::op_or );
                case opcodes::block_label:
                    brq::raise< invalid_opcode >() << "unexpected label in the middle of a block";
                case opcodes::block_next:
                    return jump{ op & 0x000fffff };
                case opcodes::shuffle_prefix:
                    shuffle( state, ( ( op & 0x00070000 ) >> 16 ) + 1, op & 0xffff );
                    return next;
                default:
                    brq::raise< invalid_opcode >() << "invalid opcode " << /*std::hex <<*/ op;
            }

            __builtin_unreachable();
        }

        /* Evaluate a single block, yielding the labels of successors. The
         * state is updated in place. */

        template< typename yield_t >
        void block( state_t &state, word label, yield_t yield )
        {
            for ( word op : prog.block( label ) )
            {
                auto step = instruction( state, op );

                if ( step == stop )
                    break;
                if ( step == next )
                    continue;

                yield( std::get< jump >( step ).label );
            }
        }
    };

    template< typename eval_t, typename queue_t, typename visited_t >
    struct visit
    {
        eval_t eval;
        queue_t queue;
        visited_t visited;

        using state_t = typename eval_t::state_t;
        using heap_t  = typename eval_t::heap_t;

        visit( program &p, heap_t &heap )
            : eval( p, heap )
        {}

        visit( program &p, heap_t &heap, const queue_t &q, const visited_t &v )
            : eval( p, heap ), queue( q ), visited( v )
        {}

        void start( word label = 0 )
        {
            queue.new_state();
            queue.push( state_t(), label );
            visited.store( state_t(), label );
        }

        bool step()
        {
            auto top = queue.pop();
            auto &[ state, label ] = top;

            auto push = [&]( word next )
            {
                auto &[ state, label ] = top;
                if ( visited.store( state, next ) )
                    queue.push( state, next );
            };

            queue.new_state();
            eval.block( state, label, push );

            return !queue.empty();
        }
    };
}
