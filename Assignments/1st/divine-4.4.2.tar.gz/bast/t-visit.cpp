#include "builder.hpp"
#include "values.hpp"
#include "eval.hpp"
#include <brick-unit>
#include <set>
#include <deque>

using exec_state = std::pair< bast::value_stack, bast::word >;

struct visited
{
    std::set< exec_state > seen;

    bool store( const bast::value_stack s, bast::word w )
    {
        auto [ iter, was_new ] = seen.emplace( s, w );
        return was_new;
    }
};

struct queue
{
    std::deque< std::pair< bast::value_stack, bast::word > > todo;

    auto pop()
    {
        auto r = todo.back();
        todo.pop_back();
        return r;
    }

    void push( const bast::value_stack &o, bast::word w )
    {
        todo.emplace_back( o, w );
    }

    void new_state() {}
    bool empty() const { return todo.empty(); }
};

int main()
{
    using namespace bast::opcodes;
    using eval_t  = bast::eval< bast::value_stack, brq::unit >;
    using visit_t = bast::visit< eval_t, queue, visited >;
    using seen_t  = std::set< exec_state >;
    bast::builder b;

    auto do_visit = []( const bast::builder &b, int steps )
    {
        brq::unit heap;
        auto p = b.build();

        visit_t visit( p, heap );
        visit.start();

        for ( int i = 0; i < steps; ++i )
            ASSERT_EQ( i < steps - 1, visit.step() );

        return visit.visited.seen;
    };

    brq::test_case( "branch" ) = [=]() mutable
    {
        auto &x = b.add_block() = { 1 };
        auto &y = b.add_block() = { 2 };
        auto &z = b.add_block() = { 3 };
        x >> y;
        x >> z;
        y >> z;

        seen_t seen = do_visit( b, 4 ),
               want = { { {}, 0 }, { { 1 }, 1 }, { { 1 }, 2 }, { { 1, 2 }, 2 } };
        ASSERT_EQ( seen, want );
    };

    brq::test_case( "loop_1" ) = [=]() mutable
    {
        auto &x = b.add_block() = {};
        x >> x;

        seen_t seen = do_visit( b, 1 ),
               want = { { {}, 0 } };

        ASSERT_EQ( seen, want );
    };

    brq::test_case( "loop_2" ) = [=]() mutable
    {
        auto &x = b.add_block() = {};
        auto &y = b.add_block() = {};
        x >> y;
        y >> x;

        seen_t seen = do_visit( b, 2 ),
               want = { { {}, 0 }, { {}, 1 } };

        ASSERT_EQ( seen, want );
    };

    brq::test_case( "loop_3" ) = [=]() mutable
    {
        auto &x = b.add_block() = { 1 };
        auto &y = b.add_block() = { drop };
        x >> y;
        y >> x;

        seen_t seen = do_visit( b, 2 ),
               want = { { {}, 0 }, { { 1 }, 1 } };

        ASSERT_EQ( seen, want );
    };
}
