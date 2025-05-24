#include "builder.hpp"
#include <brick-unit>

int main()
{
    using namespace bast::opcodes;
    bast::builder b;

    brq::test_case( "simple" ) = [=]() mutable
    {
        b.add_block() = { 13, 15, word_add };
        std::vector expect{ 0xaa200000u, 13u, 15u, 0xaa804010u };
        ASSERT_EQ( b.build().code, expect );
    };

    brq::test_case( "two_blocks" ) = [=]() mutable
    {
        auto &x = b.add_block() = { 13, 15, word_add };
        auto &y = b.add_block() = { 12, 15, word_add };
        x >> y;

        std::vector expect{ 0xaa200000u, 13u, 15u, 0xaa804010u, 0xaa300001u,
                            0xaa200001u, 12u, 15u, 0xaa804010u };

        ASSERT_EQ( b.build().code, expect );
    };

    brq::test_case( "branch" ) = [=]() mutable
    {
        auto &x = b.add_block() = { 1 };
        auto &y = b.add_block() = { 2 };
        auto &z = b.add_block() = { 3 };
        x >> y;
        x >> z;
        y >> z;

        std::vector expect{ 0xaa200000u, 1u, 0xaa300001u, 0xaa300002u,
                            0xaa200001u, 2u, 0xaa300002u,
                            0xaa200002u, 3u };

        ASSERT_EQ( b.build().code, expect );
    };

    brq::test_case( "loop_1" ) = [=]() mutable
    {
        auto &x = b.add_block() = { 1 };
        x >> x;
        std::vector expect{ 0xaa200000u, 1u, 0xaa300000u };
        ASSERT_EQ( b.build().code, expect );
    };

    brq::test_case( "loop_2" ) = [=]() mutable
    {
        auto &x = b.add_block() = { 1 };
        auto &y = b.add_block() = { 2 };
        x >> y;
        y >> x;
        std::vector expect{ 0xaa200000u, 1u, 0xaa300001u,
                            0xaa200001u, 2u, 0xaa300000u };
        ASSERT_EQ( b.build().code, expect );
    };
}
