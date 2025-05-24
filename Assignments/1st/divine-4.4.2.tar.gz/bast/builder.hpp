#include "program.hpp"
#include "opcodes.hpp"
#include <list>
#include <brick-assert>

namespace bast
{
    struct builder
    {
        struct block
        {
            std::vector< word > code;
            bool closed = false;

            explicit block( word id ) : code{ opcodes::block_label | id }
            {
                ASSERT_EQ( id & ~0xfffff, 0 );
            }

            block &operator+=( std::initializer_list< word > il )
            {
                ASSERT( !closed );
                code.insert( code.end(), il.begin(), il.end() );
                return *this;
            }

            block &operator=( const std::initializer_list< word > &il )
            {
                code.erase( code.begin() + 1, code.end() );
                return *this += il;
            }

            void operator<<( block &o ) const { builder::connect( o, *this ); }
            void operator>>( const block &o ) { builder::connect( *this, o ); }
        };

        std::list< block > blocks;

        block &add_block()
        {
            blocks.emplace_back( blocks.size() );
            return blocks.back();
        }

        static void connect( block &from, const block &to )
        {
            from.code.push_back( opcodes::block_next | to.code.front() & 0xfffff );
            from.closed = true;
        }

        program build() const
        {
            program p;

            for ( auto &b : blocks )
            {
                int start = p.code.size() + 1;
                p.code.insert( p.code.end(), b.code.begin(), b.code.end() );
                p.label.emplace_back( start, p.code.size() );
            }

            return p;
        }

        void clear()
        {
            blocks.clear();
        }
    };
}
