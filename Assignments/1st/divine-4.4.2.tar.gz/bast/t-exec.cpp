#include "builder.hpp"
#include "exec.hpp"
#include <brick-unit>

int main()
{
    using namespace bast::opcodes;
    using state_t = bast::value_stack;
    using eval_t = bast::eval< bast::value_stack, brq::unit >;
    using exec_t = bast::exec< eval_t >;
    bast::builder b;

    auto do_exec = []( const bast::builder &b, const bast::builder::block &end )
    {
        brq::unit heap;
        auto p = b.build();
        auto end_id = end.code.front() & 0xfffff;

        exec_t exec( p, heap );
        exec.start();

        while ( exec.queue.next() != end_id && exec.step() );
        ASSERT( !exec.queue.empty() );
        return exec.queue.todo.top().first;
    };

    brq::test_case( "simple" ) = [=]() mutable
    {
        auto &init = b.add_block() = { 7 };
        auto &end  = b.add_block();
        init >> end;

        state_t result = do_exec( b, end );
        state_t expect = { 7 };

        ASSERT_EQ( result, expect );
    };

    brq::test_case( "byte_loop" ) = [=]() mutable
    {
        auto &init = b.add_block() = { 13 };
        auto &loop = b.add_block() = { word_dup, word_g_tt, unsigned( -1 ), word_add };
        auto &exit = b.add_block() = { word_dup, word_g_ff, 33 };
        auto &end  = b.add_block();

        init >> loop;
        loop >> loop;
        loop >> exit;
        exit >> end;

        state_t result = do_exec( b, end );
        state_t expect = { 0, 33 };

        ASSERT_EQ( result, expect );
    };
}
