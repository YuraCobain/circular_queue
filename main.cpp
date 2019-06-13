#include "circular_queue.h"

#include <functional>
#include <iostream>
#include <queue>

int test_pop_from_empty_q_failed()
{
    CircularQueue cq( 32 );

    auto res = cq.pop_out();
    if ( res.second != OpStatus::Q_IS_EMPTY )
    {
        return -1;
    }

    std::cout << "CircularQueue->pop_out operation status is Q_IS_EMPTY\n";
    return 0;
}

int test_push_into_full_q_failed()
{
    CircularQueue cq( 4 );
    int test_input[4] = {1, 2, 3, 4};

    /* fill all queue capacity */
    for ( auto val : test_input )
    {
        auto status = cq.push_in( val );
        if ( status != OpStatus::OP_OK )
        {
            std::cout << "CircularQueue->push_in operation status is not OP_OK...\n";
            return -1;
        }
    }

    auto status = cq.push_in( 5 );

    if ( status != OpStatus::Q_IS_FULL )
    {
        return -1;
    }

    std::cout << "CircularQueue->pop_out operation status is Q_IS_FULL\n";
    return 0;
}

int test_fifo_policy()
{
    CircularQueue cq( 4 );
    std::queue<int> ref_q;
    int test_input[4] = {1, 2, 3, 4};

    /* fill all queue capacity */
    for ( auto val : test_input )
    {
        auto status = cq.push_in( val );
        ref_q.push( val );
        if ( status != OpStatus::OP_OK )
        {
            std::cout << "CircularQueue->push_in operation status is not OP_OK...\n";
            return -1;
        }
    }

    while ( !ref_q.empty() )
    {
        auto res = cq.pop_out();
        if ( res.second != OpStatus::OP_OK )
        {
            std::cout << "CircularQueue->pop_out operation status is not OP_OK...\n";
            return -1;
        }

        auto test_val = ref_q.front();
        ref_q.pop();

        if ( test_val != res.first )
        {
            std::cout << "CircularQueue fifo policy is broken: test != actual " << test_val << " "
                      << res.first << '\n';
            return -1;
        }
    }

    return 0;
}

struct TestCase
{
    std::string _name;
    std::function<int( void )> _fn;

    TestCase( const char* name, std::function<int( void )> fn ) : _name( name ), _fn( fn ) {}
    TestCase( std::string name, std::function<int( void )> fn ) : _name( name ), _fn( fn ) {}
};

int main()
{
    std::vector<TestCase> test_cases;

    test_cases.emplace_back( "pop_from_empty", test_pop_from_empty_q_failed );
    test_cases.emplace_back( "push_into_full", test_push_into_full_q_failed );
    test_cases.emplace_back( "fifo_policy", test_fifo_policy );

    for ( const auto& tc : test_cases )
    {
        std::cout << "\ntest " << tc._name << '\n';
        int ret = tc._fn();
        std::cout << "test " << tc._name << " is passed: " << std::boolalpha << (bool)(!ret) << '\n';
    }
}
