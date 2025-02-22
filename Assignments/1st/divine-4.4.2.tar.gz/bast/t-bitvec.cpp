#include "builder.hpp"
#include "values.hpp"
#include "eval.hpp"
#include <brick-unit>

int main()
{
    using namespace bast::opcodes;
    using eval_t = bast::eval< bast::value_stack, brq::unit >;
    bast::builder b;
    brq::unit heap;

    auto test_simple = [=]( bast::builder &b, int expect ) mutable
    {
        auto p = b.build();
        auto e = eval_t( p, heap );
        auto s = bast::value_stack();

        e.block( s, 0, []( bast::word w ) { ASSERT( false, w ); } );
        ASSERT_EQ( s.data.size(), 1 );
        ASSERT_EQ( s.data.back(), expect );
        b.clear();
    };

    brq::test_case( "word_add" ) = [=]() mutable
    {
        b.add_block() = { 13, 15, word_add };
        test_simple( b, 28 );
    };

    brq::test_case( "byte_add" ) = [=]() mutable
    {
        b.add_block() = { 13, byte_const,
                          15, byte_const, byte_add };
        test_simple( b, 28 );
    };

    brq::test_case( "byte_signed" ) = [=]() mutable
    {
        b.add_block() = { unsigned( -1 ), byte_const, 13, byte_const, byte_sdiv };
        test_simple( b, -13 );
        b.add_block() = { unsigned( -1 ), byte_const, 13, byte_const, byte_udiv };
        test_simple( b, 0 );
    };

    brq::test_case( "byte_g_tt" ) = [=]() mutable
    {
        b.add_block() = { 7, byte_g_tt, 1 };

        auto p = b.build();
        auto e = eval_t( p, heap );
        auto s = bast::value_stack();

        e.block( s, 0, []( bast::word w ) { ASSERT( false, w ); } );
        ASSERT_EQ( s.data.size(), 1 );
        ASSERT_EQ( s.data.back(), 1 );
    };

    brq::test_case( "byte_g_ff" ) = [=]() mutable
    {
        b.add_block() = { 7, byte_g_ff, 1 };

        auto p = b.build();
        auto e = eval_t( p, heap );
        auto s = bast::value_stack();

        e.block( s, 0, []( bast::word w ) { ASSERT( false, w ); } );
        ASSERT_EQ( s.data.size(), 0 );
    };
}
